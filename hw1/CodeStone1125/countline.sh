#!/bin/bash

#Just give space between if and the opening square braces like given below.
#if [ -f  "$File" ]; then

if [ "$#" -lt 1 ]; then
    echo "missing file name"
elif [ "$#" -gt 1 ]; then
    echo "only one argument is allowed"
else
    #Bash assignment can't have space beside "="
    fname="$1"
    if [ -f $fname ] ; then
        line_count= wc -l $fname
        echo "$line_count lines in $fname"
    else
        echo "$fname not found"
    fi
fi
