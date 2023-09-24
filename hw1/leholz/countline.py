#!/usr/bin/env python

import sys
import os.path

PYTHON_BIN_ENV = 'PYTHON_BIN'
python_bin_env_val = os.getenv(PYTHON_BIN_ENV)

current_py_bin = sys.executable
# Test ENV variable, return with error, if variable is not set.
if python_bin_env_val is None:
    print('Environment variable ' + PYTHON_BIN_ENV + ' is not set.')
    quit(1)

cli_cmd = ' '.join(sys.argv)
print('Executed with: ' + cli_cmd)
print('Executed by: ' + current_py_bin)

if not os.path.samefile(current_py_bin, python_bin_env_val):
    print('Switching executing binary...')
    os.system(python_bin_env_val + ' ' + cli_cmd)
    quit()

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
