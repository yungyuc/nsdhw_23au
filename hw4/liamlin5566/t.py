import _matrix



def make_matrix(size):
    mat1 = _matrix.Matrix(size,size)
    mat2 = _matrix.Matrix(size,size)
    mat3 = _matrix.Matrix(size,size)

    for it in range(size):
        for jt in range(size):
            mat1[it, jt] = it * size + jt + 1
            mat2[it, jt] = it * size + jt + 1
            mat3[it, jt] = 0

    return mat1, mat2, mat3



mat1, mat2, mat3, *_ = make_matrix(2)
print(mat1)
print(mat2)
print(mat3)
print(_matrix.bytes())
print(_matrix.allocated())
