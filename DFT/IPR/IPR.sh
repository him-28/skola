#!/bin/bash

FILTENE=$HOME/programs/skola/DFT/IPR/filtene

METHOD="AIM"
if [ "$1" == "-p" ]
then
   PARA="-p"
   cd $PBS_O_WORKDIR
fi

CASE=$(basename $(pwd))
export SCRATCH=$PBS_O_WORKDIR

# check if we have a complex case
ls $CASE.in1c &> /dev/null
if [ "$?" == "0" ]
then
   COMPLEX="c"
fi

K_NUM=$(( $(wc -l $CASE.klist | awk '{print $1}') - 2 ))

rm -rf IPR
mkdir IPR
cp $CASE.klist IPR/IPR.klist
cp $CASE.vsp IPR/IPR.vsp
cp $CASE.kgen IPR/IPR.kgen
cp $CASE.struct IPR/IPR.struct
# set number of electrons to 2 in CASE.in2
awk 'NR != 2 {print $0} \
     NR ==2 {printf "%8.2f%8.2f%7.2f%5.2f%3i\n", $1, 2, $3, $4, $5}'\
     $CASE.in2$COMPLEX > IPR/IPR.in2$COMPLEX
# for some reason TETRA doesn't work well for single k-point
if (( K_NUM == 1 ))
then
   sed -i 's/TETRA    0.000/GAUSS    0.002/g' IPR/IPR.in2$COMPLEX
fi

if [ -n "$PARA" ]
then
   rm -f .machine*
   echo "granularity:1" >> .machines
   echo "lapw0:$(hostname):24" >> .machines
   echo "1:$(hostname):24" >> .machines

   cp .machines IPR/.machines

   # we need in1 file for parallel initialisation
   cp $CASE.in1$COMPLEX IPR/IPR.in1$COMPLEX
fi
#FIXME: read from .machines
NPROC=1

if [ "$METHOD" == "AIM" ]
then
   ls $CASE.inaim > /dev/null || exit
   cp $CASE.inm IPR/IPR.inm
   cp $CASE.inc IPR/IPR.inc
   #switch of renormalization in mixer
   sed -i 's/YES/NO/g' IPR/IPR.inm
fi

