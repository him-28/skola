#!/bin/bash

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# Copyright (c) 2016 Pavel Ondračka.

#TODO: add the delta-SCF method
#TODO: check multiplicity and error if not one
#TODO: add the print option

function help {
   echo "Script to calculate core electron shifts using Wien2k"
   echo ""
   echo "Usage: XPS.sh [atoms]:[levels] [atoms:levels]"
   echo "atoms are selected by their number from struct file"
   echo "multiple atoms can be selected using ',' or '-' e.g. 1,2,5 or 5-10"
   echo "the same syntax goes for core levels"
   echo ""
   echo "-h print this help and exit"
   echo "-p print list of atoms with core levels"
}

function print {
   echo "print option not working yet"
}

if (($# == 0))
then
   help
   exit
fi

edgenames=("" "1S" "2S" "2PP" "2P")

CASE=$(basename $PWD)
cd $PWD

line=1
atoms=0

while ((1))
do
   if sed -n "${line}p" $CASE.inc | grep -q ORBITALS
   then
       ((atoms++))
       structline=$((atoms * 6 + 1))
       ((line[$atoms]=line))
       at_names[$atoms]=$(sed -n "${structline}p" $CASE.struct | cut -c -4 )
   elif sed -n "${line}p" $CASE.inc | grep -q " 0"
   then
       break
   else
       ((atoms[$atoms]++))
   fi
   ((line++))
done

for ((i=1; i<=atoms; i++))
do
   echo $i ${at_names[$i]} ${atoms[$i]} 
done

for arg in $@
do
   selected_atoms=$(echo $arg | cut -d ":" -f1)
   selected_atoms=$(echo $selected_atoms | sed 's/,/ /g')
   selected_edges=$(echo $arg | cut -d ":" -f2)
   selected_edges=$(echo $selected_edges | sed 's/,/ /g')

   expanded_atoms=()

   for i in $selected_atoms
   do
      if echo $i | grep "-" > /dev/null
      then
         min=$(echo $i | cut -d "-" -f1)
         max=$(echo $i | cut -d "-" -f2)
         expanded_atoms+=($(seq $min $max))
         continue
      fi
      expanded_atoms+=($i)
   done
done

echo ${expanded_atoms[@]}

for atom in ${expanded_atoms[@]}
do
   if ((atom > atoms))
   then
      echo "atom number $atom not present"
      continue
   fi

   for edge in $selected_edges
   do
      if ((edge > atoms[atom]))
      then
         echo "edge $edge for atom $atom not present"
         continue
      fi

      touch .XPSlock-$atom-$edge

      (
         save_lapw -a -d $atom-$edge $atom-$edge > /dev/null
         cd $atom-$edge

         ls ../.lcore > /dev/null && touch .lcore
         sed -i 's/ 0.0/-0.5/g' $atom-$edge.inm
         incline=$((line[$atom]+edge))
         awk -F "," -v n=$incline '{if (NR==n){printf "%1i,%1i,%.1f\n", $1, $2, $3-0.5} else print}' $atom-$edge.inc > tmp.inc
         mv tmp.inc $atom-$edge.inc

         task_id=$(qsub -A OPEN-6-17 -q qprod -l select=1:ncpus=24,walltime=30:00:00 ~/scripts/kpar_xnodes_mpi)

	 #this could be probably done in a smarter way, with no need to spawn lots of subshells
         while qstat -a -u ondracka | grep $task_id > /dev/null
         do
            sleep 120
         done

         greppatern=$(printf "%-3s%0*d" "${edgenames[$edge]}" 3 $atom)
         ecore=$(grep "$greppatern" $atom-$edge.scfc | grep -o "\-[0-9]*\.[0-9]*")
         efermi=$(grep \:FER $atom-$edge.scf2 | grep -Eo "\-?[0-9]+\.[0-9]+")

         energy=$(echo "$efermi - $ecore" | bc)
         echo $atom ${at_names[$atom]} $edge ${edgenames[$edge]} $ecore $efermi $energy >> ../XPS-shifts.txt

         cd ..

	 rm .XPSlock-$atom-$edge
      )&

      # limit number of processes
      while [ $(ls .XPSlock* | wc -l) -gt "80" ]
      do
         sleep 60
      done
   done

done
