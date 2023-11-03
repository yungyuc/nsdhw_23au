#include <iostream>
#include <cstddef>
#include "TileHelper.h"

using namespace std;

Matrix TileHelper::padMat(size_t blksize, const Matrix& originalMatrix) {
    size_t row, col;
    row = originalMatrix.n_row() + ((blksize - (originalMatrix.n_row() % blksize)) % blksize);
    col = originalMatrix.n_col() + ((blksize - (originalMatrix.n_col() % blksize)) % blksize);

    Matrix new_mat(row, col);
    for (size_t i=0; i<row; i++) {
        for (size_t j=0; j<col; j++) {
            if (i >= originalMatrix.n_row() || j >= originalMatrix.n_col())
                new_mat(i, j) = 0;
            else new_mat(i, j) = originalMatrix(i, j);
        }
    }
    return new_mat;
}

