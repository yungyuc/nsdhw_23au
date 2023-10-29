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
using namespace std;
namespace py = pybind11;

bool operator==(Matrix const &mat1, Matrix const &mat2)
{
    if (mat1.ncol() != mat2.ncol() || mat1.nrow() != mat2.ncol())
        return false;

    for (size_t i = 0; i < mat1.nrow(); i++)
    {
        for (size_t j = 0; j < mat1.ncol(); j++)
        {
            if (mat1(i, j) != mat2(i, j))
                return false;
        }
    }

    return true;
}

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
        const size_t base1 = i * mat1.ncol();
        for (size_t k=0; k<ret.ncol(); ++k)
        {
            for (size_t j = 0; j < mat1.ncol(); ++j)
            {
                v += mat1.m_buffer[base1 + j] * mat2.m_buffer[j * ret.ncol() + k];
            }
            ret.m_buffer[base1 + k] = v;
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

Matrix multiply_mkl(Matrix &mat1, Matrix &mat2){
    Matrix ret(mat1.nrow(), mat2.ncol());

    const size_t M = mat1.nrow();
    const size_t N = mat2.ncol();
    const size_t K = mat1.ncol();
    const double alpha = 1.0, beta = 0.0;

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, M, N, K, alpha, mat1.val_addr(), M, mat2.val_addr(), N, beta, ret.val_addr(), N);

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