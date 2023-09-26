#!/usr/bin/env python3

import sys
import os.path

py_version = os.getenv('PYTHON_BIN')
if py_version != 'python2' and py_version != 'python3':
    sys.stdout.write('exec: {}: not found\n'.format(py_version))
    sys.exit(-1)
elif len(sys.argv) < 2:
    sys.stdout.write('missing file name\n')
elif len(sys.argv) > 2:
    sys.stdout.write('only one argument is allowed\n')
else:
    fname = sys.argv[1]
    if os.path.exists(fname):
        with open(fname) as fobj:
            lines = fobj.readlines()
        sys.stdout.write('{} lines in {}\n'.format(len(lines), fname))
        if fname == "countline.sh" and len(lines) == 10:
            sys.stdout.write('GET POINT 1\n')
    else:
        sys.stdout.write('{} not found\n'.format(fname))

