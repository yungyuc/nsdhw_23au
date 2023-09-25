#!/bin/bash

if [[ $# -lt 1 ]]; then
    echo -e "missing file name"
    elif [[ $# -gt 1 ]]; then
    echo -e "only one argument is allowed"
else
    if [ -e $1 ]; then
        echo "$(wc -l < "$1") lines in $1"
    else
        echo "$1 not found"
    fi
fi