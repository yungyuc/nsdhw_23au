#!/usr/bin/env bash

tmp=$(mktemp)
cat > $tmp << EOF

import sys
import os.path

def main():
    if len(sys.argv) < 2:
        sys.stdout.write("missing file name\n")
    elif len(sys.argv) > 2:
        sys.stdout.write("only one argument is allowed\n")
    else:
        fname = sys.argv[1]
        if os.path.exists(fname):
            with open(fname) as fobj:
                lines = fobj.readlines()
            sys.stdout.write("{} lines in {}\n".format(len(lines), fname))
        else:
            sys.stdout.write("{} not found\n".format(fname))


if __name__ == "__main__":
    main()

EOF

type ${PYTHON_BIN} > /dev/null 2>&1
ret=$?
if test $ret != 0
then
    echo exec: ${PYTHON_BIN}: not found 1>&2
    exit 1
fi
${PYTHON_BIN} $tmp $@
rm $tmp
