#!/bin/bash

if [ $# -lt 1 ]; then
    echo -e 'missing file name\n'
elif [ $# -gt 1 ]; then
    echo -e 'only one argument is allowed\n'
else
    fname="$1"
    if [ -e "$fname" ]; then
        lines=$(wc -l <"$fname")
        echo "$lines lines in $fname"
    else
        echo "$fname not found\n"
    fi
fi