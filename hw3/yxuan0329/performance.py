import sys
import timeit

def benchmark():
    setup = '''
import _matrix
size = 10
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
        f.write("multiply_naive (repeat=5), \n")
        naiveTime = min(naive.repeat(repeat=repeat_times, number=1))
        f.write(f"min = {naiveTime} seconds\n\n")

        f.write("multiply_tile (repeat=5), tile size=16, \n")
        tileTime_16 = min(tile_16.repeat(repeat=repeat_times, number=1))
        f.write(f"min = {tileTime_16} seconds\n\n")
        
        f.write("multiply_mkl (repeat=5), \n")
        mklTime = min(mkl.repeat(repeat=repeat_times, number=1))
        f.write(f"min = {mklTime} seconds\n\n")

        f.write(f"\nTile size=16 speed-up over naive: {tileTime_16 / naiveTime}x\n")
        f.write(f"MKL speed-up over naive: {mklTime / naiveTime}x\n")

if __name__ == '__main__':
    benchmark()