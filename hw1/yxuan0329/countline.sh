#!/bin/bash

if [ $# -lt 1 ]; then
    echo "missing file name"
elif [ $# -gt 1 ]; then
    echo "only one argument is allowed"
else
    filename=$1
    if [ -e $filename ]; then
        line_count=$(wc -l < "$filename")
        echo "$line_count lines in $filename"
    else 
        echo "$filename not found"
    fi 
fi 