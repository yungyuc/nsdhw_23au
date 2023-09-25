#!/bin/bash

if [[ $# -lt 1 ]] ; then
    echo "missing file name"
elif [[ $# -gt 1 ]] ; then
    echo "only one argument is allowed"
else
    fname=$0
    if [[ ${#fname} -gt 0 ]] ; then
        LINE_NUM=$(wc -l < $fname)
        echo "${LINE_NUM} lines in $fname"
    else
        echo "$fname not found"
    fi
fi
#notice: in (wc -l filename), the last line won't be counted, 
#to get the correct number of line, we must put a blank line to the bottom of the code
