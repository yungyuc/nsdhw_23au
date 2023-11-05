import sys
import timeit

def benchmark():
    setup = '''
import _matrix
size = 1000
mat1 = _matrix.Matrix(size, size)
mat2 = _matrix.Matrix(size, size)

for i in range(size):
    for j in range(size):
        mat1[i, j] = 2*i*i + j + 2.0
        mat2[i, j] = 2*j*j + i + 1.0
'''

    naive = timeit.Timer('_matrix.multiply_naive(mat1, mat2)', setup=setup)
    tile_16 = timeit.Timer('_matrix.multiply_tile(mat1, mat2, 16)', setup=setup)
    mkl = timeit.Timer('_matrix.multiply_mkl(mat1, mat2)', setup=setup)

    repeat_times = 5

    with open('performance.txt', 'w') as f:
        f.write(f"Start multiply_naive (repeat={repeat_times}), take min = ")
        naiveTime = min(naive.repeat(repeat=repeat_times, number=1))
        f.write(f"{naiveTime} seconds\n")

        f.write(f"Start multiply_tile (repeat={repeat_times}), take min = ")
        tileTime_16 = min(tile_16.repeat(repeat=repeat_times, number=1))
        f.write(f"{tileTime_16} seconds\n")
        
        f.write(f"Start multiply_mkl (repeat={repeat_times}), take min = ")
        mklTime = min(mkl.repeat(repeat=repeat_times, number=1))
        f.write(f"{mklTime} seconds\n")

        f.write(f"\nTile size=16 speed-up over naive: {tileTime_16 / naiveTime}x\n")
        f.write(f"MKL speed-up over naive: {mklTime / naiveTime}x\n")

if __name__ == '__main__':
    benchmark()