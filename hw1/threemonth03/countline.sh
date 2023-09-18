#!/bin/bash
if [[ $# -lt 1 ]] ; then
    echo "missing file name"
elif [[ $# -gt 1 ]] ; then
    echo "only one argument is allowed"
else
    fname=$1
    if [[ -f $fname ]] ; then
        echo "$(wc -l < $fname) lines in $fname"
    else
        echo "$fname not found"
    fi
fi