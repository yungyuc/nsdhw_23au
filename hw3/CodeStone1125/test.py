#!/usr/bin/python3
import os
os.environ['LD_LIBRARY_PATH'] = '/home/williechu1125/intel/compilers_and_libraries_2019.1.144/linux/mkl/lib/intel64_lin:' + os.environ.get('LD_LIBRARY_PATH', '')
ld_library_path = os.environ.get('LD_LIBRARY_PATH', 'LD_LIBRARY_PATH 环境变量未设置')
print(f'LD_LIBRARY_PATH 的值是：{ld_library_path}')

import ma03_matrix_matrix
import pytest
import numpy as np
import math
import time

# Create matrices A and B
mat1 = ma03_matrix_matrix.Matrix(2, 3, [[1, 2, 3], [4, 5, 6]])
mat2 = ma03_matrix_matrix.Matrix(3, 2, [[1, 2], [3, 4], [5, 6]])


# Multiply using Naive algorithm
print(">>> Naive algo for A(2x3) times B(3x2):")
print("matrix A (2x3):")
print(mat1)
print("matrix B (3x2):")
print(mat2)
mat3 = ma03_matrix_matrix.multiply_naive(mat1, mat2)
print("result matrix C (2x2) = AB:")
print(mat3)

# Multiply using Tiling algorithm
print(">>> Tiling algo for A(2x3) times B(3x2):")
mat4 = ma03_matrix_matrix.multiply_tile(mat1, mat2, 4)
print("result matrix C (2x2) = AB:")
print(mat4)

# Multiply using DGEMM algorithm
print(">>> DGEMM for A(2x3) times B(3x2):")
mat5 = ma03_matrix_matrix.multiply_mkl(mat1, mat2)
print("result matrix C (2x2) = AB:")
print(mat5)
