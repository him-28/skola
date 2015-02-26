#!/bin/bash

FILTENE=$HOME/programs/skola/random-stuff/filtene/filtene

METHOD="AIM" 

CASE=$(basename $(pwd))
export SCRATCH=$PWD

rm -r IPR
mkdir IPR
cp $CASE.klist IPR/IPR.klist
cp $CASE.vsp IPR/IPR.vsp
cp $CASE.kgen IPR/IPR.kgen
cp $CASE.struct IPR/IPR.struct
cp $CASE.in2f IPR/IPR.in2

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


for band in {1..2}
do
   # create case.inf file and run filtvec
   printf "2 1 -$NKPOINTS \n1 $band\n" > $CASE.inf
   x filtvec
   cp $CASE.vectorf IPR/IPR.vector

   # run filtene
   $FILTENE $band $CASE.energy
   cp $CASE.energyf IPR/IPR.energy

   # run lapw on filtered data 
   cd IPR && SCRATCH=$PWD x lapw2

   if [ "$METHOD" == "SCF2" ]
   then
      #parse output
      grep "BAN" IPR.scf2 | sed "s/:BAN.....:...//" | tr '\n' ' '>> IPR.txt
      grep "\:CHA[0-9]" IPR.scf2 | grep -o "[0-9]\.[0-9]*  " | tr '\n' ' ' >> IPR.txt
      echo "" >> IPR.txt
   elif [ "$METHOD" == "AIM" ]
   then
      x mixer
      grep "BAN" IPR.scf2 | sed "s/:BAN.....:...//" | tr '\n' ' '>> IPR.txt
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
   #fixme: count for different multiplicity 
   awk '{print $2, $3, $5/2/($5+$6), $6/4/($5+$6)}' IPR/IPR.txt | awk '{print $1, $2, 2*$3*$3+4*$4*$4}' > IPRfinal.txt
fi

exit 
