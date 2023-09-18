#!/usr/bin/env python3

import sys
from pathlib import Path


def count_line(filename: str):
    path = Path(filename)
    if not path.exists():
        sys.stdout.write(f"{filename} not found\n")
        return

    with path.open() as fobj:
        lines = fobj.readlines()

    sys.stdout.write(f"{len(lines)} lines in {filename}\n")


def main(argv: list[str] = sys.argv):
    match argv:
        case [_]:
            sys.stdout.write("missing file name\n")
        case [_, fname]:
            count_line(fname)
        case _:
            sys.stdout.write("only one argument is allowed\n")


if __name__ == "__main__":
    main()
