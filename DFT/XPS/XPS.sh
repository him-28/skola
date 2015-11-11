#!/bin/bash

function help {
   echo "Usage: XPS-shifts [atoms]:[levels] [atoms:levels]"
   echo "multiple atoms can be selected using ',' or '-' e.g. 1,2,5 or 5-10"
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

      (
         save_lapw -a -d $atom-$edge $atom-$edge
         cd $atom-$edge
         sed -i 's/ 0.0/-0.5/g' $atom-$edge.inm
         incline=$((line[$atom]+edge))
         awk -F "," -v n=$incline '{if (NR==n){printf "%1i,%1i,%.1f\n", $1, $2, $3-0.5} else print}' $atom-$edge.inc > tmp.inc
         mv tmp.inc $atom-$edge.inc

         task_id=$(qsub -A OPEN-5-30 -q qprod -l select=1:ncpus=24,walltime=06:00:00 ~/scripts/kpar_xnodes_mpi)

         while qstat -a -u ondracka | grep $task_id > /dev/null
         do
            sleep 10
         done

         greppatern=$(printf "%-3s%0*d" "${edgenames[$edge]}" 3 $atom)
         ecore=$(grep "$greppatern" $atom-$edge.scfc | grep -o "\-[0-9]*\.[0-9]*")
         efermi=$(grep \:FER $atom-$edge.scf2 | grep -Eo "\-?[0-9]+\.[0-9]+")

         energy=$(echo "$efermi - $ecore" | bc)
         echo $atom ${at_names[$atom]} $edge ${edge_names[$edge]} $ecore $efermi $energy >> ../XPS-shifts.txt

         cd ..
         rm -r $atom-$edge
      )&

      # limit number of processes
      while [ "$(jobs | wc -l)" -gt "10" ]
      do
         sleep 1
      done
   done

done
