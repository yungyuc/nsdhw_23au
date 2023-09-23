#!/bin/bash

# Storing no. of parameters.
int_params="$#"

# Validating number of parameters.
if ! [ "$int_params" = 1 ]; then
  echo "Please provide exactly one parameter."
  exit 1
fi

# Validating file existence
filename="$1"
if ! [ -f "$filename" ]; then
  echo "The given file $filename does not exists."
  exit 2
fi

# Counting rows (raw w/o filename etc.)
no_rows=$(wc -l < "$filename")

# Printing results
echo "$no_rows rows in file $filename."
exit 0
