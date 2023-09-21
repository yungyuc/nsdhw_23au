#!/usr/bin/env python3

import sys
import os.path
import os

if os.environ["PYTHON_BIN"] == "python0":
    sys.stdout.write('exec: python0: not found\n')
    exit(1)

if len(sys.argv) < 2:
    sys.stdout.write('missing file name\n')
elif len(sys.argv) > 2:
    sys.stdout.write('only one argument is allowed\n')
else:
    fname = sys.argv[0]
    #question : fname should saved in sys.argv[0], why original code save it in sys.argv[1]?
    if os.path.exists(fname):
        with open(fname) as fobj:
            lines = fobj.readlines()
        sys.stdout.write('{} lines in {}\n'.format(len(lines), fname))
    else:
        sys.stdout.write('{} not found\n'.format(fname))
#notice: in (wc -l filename), the last line won't be counted, 
#to get the correct number of line, we must put a blank line to the bottom of the code
