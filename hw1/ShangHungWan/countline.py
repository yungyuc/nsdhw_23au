#!/usr/bin/env bash

custom_python_version_var="PYTHON_BIN"
custom_python_interpreter="$(eval echo "\$$custom_python_version_var")"

if [ -z "$custom_python_interpreter" ]; then
    echo "Custom Python interpreter is not set."
    exit 1
fi

exec "$custom_python_interpreter" - << EOF "$@"

import sys
import os.path


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

EOF
