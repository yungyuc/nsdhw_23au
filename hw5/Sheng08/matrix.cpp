#include <mkl.h>

#include "matrix.hpp"

using namespace std;

Matrix multiply_naive(Matrix const& mat1, Matrix const& mat2) {
    Matrix ret(mat1.nrow(), mat2.ncol());

    for (size_t i = 0; i < ret.nrow(); i++) {
        for (size_t j = 0; j < ret.ncol(); j++) {
            // double val = 0;
            for (size_t k = 0; k < mat1.ncol(); k++) {
                // val += mat1(i, k) * mat2(k, j);
                ret(i, j) += mat1(i, k) * mat2(k, j);
            }
            // ret(i, j) = val;
        }
    }

    return ret;
}

Matrix multiply_tile(const Matrix& mat1, const Matrix& mat2, size_t tsize) {
    // Initialize the result matrix with appropriate dimensions.
    Matrix ret(mat1.nrow(), mat2.ncol());

    // Iterate over blocks (tiles) of the first matrix rows.
    for (size_t ti = 0; ti < mat1.nrow(); ti += tsize) {
        // Iterate over blocks (tiles) of the second matrix columns.
        for (size_t tj = 0; tj < mat2.ncol(); tj += tsize) {
            // Iterate over blocks (tiles) matching the current rows of the first matrix
            // and columns of the second matrix.
            for (size_t tk = 0; tk < mat1.ncol(); tk += tsize) {
                // Perform multiplication for the current block.
                for (size_t i = ti; i < min(ti + tsize, mat1.nrow()); ++i) {
                    for (size_t j = tj; j < min(tj + tsize, mat2.ncol()); ++j) {
                        for (size_t k = tk; k < min(tk + tsize, mat1.nrow()); ++k) {
                            ret(i, j) += mat1(i, k) * mat2(k, j);
                        }
                    }
                }
            }
        }
    }

    return ret;
}

Matrix multiply_mkl(Matrix& mat1, Matrix& mat2) {
    Matrix ret(mat1.nrow(), mat2.ncol());

    cblas_dgemm(
        CblasRowMajor, /* const CBLAS_LAYOUT Layout */
        CblasNoTrans,  /* const CBLAS_TRANSPOSE transa */
        CblasNoTrans,  /* const CBLAS_TRANSPOSE transb */
        mat1.nrow(),   /* const MKL_INT m */
        mat2.ncol(),   /* const MKL_INT n */
        mat1.ncol(),   /* const MKL_INT k */
        1.0,           /* const double alpha */
        mat1.data(),   /* const double *a */
        mat1.ncol(),   /* const MKL_INT lda */
        mat2.data(),   /* const double *b */
        mat2.ncol(),   /* const MKL_INT ldb */
        0.0,           /* const double beta */
        ret.data(),    /* double * c */
        ret.ncol()     /* const MKL_INT ldc */
    );

    return ret;
}