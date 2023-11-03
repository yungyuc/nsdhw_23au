import sys
import timeit

# The python module that wraps the matrix code.
import _matrix

class Writer:

    def __init__(self, streams):

        self.streams = streams

    def write(self, msg):

        for stream in self.streams:

            stream.write(msg)


def benchmark():

    setup = '''
import _matrix

size = 1000

mat1 = _matrix.Matrix(size,size)
mat2 = _matrix.Matrix(size,size)

for it in range(size):
    for jt in range(size):
        mat1[it, jt] = it * size + jt + 1
        mat2[it, jt] = it * size + jt + 1
'''

    naive = timeit.Timer('_matrix.multiply_naive(mat1, mat2)', setup=setup)
    tile_16 = timeit.Timer('_matrix.multiply_tile(mat1, mat2, 16)', setup=setup)
    tile_32 = timeit.Timer('_matrix.multiply_tile(mat1, mat2, 32)', setup=setup)
    tile_64 = timeit.Timer('_matrix.multiply_tile(mat1, mat2, 64)', setup=setup)
    tile_128 = timeit.Timer('_matrix.multiply_tile(mat1, mat2, 128)', setup=setup)
    mkl = timeit.Timer('_matrix.multiply_mkl(mat1, mat2)', setup=setup)

    repeat = 5

    with open('performance.txt', 'w') as fobj:

        w = Writer([sys.stdout, fobj])

        w.write(f'Start multiply_naive (repeat={repeat}), take min = ')
        naivesec = minsec = min(naive.repeat(repeat=repeat, number=1))
        w.write(f'{minsec} seconds\n')

        tilesec_16 = minsec = min(tile_16.repeat(repeat=repeat, number=1))
        w.write(f'Start multiply_tile tile size=16 (repeat={repeat}), take min = ')
        w.write(f'{minsec} seconds\n')

        w.write(f'Start multiply_tile tile size=32 (repeat={repeat}), take min = ')
        tilesec_32 = minsec = min(tile_32.repeat(repeat=repeat, number=1))
        w.write(f'{minsec} seconds\n')

        w.write(f'Start multiply_tile tile size=64 (repeat={repeat}), take min = ')
        tilesec_64 = minsec = min(tile_64.repeat(repeat=repeat, number=1))
        w.write(f'{minsec} seconds\n')

        w.write(f'Start multiply_tile tile size=128 (repeat={repeat}), take min = ')
        tilesec_128 = minsec = min(tile_128.repeat(repeat=repeat, number=1))
        w.write(f'{minsec} seconds\n')

        w.write(f'Start multiply_mkl (repeat={repeat}), take min = ')
        mklsec = minsec = min(mkl.repeat(repeat=repeat, number=1))
        w.write(f'{minsec} seconds\n\n\n')

        w.write('tile size=16 speed-up over naive: %g x\n' % (naivesec/tilesec_16))
        w.write('tile size=32 speed-up over naive: %g x\n' % (naivesec/tilesec_32))
        w.write('tile size=64 speed-up over naive: %g x\n' % (naivesec/tilesec_64))
        w.write('tile size=128 speed-up over naive: %g x\n' % (naivesec/tilesec_128))
        w.write('MKL speed-up over naive: %g x\n' % (naivesec/mklsec))

if __name__ == '__main__':
    benchmark()
