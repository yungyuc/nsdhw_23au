#!/bin/bash

if [ $# -lt 1 ]; then
	echo -e "missing file name\n"
elif [ $# -gt 1 ]; then
	echo -e "only one argument is allowed\n"
elif [ -e $0 ]; then
	num="$(wc -l $0 | tr -dc '0-9')"
	echo -e "$num lines in $0\n"
else
	echo -e "$0 not found\n"
fi
