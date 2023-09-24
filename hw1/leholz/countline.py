#!/usr/bin/env python
from distutils.spawn import find_executable
import sys
import os.path

PYTHON_BIN_ENV = 'PYTHON_BIN'
python_bin_env_val = os.getenv(PYTHON_BIN_ENV)

current_py_bin = sys.executable
# Test ENV variable, return with error, if variable is not set.
if python_bin_env_val is None:
    print('Environment variable ' + PYTHON_BIN_ENV + ' is not set.')
    quit(1)

py_path = find_executable(python_bin_env_val)

if py_path is None:
    print('Python binary specified by ' + python_bin_env_val + ' can not be resolved.')
    quit(4)

if not os.path.exists(py_path):
    print('Python binary specified by ' + python_bin_env_val + ' is not available.')
    quit(2)

if not os.access(py_path, os.X_OK):
    print('Python binary specified by ' + python_bin_env_val + ' is not executable.')
    quit(3)

cli_cmd = ' '.join(sys.argv)
print('Executed with: ' + cli_cmd)
print('Executed by: ' + current_py_bin)

if not os.path.samefile(current_py_bin, py_path):
    print('Switching executing binary...')
    os.system(py_path + ' ' + cli_cmd)
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
