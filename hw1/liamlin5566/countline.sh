#! /bin/bash

if [ "$#" == 0 ]; then
	echo "missing file name"
elif [ "$#" == 2 ]; then
	echo "only one argument is allowed"
else 

	count=0
	fname=$1
	
	if [ -f "$fname" ]; then	
		while read line; do  
			count=$((count+1))
		done < $fname
		echo "$count lines in $fname"
	else
		echo "$fname not found"
	fi
fi

