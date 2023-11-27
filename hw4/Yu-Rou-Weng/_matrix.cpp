#include <mkl/mkl.h>
#include <mkl/mkl_cblas.h>
#include <mkl/mkl_lapack.h>
#include <mkl/mkl_lapacke.h>
#include "pybind11/operators.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include <bits/stdc++.h>

#include "_matrix.hpp"
#define MATRIX_H
using namespace std;
namespace py = pybind11;

Matrix multiply_naive(Matrix &mat1, Matrix &mat2)
{
    if (mat1.ncol() != mat2.nrow())
    {
        exit(1);
    }

    Matrix ret(mat1.nrow(), mat2.ncol());

    for (size_t i = 0; i < mat1.nrow(); i++)
    {
        for (size_t j = 0; j < mat2.ncol(); j++)
        {
            for (size_t k = 0; k < mat1.ncol(); k++)
            {
                ret(i, j) += mat1(i, k) * mat2(k, j);
            }
        }
    }
    return ret;
}

Matrix multiply_tile(Matrix const &mat1, Matrix const &mat2, size_t const tile_size)
{
    if (mat1.ncol() != mat2.nrow())
    {
        exit(1);
    }

    Matrix ret(mat1.nrow(), mat2.ncol());
    for (size_t i = 0; i < mat1.nrow(); i += tile_size)
    {
        for (size_t k = 0; k < mat1.ncol(); k += tile_size)
        {
            for (size_t j = 0; j < mat2.ncol(); j += tile_size)
            {
                for (size_t ti = i; ti < min(i + tile_size, mat1.nrow());
                     ti++)
                {
                    for (size_t tk = k; tk < min(k + tile_size, mat1.ncol());
                         tk++)
                    {
                        for (size_t tj = j; tj < min(j + tile_size, mat2.ncol()); tj++)
                        {
                            ret(ti, tj) += mat1(ti, tk) * mat2(tk, tj);
                        }
                    }
                }
            }
        }
    }
    return ret;
}

Matrix multiply_mkl(Matrix &mat1, Matrix &mat2)
{
    if (mat1.ncol() != mat2.nrow())
    {
        exit(1);
    }

    mkl_set_num_threads(1);

    Matrix ret(mat1.nrow(), mat2.ncol());

    cblas_dgemm(CblasRowMajor,
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
                ret.data(),
                ret.ncol());

    return ret;
}

PYBIND11_MODULE(_matrix, m)
{
    m.doc() = "matrix-matrix multiplication";

    py::class_<Matrix>(m, "Matrix")
        .def(py::init<size_t, size_t>())
        .def("__getitem__", [](const Matrix &mat, pair<size_t, size_t> index)
             { return mat(index.first, index.second); })
        .def("__setitem__", [](Matrix &mat, pair<size_t, size_t> index, double value)
             { mat(index.first, index.second) = value; })
        .def("__eq__", &Matrix::operator==)
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol);
    m.def("multiply_naive", &multiply_naive, "multiply_naive");
    m.def("multiply_tile", &multiply_tile, "multiply_tile");
    m.def("multiply_mkl", &multiply_mkl, "multiply_mkl");

    m.def("bytes", bytes, "bytes used");
    m.def("allocated", allocated, "bytes allocated");
    m.def("deallocated", deallocated, "bytes deallocated");
}