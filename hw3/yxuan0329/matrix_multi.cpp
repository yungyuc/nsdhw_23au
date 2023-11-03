#include "matrix.h"
#include "TileHelper.h"

#include <iostream>
#include <cstddef>
#include <stdexcept>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include <mkl/mkl.h>

namespace py = pybind11;

Matrix multiply_naive(const Matrix& lhs, const Matrix& rhs) {
    if (lhs.n_col() != rhs.n_row()) {
        throw std::invalid_argument("Invalid shape size");
    }

    int r = lhs.n_row(), c = rhs.n_col(), n = lhs.n_col();
    
    Matrix result(r, c);

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            for (int k = 0; k < n; ++k) {
                result(i, j) += lhs(i, k) * rhs(k, j);
            }
        }
    }
    return result;
}

Matrix multiply_tile(const Matrix& lhs, const  Matrix& rhs, size_t blocksize) {
    if (lhs.n_col() != rhs.n_row()) {
        throw std::invalid_argument("Invalid shape size");
    }

    TileHelper helper;

    // Padding 0 so that the row and col can be divisible by block size
    Matrix fakeLhs, fakeRhs;

    fakeLhs = helper.padMatrix(blocksize, lhs);
    fakeRhs = helper.padMatrix(blocksize, rhs);

    Matrix result(lhs.n_row(), rhs.n_col()), fakeResult(fakeLhs.n_row(), fakeRhs.n_col());

    size_t lhsRowOffset, lhsColOffset;
    size_t rhsRowOffset, rhsColOffset;

    for (lhsRowOffset = 0; lhsRowOffset < fakeLhs.n_row(); lhsRowOffset += blocksize) {
        for (rhsColOffset = 0; rhsColOffset < fakeRhs.n_col(); rhsColOffset += blocksize) {
            for (size_t cnt = 0; cnt < fakeLhs.n_col(); cnt += blocksize) {
                lhsColOffset = cnt;
                rhsRowOffset = cnt;

                // Parse matrix
                Matrix lhsInBlock(blocksize, blocksize), rhsInBlock(blocksize, blocksize);
                for (size_t i = 0; i < blocksize; ++i) {
                    for (size_t j = 0; j < blocksize; ++j) {
                        lhsInBlock(i, j) = fakeLhs(lhsRowOffset + i, lhsColOffset + j);
                    }
                }

                for (size_t i = 0; i < blocksize; ++i) {
                    for (size_t j = 0; j < blocksize; ++j) {
                        rhsInBlock(i, j) = fakeRhs(rhsRowOffset + i, rhsColOffset + j);
                    }
                }

                rhsInBlock = rhsInBlock.transpose();

                // Store back to result
                size_t resultRowOffset = lhsRowOffset, resultColOffset = rhsColOffset;

                for (size_t i = 0; i < blocksize; ++i) {
                    for (size_t j = 0; j < blocksize; ++j) {
                        double v = 0;
                        for (size_t k = 0; k < blocksize; ++k) {
                            v += lhsInBlock(i, k) * rhsInBlock(j, k);
                        }
                        fakeResult(resultRowOffset + i, resultColOffset + j) += v;
                    }
                }
            }
        }
    }

    for (size_t i = 0; i < result.n_row(); ++i) {
        for (size_t j = 0; j < result.n_col(); ++j) {
            result(i, j) = fakeResult(i, j);
        }
    }

    return result;
}


Matrix multiply_mkl(const Matrix& mat1, const Matrix& mat2)
{
    if (mat1.n_col() != mat2.n_row()) {
        throw std::invalid_argument("Invalid shape size");
    }
    Matrix ret(mat1.n_row(), mat2.n_col());

    cblas_dgemm(
        CblasRowMajor
        , CblasNoTrans
        , CblasNoTrans
        , mat1.n_row()
        , mat2.n_col()
        , mat1.n_col()
        , 1.0
        , mat1.m_buffer
        , mat1.n_col()
        , mat2.m_buffer
        , mat2.n_col()
        , 0.0
        , ret.m_buffer
        , ret.n_col()
    );

    return ret;
}

PYBIND11_MODULE(_matrix, m) {
  m.doc() = "Matrix multiplication function implementation";      // module doc string
  m.def("multiply_naive", &multiply_naive);
  m.def("multiply_tile", &multiply_tile);
  m.def("multiply_mkl", &multiply_mkl);
  py::class_<Matrix>(m, "Matrix")
    .def(py::init<size_t, size_t>())
    .def_property_readonly("nrow", [](Matrix& m){ return m.n_row(); })
    .def_property_readonly("ncol", [](Matrix& m){ return m.n_col(); })
    .def(py::self == py::self) 
    .def(py::self != py::self) 
    .def("__getitem__", [](Matrix& m, std::pair<size_t, size_t> idx) { return m(idx.first, idx.second); })
    .def("__setitem__", [](Matrix& m, std::pair<size_t, size_t> idx, double val) { m(idx.first, idx.second) = val; });
}