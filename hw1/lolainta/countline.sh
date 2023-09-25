#!/usr/bin/env bash
echo $(wc -l $1 | tr -dc '0-9')