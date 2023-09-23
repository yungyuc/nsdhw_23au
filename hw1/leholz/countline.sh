#!/bin/bash

int_params="$#"

# Validating number of parameters.
if ! [ "$int_params" = 1 ]; then
  echo "Please provide exactly one parameter."
  exit 1
fi

filename="$1"
if ! [ -f "$filename" ]; then
  echo "The given file $filename does not exists."
  exit 2
fi

echo "Successfully terminated."