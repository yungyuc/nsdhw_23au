#!/usr/bin/env python3

import sys
import timeit

import _matrix


class Writer:
    def __init__(self, streams):
        self.streams = streams

    def write(self, msg: str) -> None:
        for stream in self.streams:
            stream.write(msg)


def benchmark() -> None:
    setup = """
import _matrix

size = 1024

mat1 = _matrix.Matrix(size,size)
mat2 = _matrix.Matrix(size,size)

for it in range(size):
    for jt in range(size):
        mat1[it, jt] = it * size + jt + 1
        mat2[it, jt] = it * size + jt + 1
"""

    naive = timeit.Timer(
        "_matrix.multiply_naive(mat1, mat2)", setup=setup)
    tile_16 = timeit.Timer(
        "_matrix.multiply_tile(mat1, mat2, 16)", setup=setup)
    tile_32 = timeit.Timer(
        "_matrix.multiply_tile(mat1, mat2, 32)", setup=setup)
    tile_64 = timeit.Timer(
        "_matrix.multiply_tile(mat1, mat2, 64)", setup=setup)
    tile_128 = timeit.Timer(
        "_matrix.multiply_tile(mat1, mat2, 128)", setup=setup)
    mkl = timeit.Timer(
        "_matrix.multiply_mkl(mat1, mat2)", setup=setup)

    repeat = 5

    with open("performance.txt", "w") as fobj:
        w = Writer([sys.stdout, fobj])

        w.write(f"Start multiply_naive (repeat={repeat}), take min = ")
        naivesec = minsec = min(naive.repeat(repeat=repeat, number=1))
        w.write(f"{minsec} seconds\n")

        w.write(
            f"Start multiply_tile (tile_size=16) (repeat={repeat}), "
            f"take min = ")
        tilesec_16 = minsec = min(tile_16.repeat(repeat=repeat, number=1))
        w.write(f"{minsec} seconds\n")

        w.write(
            f"Start multiply_tile (tile_size=32) (repeat={repeat}), "
            f"take min = ")
        tilesec_32 = minsec = min(tile_32.repeat(repeat=repeat, number=1))
        w.write(f"{minsec} seconds\n")

        w.write(
            f"Start multiply_tile (tile_size=64) (repeat={repeat}), "
            f"take min = ")
        tilesec_64 = minsec = min(tile_64.repeat(repeat=repeat, number=1))
        w.write(f"{minsec} seconds\n")

        w.write(
            f"Start multiply_tile (tile_size=128) (repeat={repeat}), "
            f"take min = ")
        tilesec_128 = minsec = min(tile_128.repeat(repeat=repeat, number=1))
        w.write(f"{minsec} seconds\n")

        w.write(
            f"Start multiply_mkl (repeat={repeat}), "
            f"take min = ")
        mklsec = minsec = min(mkl.repeat(repeat=repeat, number=1))
        w.write(f"{minsec} seconds\n")

        w.write("\n")

        w.write("Tile (tile_size= 16) speed-up over naive: %g x\n"
            % (naivesec / tilesec_16))
        w.write("Tile (tile_size= 32) speed-up over naive: %g x\n"
            % (naivesec / tilesec_32))
        w.write("Tile (tile_size= 64) speed-up over naive: %g x\n"
            % (naivesec / tilesec_64))
        w.write("Tile (tile_size=128) speed-up over naive: %g x\n"
            % (naivesec / tilesec_128))
        w.write("MKL                  speed-up over naive: %g x\n"
            % (naivesec / mklsec))


if __name__ == "__main__":
    benchmark()
