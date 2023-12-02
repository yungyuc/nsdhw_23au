#pragma once
#include <cstddef>
#include <mkl.h>
#include <stdexcept>
#include <vector>

#include <pybind11/pybind11.h>
#include <iomanip>
#include <iostream>
class Matrix {
public:
    Matrix(size_t nrow, size_t ncol)
        : _nrow(nrow), _ncol(ncol) {
        _reset_buffer(nrow, ncol);
    }


    Matrix(Matrix const& other)
        : _nrow(other._nrow), _ncol(other._ncol) {
        _reset_buffer(other._nrow, other._ncol);
        for (size_t i = 0; i < _nrow; ++i) {
            for (size_t j = 0; j < _ncol; ++j) {
                (*this)(i, j) = other(i, j);
            }
        }
    }
    Matrix(Matrix&& other)
        : _nrow(other._nrow), _ncol(other._ncol) {
        _reset_buffer(0, 0);
        std::swap(_nrow, other._nrow);
        std::swap(_ncol, other._ncol);
        std::swap(_buffer, other._buffer);
    }
    double& operator[](std::pair<size_t, size_t> idx) const {
        if (idx.first > _nrow || idx.second > _ncol) {
            throw std::out_of_range("Out");
        }
        return _buffer[_index(idx.first, idx.second)];
    }

    double operator()(size_t row, size_t col) const {
        if (row > _nrow || col > _ncol) {
            throw std::out_of_range("Out");
        }
        return _buffer[_index(row, col)];
    }
    double& operator()(size_t row, size_t col) {
        if (row > _nrow || col > _ncol) {
            throw std::out_of_range("Out");
        }
        return _buffer[_index(row, col)];
    }

    bool operator==(const Matrix& other) const {
        if (other.nrow() != _nrow && other.ncol() != _ncol) {
            throw std::length_error("row != nrow or col != ncol");
        }
        for (size_t i = 0; i < _nrow; i++) {
            for (size_t j = 0; j < _ncol; j++) {
                if (_buffer[_index(i, j)] != other(i, j))
                    return false;
            }
        }
        return true;
    }

    size_t nrow() const {
        return _nrow;
    }

    size_t ncol() const {
        return _ncol;
    }

    size_t size() const {
        return _nrow * _ncol;
    }

    double* get_buffer() const {
        return _buffer;
    }

    void _reset_buffer(size_t nrow, size_t ncol) {
        if (_buffer)
            delete[] _buffer;
        const size_t nelement = nrow * ncol;
        if (nelement)
            _buffer = new double[nelement];
        else
            _buffer = nullptr;
        _nrow = nrow;
        _ncol = ncol;
    }

    size_t _index(size_t row, size_t col) const {
        return row * _ncol + col;
    }

    size_t _nrow = 0, _ncol = 0;
    double* _buffer = nullptr;
};

Matrix multiply_naive(Matrix const& mat1, Matrix const& mat2) {
    if (mat1.ncol() != mat2.nrow()) {
        throw std::out_of_range("mat1.col != mat2.row");
    }
    Matrix ret(mat1.nrow(), mat2.ncol());
    for (size_t i = 0; i < ret.nrow(); i++) {
        for (size_t k = 0; k < ret.ncol(); k++) {
            for (size_t j = 0; j < mat1.ncol(); j++) {
                ret(i, k) += mat1(i, j) * mat2(j, k);
            }
        }
    }
    return ret;
}
Matrix multiply_tile(Matrix& mat1, Matrix& mat2, size_t tsize) {
    if (mat1.ncol() != mat2.nrow()) {
        throw std::out_of_range("the number of first matrix column differs from that of second matrix row");
    }
    Matrix ret(mat1.nrow(), mat2.ncol());

    for (size_t row = 0; row < mat1.nrow(); row += tsize)
        for (size_t col = 0; col < mat2.ncol(); col += tsize)
            for (size_t inner = 0; inner < mat1.ncol(); inner += tsize)
                for (size_t i = row; i < std::min(mat1.nrow(), row + tsize); i++)
                    for (size_t j = col; j < std::min(mat2.ncol(), col + tsize); j++)
                        for (size_t k = inner; k < std::min(mat1.ncol(), inner + tsize); k++)
                            ret(i, j) += mat1(i, k) * mat2(k, j);
    return ret;
}

Matrix multiply_mkl(Matrix const& mat1, Matrix const& mat2) {
    if (mat1.ncol() != mat2.nrow()) {
        throw std::out_of_range("mat1.col != mat2.row");
    }
    Matrix ret(mat1.nrow(), mat2.ncol());
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                mat1.nrow(), mat2.ncol(), mat1.ncol(), 1.0, mat1._buffer, mat1.ncol(),
                mat2._buffer, mat2.ncol(), 0.0, ret._buffer, ret.ncol());
    return ret;
}