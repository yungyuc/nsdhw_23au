#!/bin/bash

# This script count lines of a file


if [ $# -lt 1 ]; then
  echo "missing file name"
  exit
elif [ $# -gt 1 ]; then
  echo "only one argument is allowed"
  exit
fi

filename=$1

if [ ! -f "$filename" ]; then
  echo "$filename not found"
  exit
fi

line_count=$(wc -l $filename | tr -dc "0-9")
echo "$line_count lines in $filename"
