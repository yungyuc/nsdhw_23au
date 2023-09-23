#!/bin/bash

int_params="$#"

if ! [ "$int_params" = 1 ]; then
  echo "Please provide exactly one parameter."
  exit 0
fi

echo "Successfully terminated."