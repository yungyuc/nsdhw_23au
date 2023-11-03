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
            mat1[i, j] = i * size + j + 1
            mat2[i, j] = i * size + j + 1 
    '''

    naive = timeit.Timer('_matrix.multiply_naive(mat1, mat2)', setup=setup)
    tile_16 = timeit.Timer('_matrix.multiply_tile(mat1, mat2, 16)', setup=setup)
    tile_32 = timeit.Timer('_matrix.multiply_tile(mat1, mat2, 32)', setup=setup)
    tile_64 = timeit.Timer('_matrix.multiply_tile(mat1, mat2, 64)', setup=setup)
    tile_128 = timeit.Timer('_matrix.multiply_tile(mat1, mat2, 128)', setup=setup)
    mkl = timeit.Timer('_matrix.multiply_mkl(mat1, mat2)', setup=setup)

    repeat_times = 5

    with open('performance.txt', 'w') as f:
        f.write('Start multiply_naive (repeat=5), take min = ')
        naiveTime = min(naive.repeat(repeat=repeat_times, number=1))
        f.write('{} seconds\n'.format(naiveTime))

        f.write('Start multiply_tile (repeat=5) tile size=16, take min = ')
        tileTime_16 = min(tile_16.repeat(repeat=repeat_times, number=1))
        f.write('{} seconds\n'.format(tileTime_16))

        f.write('Start multiply_tile (repeat=5) tile size=32, take min = ')
        tileTime_32 = min(tile_32.repeat(repeat=repeat_times, number=1))
        f.write('{} seconds\n'.format(tileTime_32))

        f.write('Start multiply_tile (repeat=5) tile size=64, take min = ')
        tileTime_64 = min(tile_64.repeat(repeat=repeat_times, number=1))
        f.write('{} seconds\n'.format(tileTime_64))

        f.write('Start multiply_tile (repeat=5) tile size=128, take min = ')
        tileTime_128 = min(tile_128.repeat(repeat=repeat_times, number=1))
        f.write('{} seconds\n'.format(tileTime_128))
        
        f.write('Start multiply_mkl (repeat=5), take min = ')
        mklTime = min(mkl.repeat(repeat=repeat_times, number=1))
        f.write('{} seconds\n'.format(mklTime))

        f.write('Tile size=16 speed-up over naive: {} x\n'.format(tileTime_16 / naiveTime))
        f.write('Tile size=32 speed-up over naive: {} x\n'.format(tileTime_32 / naiveTime))
        f.write('Tile size=64 speed-up over naive: {} x\n'.format(tileTime_64 / naiveTime))
        f.write('Tile size=128 speed-up over naive: {} x\n'.format(tileTime_128 / naiveTime))
        f.write('MKL speed-up over naive: {} x\n'.format(mklTime / naiveTime))

if __name__ == '__main__':
    benchmark()