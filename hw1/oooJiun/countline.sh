# !/bin/bash

if [ $# -lt 1 ]; then
    echo "missing file name"
elif [ $# -gt 1 ]; then
    echo "only one argument is allowed"
else
    fname=$1
    if [ -f $fname ]; then
        lines=$(wc -l $fname | tr -dc '0-9' )
        echo "$lines lines in $fname"
    else
        echo "$fname not found"
    fi
fi
# 'wc -l filename' undercounts by one line; adding a blank line at the end of the file helps avoid this situation.
