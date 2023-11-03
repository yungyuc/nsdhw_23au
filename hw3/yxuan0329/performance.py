import sys
import timeit
import _matrix

def benchmark():
    setup = '''
    import _matrix
    size = 1000
    mat1 = _matrix.Matrix(size, size)
    mat2 = _matrix.Matrix(size, size)

    for i in range (size):
        for j in range(size):
            mat1[i, j] = 2 * i * i + j + 2.0
            mat2[i, j] = 2 * j * j + i + 2.0
    '''

    naive = timeit.Timer('_matrix.multiply_naive(mat1, mat2)', setup=setup)
    tile_16 = timeit.Timer('_matrix.multiply_tile(mat1, mat2, 16)', setup=setup)
    mkl = timeit.Timer('_matrix.multiply_mkl(mat1, mat2)', setup=setup)

    repeat_times = 5

    with open('performance.txt', 'w') as f:
        f.write('Start multiply_naive (repeat=5), take min = ')
        naiveTime = min(naive.repeat(repeat=repeat_times, number=1))
        f.write('{} seconds\n'.format(naiveTime))

        f.write('Start multiply_tile (repeat=5) tile size=16, take min = ')
        tileTime_16 = min(tile_16.repeat(repeat=repeat_times, number=1))
        f.write('{} seconds\n'.format(tileTime_16))
        
        f.write('Start multiply_mkl (repeat=5), take min = ')
        mklTime = min(mkl.repeat(repeat=repeat_times, number=1))
        f.write('{} seconds\n'.format(mklTime))

        f.write('Tile size=16 speed-up over naive: {} x\n'.format(tileTime_16 / naiveTime))
        f.write('MKL speed-up over naive: {} x\n'.format(mklTime / naiveTime))

if __name__ == '__main__':
    benchmark()