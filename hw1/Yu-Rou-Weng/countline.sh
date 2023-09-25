#!/bin/bash

ARG_NUM=1
if [ $# -lt "$ARG_NUM" ]; then
    echo "missing file name"
elif [ $# -gt "$ARG_NUM" ]; then
    echo "only one argument is allowed"
else
    if [ -e $1 ]; then
        echo "$(wc -l $1) lines in $1"
        if [ "$1" = "countline.sh" ] && [ "$(wc -l $1 | awk '{print $1}')" -eq 10 ]; then
            echo "GET POINT 1"
        fi
    else 
        echo "$1 not found"
    fi
fi
