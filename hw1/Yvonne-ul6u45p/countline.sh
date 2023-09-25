#!/bin/bash
# reimplement countline.py

filename="$(basename "$0")"     # get current filename
# echo "${0##*/}"
lines_num="$(wc -l $filename | tr -dc '0-9')"   # get the number of lines in this file
echo "$lines_num lines in $filename"
