#!/bin/bash

FILESA=$(find *.Im_eps_xx_*)
FILESB=$(find fort.*)
BLANK=" "
FILESALL=$FILESA$BLANK$FILESB

mkdir deconv-out

for i in $(find $FILESALL) 
do
	TEST=$(grep -v "[0-9]*\.[0-9]*\(  0.0000E+00\)\{10\}" $i | grep "[0-9]")
	NLINES=$(echo "$TEST" | wc -l)
	if [ "$NLINES" -gt "3" ]
	then
		echo "file $i contains non null lines, saving"
		echo "$TEST" > $i
        	echo "repairing first line in file $i"
        	sed -i "/ [0-9]\{1,3\} \{1,3\}[0-9]\{1,3\}/s/ \{4,10\}/\t/g" $i
        	sed -i "/[0-9]\{1,3\}\t[0-9]\{1,3\}/s/ \{1,3\}/-/g" $i
        	sed -i "s/-E/E/g" $i
	
		for j in 2 3 4 5 6 7 8 9 10 11
			do
			#echo "testing $j column in $i file"
			TRANSNAME=$(awk -v col=$j 'NR==1 {print $col}' $i)
			DATA=$(awk -v col=$j 'NR==1 {next} $col {print $1" "$col}' $i)
			TRESHOLD=$(echo "$DATA" | awk -v limit=$1 '$2 > limit {print $2; exit}')
			if [ "$TRESHOLD" != "" ]
			then
				echo "$i: $j-th comlumn is not null- saving into deconv-out/$TRANSNAME.epsdec"
				echo "$DATA" > deconv-out/$TRANSNAME.epsdec
			fi
		done
	else
		echo "file $i doesn't contain any usefull info"
		rm $i
	fi  
done
