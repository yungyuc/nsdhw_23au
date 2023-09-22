#!/bin/bash

if [ $# -eq 1 ]; then
    if test -f $1; then
        line=$(wc -l $1 | cut -d " " -f 1)
        echo -n $line && echo -n " lines in " && echo $1
    else
        echo -n $1 && echo " not found"
    fi
else if [ $# -eq 0 ]; then
    echo "missing file name"
    else
      echo "only one argument is allowed"
  fi
fi
