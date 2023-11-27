#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
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
    // Matrix & operator=(std::vector<double> const & vec)
    // {
    //     if (size() != vec.size())
    //     {
    //         throw std::out_of_range("number of elements mismatch");
    //     }

    //     size_t k = 0;
    //     for (size_t i=0; i<m_nrow; ++i)
    //     {
    //         for (size_t j=0; j<m_ncol; ++j)
    //         {
    //             (*this)(i,j) = vec[k];
    //             ++k;
    //         }
    //     }

    //     return *this;
    // }

    // Matrix(Matrix && other)
    //   : m_nrow(other.m_nrow), m_ncol(other.m_ncol)
    // {
    //     reset_buffer(0, 0);
    //     std::swap(m_nrow, other.m_nrow);
    //     std::swap(m_ncol, other.m_ncol);
    //     std::swap(m_buffer, other.m_buffer);
    // }

    // double *val_addr() const {
    //     return &(this->m_buffer[0]);
    // }

    
    // Matrix & operator=(Matrix && other)
    // {
    //     if (this == &other) { return *this; }
    //     reset_buffer(0, 0);
    //     std::swap(m_nrow, other.m_nrow);
    //     std::swap(m_ncol, other.m_ncol);
    //     std::swap(m_buffer, other.m_buffer);
    //     return *this;
    // }

    // ~Matrix()
    // {
    //     reset_buffer(0, 0);
    // }

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
    // size_t nrow() const { return m_nrow; }
    // size_t ncol() const { return m_ncol; }

    // size_t size() const { return m_nrow * m_ncol; }

    // double buffer(size_t i) const {
    //     if (i < m_nrow * m_ncol) {
    //         return m_buffer[i];
    //     } else {
    //         return 0.0;
    //     }
    // }

    // compare
    bool operator==(const Matrix &other) const
    {
        return equal(_data.begin(), _data.end(), other._data.begin());
    }

    vector<double, MyAllocator<double>> _data;

    // std::vector<double> buffer_vector() const
    // {
    //     std::vector<double> buffer;
    //     buffer.reserve(m_nrow * m_ncol);

    //     for (size_t i = 0; i < m_nrow; ++i) {
    //         for (size_t j = 0; j < m_ncol; ++j) {
    //             buffer.push_back(m_buffer[index(i, j)]);
    //         }
    //     }

    //     return buffer;
    // }




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