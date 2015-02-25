#!/bin/bash

FILTENE=$HOME/programs/skola/random-stuff/filtene/filtene

CASE=$(basename $(pwd))
export SCRATCH=$PWD

rm -r IPR
mkdir IPR
cp $CASE.klist IPR/IPR.klist
cp $CASE.vsp IPR/IPR.vsp
cp $CASE.kgen IPR/IPR.kgen
cp $CASE.struct IPR/IPR.struct
cp $CASE.in2f IPR/IPR.in2

NKPOINTS=$(($(wc -l < $CASE.klist) - 2))
echo "kpoint number $NKPOINTS"

for band in {1..40}
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

   #parse output
   grep "BAN" IPR.scf2 | sed "s/:BAN.....:...//" | tr '\n' ' '>> IPR.txt
   grep "\:CHA[0-9]" IPR.scf2 | grep -o "[0-9]\.[0-9]*  " | tr '\n' ' ' >> IPR.txt
   echo "" >> IPR.txt

   cd ..
done

awk '{print $2, $3, $5/2/($5+$6), $6/4/($5+$6)}' IPR/IPR.txt | awk '{print $1, $2, 2*$3*$3+4*$4*$4}' > IPRfinal.txt

exit 
