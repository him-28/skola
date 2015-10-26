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

CASE=$(basename $PWD)

line=1
atoms=0

while ((1))
do
   if sed -n "${line}p" $CASE.inc | grep -q ORBITALS
   then
       ((atoms++))
       structline=$((atoms * 6 + 1))
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
   done
done
