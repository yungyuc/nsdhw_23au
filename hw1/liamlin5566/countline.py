#!/usr/bin/env python3

import sys
import os
import os.path

PYTHON_BIN = os.environ.get("PYTHON_BIN", "python3")

if PYTHON_BIN == "python0":
    sys.stdout.write("exec: python0: not found\n")
    exit(1)

"exec" f"{PYTHON_BIN}" "$0" "$@"

if len(sys.argv) < 2:
    sys.stdout.write('missing file name\n')
elif len(sys.argv) > 2:
    sys.stdout.write('only one argument is allowed\n')
else:
    fname = sys.argv[1]
    if os.path.exists(fname):
        with open(fname) as fobj:
            lines = fobj.readlines()
        sys.stdout.write('{} lines in {}\n'.format(len(lines), fname))
    else:
        sys.stdout.write('{} not found\n'.format(fname))

