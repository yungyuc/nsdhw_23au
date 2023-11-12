#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <utility>
#include <mkl.h>
#include <algorithm>

class Matrix {

public:
    Matrix(size_t nrow, size_t ncol);
    Matrix(const Matrix &mat);
    Matrix(size_t nrow, size_t ncol, std::vector<double> const & vec);
    ~Matrix();
    Matrix(Matrix && other);
    Matrix & operator=(Matrix const & mat);
    Matrix operator+(Matrix const & other);
    Matrix & operator=(Matrix && other);
    Matrix & operator=(std::vector<double> const & vec);
    double   operator() (size_t row, size_t col) const;
    double & operator() (size_t row, size_t col);
    bool operator==(Matrix const & mat) const;

    double * data() const;
    size_t nrow() const;
    size_t ncol() const;
    size_t size() const { return m_nrow * m_ncol; }
    double buffer(size_t i) const { return m_buffer[i]; }
    std::vector<double> buffer_vector() const
    {
        return std::vector<double>(m_buffer, m_buffer+size());
    }

private:
    void reset_buffer(size_t nrow, size_t ncol);
    size_t index(size_t row, size_t col) const{return m_ncol*row + col;}
    size_t m_nrow = 0;
    size_t m_ncol = 0;
    double * m_buffer = nullptr;
};



Matrix multiply_tile(Matrix const& mat1, Matrix const& mat2, size_t tsize);
Matrix multiply_naive(Matrix const& mat1, Matrix const& mat2);
Matrix multiply_mkl(Matrix const& mat1, Matrix const& mat2);

// Matrix operator*(Matrix const & mat1, Matrix const & mat2);
// std::ostream & operator<<(std::ostream & os, std::vector<double> const & vec);
// std::vector<double> operator*(Matrix const & mat, std::vector<double> const & vec);


#endif
