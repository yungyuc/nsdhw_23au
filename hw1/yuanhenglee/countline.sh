#! /bin/bash

# Check if the input is valid
if [ $# -lt 1 ]; then
    echo "missing file name"
    exit 1
elif [ $# -gt 1 ]; then
    echo "only one argument is allowed"
    exit 1
fi

# Check if the file exists
if [ ! -f $1 ]; then
    echo "$1 not found"
    exit 1
else
    # Count the number of lines with wc
    count=$(wc -l < $1)
    echo "$count lines in $1"
fi