# create array with atom multiplicities
MULT=($(grep -o "MULT= [0-9]*" $CASE.struct | grep -o "[0-9]*" | tr '\n' ' '))
N_INDEP_ATOMS=${#MULT[*]}
NATOMS=0

for a in ${MULT[*]}
do
   NATOMS=$(($NATOMS + $a))
done
echo "we have $NATOMS atoms, $N_INDEP_ATOMS independent"

NKPOINTS=$(($(wc -l < $CASE.klist) - 2))
echo "kpoint number $NKPOINTS"

if [ "$METHOD" == "AIMX" ]
then
   # this run x aim in paralel over atoms
   for (( atom=1 ; atom<=$NATOMS ; atom++ ))
   do
      (
         mkdir IPR/surf$atom
         cd IPR/surf$atom
         cp ../../$CASE.inaim surf$atom.inaim
         cp ../../$CASE.clmsum surf$atom.clmsum
         cp ../../$CASE.struct surf$atom.struct
         sed -i "2s/[0-9]\+/$atom/g" surf$atom.inaim
         SCRATCH=$PWD x aim
         # prepare inaim file for integration
         printf "IRHO\nWEIT\n30\nEND" > surf$atom.inaim
      ) &

      # limit number of processes to number of processors
      while [ "$(jobs | wc -l)" -gt "$(nproc)" ]
      do
         sleep 1
      done
   done
   wait
   echo "AIM surfaces calculation finished"
fi

# FIXME: get number of bands from input, for now iterate till filtvec returns error
for band in {1..10}
do
   export SCRATCH=$PBS_O_WORKDIR

   if [ -n "$PARA" ]
   then
      for (( proc=1 ; proc<=$NPROC ; proc++  ))
      do
         #create case.inf
         K_NUM=$(( $(wc -l $CASE.klist_$proc | awk '{print $1}') - 1 ))
         # kpoint are actually numbered from 1 in CASE.vertor_x files
         if (( K_NUM == 1 ))
         then
            printf "1 1\n1 $band\n" > $CASE.inf$COMPLEX
         else
            printf "2 1 -$K_NUM \n1 $band\n" > $CASE.inf$COMPLEX
	 fi

         # run filtvec on partial vector files
         cp $CASE.vector_$proc $CASE.vector

         # run filtvec and stop when missing a band index
         x filtvec 2>&1 | grep ERROR && break 2
         mv $CASE.vectorf IPR/IPR.vector_$proc

         # run filtene on partial energy files
         $FILTENE $band $CASE.energy_$proc
         mv $CASE.energy_${proc}f IPR/IPR.energy_$proc
      done
   else
      printf "2 1 -$NKPOINTS \n1 $band\n" > $CASE.inf$COMPLEX

      # run filtvec and stop when missing a band index
      x filtvec 2>&1 | grep ERROR && break 2
      mv $CASE.vectorf IPR/IPR.vector

      # run filtene
      $FILTENE $band $CASE.energy
      mv $CASE.energyf IPR/IPR.energy
   fi

   export SCRATCH=$SCRATCH/IPR
   cd IPR
   # use lapw1 to regenerate needed machine and processes files
   if [ -z "$LAPW1_INIT" ] && [ -n "$PARA" ]
   then
      x lapw1 -d $PARA
      LAPW1_INIT=1
   fi
   # run lapw2 on filtered data
   x lapw2 $PARA

   if [ "$METHOD" == "SCF2" ]
   then
      #parse output
      grep "BAN" IPR.scf2 | sed "s/:BAN.....:...//" | tr '\n' ' '>> IPR.txt
      grep "\:CHA[0-9]" IPR.scf2 | grep -o "[0-9]\.[0-9]*  " | tr '\n' ' ' >> IPR.txt
      echo "" >> IPR.txt
   elif [ "$METHOD" == "AIM" ]
   then
      # mix the electron density for current band
      x mixer
      if (( K_NUM == 1 ))
      then
         grep "           1 " IPR.energy_1 | tr '\n' ' ' >> IPR.txt
      else
         grep "BAN" IPR.scf2 | sed "s/:BAN.....:...//" | tr '\n' ' '>> IPR.txt
      fi
      # integrate el. density on precomputed areas for all atoms
      for (( atom=1 ; atom<=$NATOMS ; atom++ ))
      do
         (
            cd surf$atom
            cp ../IPR.clmsum surf$atom.clmsum
            SCRATCH=$PWD x aim
         ) &

         # limit number of processes to number of processors
         while [ "$(jobs | wc -l)" -gt "$(nproc)" ]
         do
            sleep 1
         done
      done
      wait

      for (( atom=1 ; atom<=$NATOMS ; atom++ ))
      do
         CHARGE[$atom]=$(grep "CUBE.*CHARGE" surf$atom/surf$atom.outputaim | grep -o "[0-9]\+\.[0-9]\{8\}" | head -n1)
         printf "${CHARGE[$atom]} " >> IPR.txt
      done

      echo "" >> IPR.txt
   fi

   cd ..
done

if [ "$METHOD" == "SCF2" ]
then
   #FIXME: count for different multiplicity
   awk '{print $2, $3, $5/2/($5+$6), $6/4/($5+$6)}' IPR/IPR.txt | awk '{print $1, $2, 2*$3*$3+4*$4*$4}' > IPR/IPRfinal.txt
elif [ "$METHOD" == "AIM" ]
then
   if (( K_NUM == 1 ))
   then
      awk -v n="$NATOMS" '{sum=0; for (i=3; i<=2+n; i++) sum+= $i*$i/4; print $3, sum}' IPR/IPR.txt > IPR/IPRfinal.txt
   else
      awk -v n="$NATOMS" '{sum=0; for (i=5; i<=4+n; i++) sum+= $i*$i/4; print $2, $3, sum}' IPR/IPR.txt > IPR/IPRfinal.txt
   fi
fi

exit
