import pytest
import math
import _matrix
import random
import numpy as np
import timeit

def test_matrix_creation():
    rows = random.randint(1, 1000)
    cols = random.randint(1, 1000)
    mat = _matrix.Matrix(rows, cols)
    assert mat.nrow == rows
    assert mat.ncol == cols

def test_matrix_get_set_value():
    rows = random.randint(1, 1000)
    cols = random.randint(1, 1000)
    mat = _matrix.Matrix(rows, cols)
    
    # Generate random row and column indices
    row_index = random.randint(0, rows - 1)
    col_index = random.randint(0, cols - 1)
    
    # Generate a random value
    random_value = random.uniform(100.0, 10000.0)
    
    mat.setvalue(row_index, col_index, random_value)
    assert mat.getvalue(row_index, col_index) == random_value

def test_matrix_buffer_vector():
    rows = 2
    cols = 3
    # Generate random data for the matrix
    mat_data = [random.uniform(100.0, 10000.0) for _ in range(rows * cols)]
    mat = _matrix.Matrix(rows, cols, mat_data)

    # Get the buffer vector
    buffer = mat.buffer_vector()

    # Check if each element in the buffer is equal to its corresponding element in the data
    for i in range(rows * cols):
        assert buffer[i] == mat_data[i]

def test_matrix_getitem_setitem():
    rows, cols = 100, 1000
    mat = _matrix.Matrix(rows, cols)
    
    # Set a random value at a random position
    random_row = random.randint(0, rows - 1)
    random_col = random.randint(0, cols - 1)
    random_value = random.uniform(100.0, 10000.0)
    
    mat[(random_row, random_col)] = random_value
    
    # Verify that the value was set correctly
    assert mat[(random_row, random_col)] == random_valu

def test_matrix_multiplication():
    tolerance = 1e-6 
    # Generate random data for mat1 and mat2
    mat1_data = np.random.rand(100, 100).flatten().tolist()
    mat2_data = np.random.rand(100, 100).flatten().tolist()

    mat1 = _matrix.Matrix(100, 100, mat1_data)
    mat2 = _matrix.Matrix(100, 100, mat2_data)
    
    result = _matrix.multiply_naive(mat1, mat2)
    
    # Calculate the expected result using numpy
    expected_result = np.dot(np.array(mat1_data).reshape(100, 100), np.array(mat2_data).reshape(100, 100))
    
    # Check each element of the result matrix
    for i in range(100):
        for j in range(100):
            assert math.isclose(result[(i, j)], expected_result[i][j], rel_tol=tolerance)


if __name__ == '__main__':
    pytest.main()
