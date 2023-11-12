#include <stdexcept>
#include <algorithm>
#include <mkl/mkl.h>
// #include <mkl/mkl_lapack.h>
// #include <mkl/mkl_lapacke.h>
#include "matrix.h"

Matrix::Matrix(int nrow, int ncol) : nrow_(nrow), ncol_(ncol) {
    data_ = new double[nrow * ncol] {0};
}

Matrix::Matrix(const Matrix &m) : nrow_(m.nrow_), ncol_(m.ncol_) {
    data_ = new double[nrow_ * ncol_];
    for (int i = 0; i < nrow_ * ncol_; i++) {
        data_[i] = m.data_[i];
    }
}

Matrix::~Matrix() {
    delete[] data_;
}

double Matrix::operator()(int i, int j) const {
    return data_[i * ncol_ + j];
}

double &Matrix::operator()(int i, int j) {
    return data_[i * ncol_ + j];
}

int Matrix::nrow() const {
    return nrow_;
}

int Matrix::ncol() const {
    return ncol_;
}

bool Matrix::operator==(const Matrix &m) const {
    if (nrow_ != m.nrow_ || ncol_ != m.ncol_) {
        return false;
    }
    for (int i = 0; i < nrow_ * ncol_; i++) {
        if (data_[i] != m.data_[i]) {
            return false;
        }
    }
    return true;
}


Matrix multiply_naive(const Matrix &mat1, const Matrix &mat2) {
    if (mat1.ncol() != mat2.nrow()) {
        throw std::invalid_argument("Matrix dimensions do not match");
    }
    Matrix result(mat1.nrow(), mat2.ncol());
    for (int i = 0; i < mat1.nrow(); i++) {
        for (int j = 0; j < mat2.ncol(); j++) {
            double sum = 0;
            for (int k = 0; k < mat1.ncol(); k++) {
                sum += mat1(i, k) * mat2(k, j);
            }
            result(i, j) = sum;
        }
    }
    return result;
}

Matrix multiply_tile(const Matrix &mat1, const Matrix &mat2, int tile_size = 32) {
    int N = mat1.nrow();
    int M = mat1.ncol();
    int K = mat2.ncol();
    if (mat1.ncol() != mat2.nrow()) {
        throw std::invalid_argument("Matrix dimensions do not match");
    }


    Matrix result(mat1.nrow(), mat2.ncol());
    for (int i = 0; i < N; i += tile_size) {
        int i_end = std::min(i + tile_size, N);
        for (int k = 0; k < K; k += tile_size) {
            int k_end = std::min(k + tile_size, K);
            for (int j = 0; j < M; j += tile_size) {
                int j_end = std::min(j + tile_size, M);

                for (int i0 = i; i0 < i_end; i0++) {
                    for (int k0 = k; k0 < k_end; k0++) {
                        for (int j0 = j; j0 < j_end; j0++) {
                            result.data_[i0 * K + j0] += mat1.data_[i0 * M + k0] * mat2.data_[k0 * K + j0];
                        }
                    }
                }

            }
        }
    }


    return result;
}

Matrix multiply_mkl(const Matrix &mat1, const Matrix &mat2) {
    if (mat1.ncol() != mat2.nrow()) {
        throw std::invalid_argument("Matrix dimensions do not match");
    }
    Matrix result(mat1.nrow(), mat2.ncol());
    cblas_dgemm(
        CblasRowMajor,
        CblasNoTrans,
        CblasNoTrans,
        mat1.nrow(),
        mat2.ncol(),
        mat1.ncol(),
        1.0,
        mat1.data_,
        mat1.ncol(),
        mat2.data_,
        mat2.ncol(),
        0.0,
        result.data_,
        result.ncol()
    );
    return result;
}