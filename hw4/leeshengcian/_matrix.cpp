#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

#include <bits/stdc++.h>
#include <cblas.h>

#include '_matrix.h'

Matrix multiply_naive(Matrix &mat1, Matrix &mat2)
{
    Matrix res(mat1.nrow(), mat2.ncol());
    for (size_t k = 0; k < mat2.ncol(); k++)
        for (size_t i = 0; i < mat1.nrow(); i++)
            for (size_t j = 0; j < mat1.ncol(); j++)
                res(i, k) += mat1(i, j) * mat2(j, k);

    return res;
}

Matrix multiply_tile(Matrix &mat1, Matrix &mat2, size_t tsize)
{
    Matrix res(mat1.nrow(), mat2.ncol());

    for (size_t ti = 0; ti < mat1.nrow(); ti += tsize)
        for (size_t tj = 0; tj < mat1.ncol(); tj += tsize)
            for (size_t tk = 0; tk < mat2.ncol(); tk += tsize)
                for (size_t i = ti; i < std::min(ti + tsize, mat1.nrow()); i++)
                    for (size_t k = tk; k < std::min(tk + tsize, mat2.ncol()); k++)
                    {
                        double tmp = 0.0;
                        for (size_t j = tj; j < std::min(tj + tsize, mat1.ncol()); j++)
                            tmp += mat1(i, j) * mat2(j, k);
                        res(i, k) += tmp;
                    }
    return res;
}

Matrix multiply_mkl(Matrix &mat1, Matrix &mat2)
{
    Matrix res(mat1.nrow(), mat2.ncol());
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                mat1.nrow(), mat2.ncol(), mat1.ncol(),
                1.0, mat1.data(), mat1.ncol(), mat2.data(), mat2.ncol(), 0.0, res.data(), mat2.ncol());

    return res;
}

PYBIND11_MODULE(_matrix, m)
{
    m.doc() = "Matrix-multiplication";
    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_tile", &multiply_tile);
    m.def("multiply_mkl", &multiply_mkl);
    m.def("bytes", &bytes);
    m.def("allocated", &allocated);
    m.def("deallocated", &deallocated);

    pybind11::class_<Matrix>(m, "Matrix")
        .def(pybind11::init<size_t, size_t>())
        .def(pybind11::self == pybind11::self)
        .def("__getitem__", &Matrix::getitem)
        .def("__setitem__", &Matrix::setitem)
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol);
}