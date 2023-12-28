#include "matrix.hpp"
#include <stdexcept>
#include <algorithm>
#include <mkl.h>
#include <cassert>
#include <vector>


Matrix::Matrix(int nrow, int ncol) : nrow_(nrow), ncol_(ncol) {
    data_ = std::vector<double>(nrow * ncol, 0);
    data_.shrink_to_fit();
}

Matrix::Matrix(const Matrix &m) : nrow_(m.nrow_), ncol_(m.ncol_), data_(move(m.data_)) {}

Matrix::Matrix(Matrix &&m) : nrow_(m.nrow_), ncol_(m.ncol_), data_(move(m.data_)) {}

Matrix::~Matrix() {
    // data_.clear();
    std::vector<double>().swap(data_);
}

double Matrix::operator()(int i, int j) const {
    assert(i < nrow_ && j < ncol_);
    return data_[i * ncol_ + j];
}

double &Matrix::operator()(int i, int j) {
    assert(i < nrow_ && j < ncol_);
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

double *Matrix::data() {
    return data_.data();
}

const double *Matrix::data() const {
    return data_.data();
}

Matrix multiply_naive(const Matrix &mat1, const Matrix &mat2) {
    if (mat1.ncol() != mat2.nrow()) {
        throw std::invalid_argument("Matrix dimensions do not match");
    }
    Matrix result(mat1.nrow(), mat2.ncol());
    for (int i = 0; i < mat1.nrow(); i++) {
        for (int j = 0; j < mat2.ncol(); j++) {
            for (int k = 0; k < mat1.ncol(); k++) {
                result(i, j) += mat1(i, k) * mat2(k, j);
            }
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
                            result.data()[i0 * K + j0] += mat1.data()[i0 * M + k0] * mat2.data()[k0 * K + j0];
                            // result(i0, j0) += mat1(i0, k0) * mat2(k0, j0);
                        }
                    }
                }

            }
        }
    }


    return result;
}

Matrix multiply_mkl( Matrix &mat1,  Matrix &mat2) {
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
        mat1.data(),
        mat1.ncol(),
        mat2.data(),
        mat2.ncol(),
        0.0,
        result.data(),
        result.ncol()
    );
    return result;
}