#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
// https://dboyliao.medium.com/pybind11-%E5%85%A5%E9%96%80%E7%8E%A9%E6%A8%82%E6%89%8B%E8%A8%98-9da22f6193f2
#include <stdexcept>
#include <vector>
#include <atomic>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <mkl.h>

#include "item.hpp"
using namespace std;

static MyAllocator<double> Myalloc;
class Matrix {

public:
    // initialize
    size_t numRows = 0;
    size_t numCols = 0;
    // double* m_buffer = nullptr;

    Matrix(size_t nrow, size_t ncol): numRows(nrow), numCols(ncol), _data(Myalloc)
    {
        _data.resize(nrow * ncol);
    }

    size_t nrow() const { return numRows; }
    size_t ncol() const { return numCols; }

    // set data & get data
    double operator()(size_t row, size_t col) const
    {
        return _data[row * numCols + col];
    }
    double &operator()(size_t row, size_t col)
    {
        return _data[row * numCols + col];
    }

    // compare
    bool operator==(const Matrix &other) const
    {
        return equal(_data.begin(), _data.end(), other._data.begin());
    }

    vector<double, MyAllocator<double>> _data;

};

size_t bytes() {return Myalloc.counter.bytes();}
size_t allocated() {return Myalloc.counter.allocated(); }
size_t deallocated() {return Myalloc.counter.deallocated();}

Matrix multiply_naive(Matrix const & mat1, Matrix const & mat2) {
    if (mat1.ncol() != mat2.nrow()) {
        throw out_of_range("Dimension wrong!!!!!");;
    }

    Matrix result(mat1.nrow(), mat2.ncol());

    for (size_t i_outer = 0; i_outer < result.nrow(); i_outer++) {
        for (size_t k_outer = 0; k_outer < result.ncol(); k_outer++) {
            double value = 0;
            for (size_t j_inner = 0; j_inner < mat1.ncol(); j_inner++) {
                value += mat1(i_outer, j_inner) * mat2(j_inner, k_outer);
            }
            result(i_outer, k_outer) = value;
        }
    }

    return result;
}

Matrix multiply_tile(const Matrix &mat1, const Matrix &mat2, size_t tile_size) {
    if (mat1.ncol() != mat2.nrow()) {throw out_of_range("Dimension wrong!!!!!");}
    Matrix result(mat1.nrow(), mat2.ncol());
    for (size_t i_outer = 0; i_outer < mat1.nrow(); i_outer += tile_size) {
        size_t i_outer_max = min(i_outer + tile_size, mat1.nrow());
        for (size_t j_outer = 0; j_outer < mat2.ncol(); j_outer += tile_size) {
            size_t j_outer_max = min(j_outer + tile_size, mat2.ncol());
            for (size_t k_outer = 0; k_outer < mat1.ncol(); k_outer += tile_size) {
                size_t k_outer_max = min(k_outer + tile_size, mat1.ncol());
                for (size_t j_inner = j_outer; j_inner < j_outer_max; j_inner++) {
                    for (size_t i_inner = i_outer; i_inner < i_outer_max; i_inner++) {
                        for (size_t k_inner = k_outer; k_inner < k_outer_max; k_inner++) {
                            result(i_inner, j_inner) += mat1(i_inner, k_inner) * mat2(k_inner, j_inner);
    }}}}}}
    return result;
}


Matrix multiply_mkl(const Matrix &mat1, const Matrix &mat2) {
    if (mat1.ncol() != mat2.nrow()) {throw out_of_range("Dimension wrong!!!!!");}
    Matrix result(mat1.nrow(), mat2.ncol());
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                mat1.nrow(), mat2.ncol(), mat1.ncol(),
                1.0, mat1._data.data(), mat1.ncol(),
                mat2._data.data(), mat2.ncol(),
                0.0, result._data.data(), mat2.ncol());

    return result;
}

PYBIND11_MODULE(_matrix, m)
{
    m.doc() = "_maxtrix function";    
    m.def("multiply_naive", &multiply_naive);  
    m.def("multiply_mkl", &multiply_mkl);     
    m.def("multiply_tile", &multiply_tile);     
    m.def("bytes", &bytes);
    m.def("allocated", &allocated);
    m.def("deallocated", &deallocated);
    pybind11::class_<Matrix>(m, "Matrix") 
        .def(pybind11::init<size_t, size_t>()) 
        .def_property_readonly("ncol", &Matrix::ncol)
        .def("__setitem__", [](Matrix &mat, pair<size_t, size_t> row_col, double val) {mat(row_col.first, row_col.second) = val;})
        .def("__getitem__", [](Matrix &mat, pair<size_t, size_t> row_col){return mat(row_col.first, row_col.second);})
        .def("__eq__", &Matrix::operator==)
        .def_property_readonly("nrow", &Matrix::nrow);
}