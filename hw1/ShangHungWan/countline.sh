#!/usr/bin/env bash

if [ "$#" -eq 0 ]; then
    echo "missing file name"
    exit 1
elif [ "$#" -gt 1 ]; then
    echo "only one argument is allowed"
    exit 1
fi

if [ ! -e "$1" ]; then
    echo "$1 not found"
    exit 1
fi

input=$(wc -l $1)
lines="${input%% *}"
echo "$lines lines in {}"
