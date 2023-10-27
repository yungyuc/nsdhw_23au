#include <iostream>
#include <stdio.h>
#include <stdexcept>
#include <math.h>
#include <mkl.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <pybind11/operators.h>

#include "_matrix.h"

Matrix multiply_naive(Matrix const &mat1, Matrix const &mat2){
    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }

    Matrix ret(mat1.nrow(), mat2.ncol());

    for (size_t i=0; i<ret.nrow(); ++i)
    {
        for (size_t k=0; k<ret.ncol(); ++k)
        {
            double v = 0;
            for (size_t j=0; j<mat1.ncol(); ++j)
            {
                v += mat1(i,j) * mat2(j,k);
            }
            ret(i,k) = v;
        }
    }

    return ret;
}

Matrix multiply_tile(const Matrix &mat1, const Matrix &mat2, size_t blocksize)
{
    Matrix ret(mat1.nrow(), mat2.ncol());

    for (size_t blocki = 0; blocki < mat1.nrow(); blocki += blocksize)
    {
        size_t i_bound = std::min(blocki + blocksize, mat1.nrow());
        for (size_t blockj = 0; blockj < mat2.ncol(); blockj += blocksize)
        {
            size_t j_bound = std::min(blockj + blocksize, mat2.ncol());
            for (size_t blockk = 0; blockk < mat1.ncol(); blockk += blocksize)
            {
                size_t k_bound = std::min(blockk + blocksize, mat1.ncol());
                for (size_t k = blockk; k < k_bound; k++)
                {
                    for (size_t i = blocki; i < i_bound; i++)
                    {
                        for (size_t j = blockj; j < j_bound; j++)
                        {
                            ret(i, j) += mat1(i, k) * mat2(k, j);
                        }
                    }
                }
            }
        }
    }

    return ret;
}

Matrix multiply_mkl(Matrix const &mat1, Matrix const &mat2){
    Matrix ret(mat1.nrow(), mat2.ncol());

    const size_t M = mat1.nrow();
    const size_t N = mat2.ncol();
    const size_t K = mat1.ncol();
    const double alpha = 1.0, beta = 0.0;

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, M, N, K, alpha, mat1, M, mat2, N, beta, ret, N);

    return ret;
}


PYBIND11_MODULE(_matrix, m)
{
    m.doc() = "Matrix-multiplication function test and performance.";
    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_tile", &multiply_tile);
    m.def("multiply_mkl", &multiply_mkl);

    py::class_<Matrix>(m, "Matrix")
        .def(py::init<>())
        .def(py::init<size_t, size_t>())
        .def(py::self == py::self)
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol)
        .def("__getitem__", &Matrix::getvalue)
        .def("__setitem__", &Matrix::setvalue);
}