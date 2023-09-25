#!/usr/bin/env python3

import sys
import os.path
import os

bin = os.environ["PYTHON_BIN"]
if bin not in ["python2","python3"]:
    sys.stdout.write("exec: "+ bin +': not found\n')
    exit(1)



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
