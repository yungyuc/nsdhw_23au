#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <iostream>
#include <vector>
#include <mkl.h>
#include <utility>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

class Matrix {

public:
    Matrix(size_t nrow, size_t ncol) : m_nrow(nrow), m_ncol(ncol) 
    {
        m_buffer = new double[nrow * ncol];
        for (size_t i = 0; i < nrow * ncol; i++) {
            m_buffer[i] = 0;
        }
    }
    Matrix(const Matrix &mat) : m_nrow(mat.m_nrow), m_ncol(mat.m_ncol)
    {
        m_buffer = new double[m_nrow * m_ncol];
        for (size_t i = 0; i < m_nrow * m_ncol; i++) {
            m_buffer[i] = mat.m_buffer[i];
        }
    }
    // Matrix(size_t nrow, size_t ncol, std::vector<double> const & vec);
    ~Matrix()
    {
        delete[] m_buffer;
    }
    Matrix & operator=(Matrix const & mat)
    {
        if (this != &mat) {
            delete[] m_buffer;
            m_nrow = mat.m_nrow;
            m_ncol = mat.m_ncol;
            m_buffer = new double[m_nrow * m_ncol];
            for (size_t i = 0; i < m_nrow * m_ncol; i++) {
                m_buffer[i] = mat.m_buffer[i];
            }
        }
        return *this;
    }
    double   operator() (size_t row, size_t col) const { return m_buffer[row * m_ncol + col]; }
    double & operator() (size_t row, size_t col) { return m_buffer[row * m_ncol + col]; }
    bool operator==(Matrix const & mat) const
    {
        if (m_nrow != mat.m_nrow || m_ncol != mat.m_ncol) {
            return false;
        }
        for (size_t i = 0; i < m_nrow * m_ncol; i++) {
            if (m_buffer[i] != mat.m_buffer[i]) {
                return false;
            }
        }
        return true;
    }

    double * data() const { return m_buffer; }
    size_t nrow() const { return m_nrow; }
    size_t ncol() const { return m_ncol; }

private:

    size_t m_nrow;
    size_t m_ncol;
    double * m_buffer;
};

Matrix multiply_tile(Matrix const& mat1, Matrix const& mat2, size_t tsize);
Matrix multiply_naive(Matrix const& mat1, Matrix const& mat2);
Matrix multiply_mkl(Matrix const& mat1, Matrix const& mat2);

#endif