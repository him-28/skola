#!/bin/bash

FILTENE=$HOME/programs/skola/random-stuff/filtene/filtene

METHOD="AIM"
if [ "$1" == "-p" ]
then
   PARA="-p"
   cd $PBS_O_WORKDIR
fi

CASE=$(basename $(pwd))
export SCRATCH=$PBS_O_WORKDIR

rm -rf IPR
mkdir IPR
cp $CASE.klist IPR/IPR.klist
cp $CASE.vsp IPR/IPR.vsp
cp $CASE.kgen IPR/IPR.kgen
cp $CASE.struct IPR/IPR.struct
cp $CASE.in2f IPR/IPR.in2

if [ -n "$PARA" ]
then
   rm -f .machine*
   echo "granularity:1" >> .machines
   echo "lapw0:$(hostname):16" >> .machines
   for i in {1..4}
   do
      echo "1:$(hostname):4" >> .machines
   done

   mv .machines IPR/.machines

   # we need in1 file for parallel initialisation
   cp $CASE.in1 IPR/IPR.in1
fi
#FIXME: read from .machines
NPROC=4


if [ "$METHOD" == "AIM" ]
then
   cp $CASE.inm IPR/IPR.inm
   cp $CASE.inc IPR/IPR.inc
   printf "IRHO\nWEIT\n30\nEND" >> IPR/IPR.inaim
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

if [ "$METHOD" == "AIM" ]
then
   for (( atom=1 ; atom<=$NATOMS ; atom++ ))
   do
      sed -i "2s/[0-9]\+/$atom/g" $CASE.inaim
      x aim
      mv $CASE.surf IPR/IPR.surf$atom
   done
fi

# get number of bands from input, for now iterate till filtvec returns error
for band in {40..10000}
do
   export SCRATCH=$PBS_O_WORKDIR

   if [ -n "$PARA" ]
   then
      for (( proc=1 ; proc<=$NPROC ; proc++  ))
      do
         #create case.inf
         K_NUM=$(( $(wc -l $CASE.klist_$proc | awk '{print $1}') - 1 ))
         # kpoint are actually numbered from 1 in CASE.vertor_x files
         printf "2 1 -$K_NUM \n1 $band\n" > $CASE.inf

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
      printf "2 1 -$NKPOINTS \n1 $band\n" > $CASE.inf

      # run filtvec and stop when missing a band index
      x filtvec 2>&1 | grep ERROR && break 2
      mv $CASE.vectorf IPR/IPR.vector

      # run filtene
      $FILTENE $band $CASE.energy
      mv $CASE.energyf IPR/IPR.energy
   fi

   # run lapw on filtered data
   export SCRATCH=$SCRATCH/IPR
   cd IPR && x lapw1 -d $PARA && x lapw2 $PARA

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
      grep "BAN" IPR.scf2 | sed "s/:BAN.....:...//" | tr '\n' ' '>> IPR.txt
      # integrate el. density on precomputed areas for all atoms
      for (( atom=1 ; atom<=$NATOMS ; atom++ ))
      do
         cp IPR.surf$atom IPR.surf
         sed -i "2s/[0-9]\+/$atom/g" IPR.inaim
         SCRATCH=$PWD x aim
         grep "CUBE.*CHARGE" IPR.outputaim | grep -o "[0-9]\+\.[0-9]\{8\}" | head -n1 | tr '\n' ' ' >> IPR.txt
      done
      echo "" >> IPR.txt
   fi

   cd ..
done

if [ "$METHOD" == "SCF2" ]
then
   #FIXME: count for different multiplicity
   awk '{print $2, $3, $5/2/($5+$6), $6/4/($5+$6)}' IPR/IPR.txt | awk '{print $1, $2, 2*$3*$3+4*$4*$4}' > IPRfinal.txt
fi

exit
