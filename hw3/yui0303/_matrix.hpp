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
    Matrix(size_t nrow, size_t ncol);
    Matrix(const Matrix &mat);
    Matrix(size_t nrow, size_t ncol, std::vector<double> const & vec);
    ~Matrix();
    Matrix & operator=(Matrix const & mat);
    double   operator() (size_t row, size_t col) const;
    double & operator() (size_t row, size_t col);
    bool operator==(Matrix const & mat) const;
    // friend std::ostream & operator<<(std::ostream & os, Matrix const & mat);

    double * data() const;
    size_t nrow() const;
    size_t ncol() const;

private:

    size_t m_nrow;
    size_t m_ncol;
    double * m_buffer;
};



Matrix multiply_tile(Matrix const& mat1, Matrix const& mat2, size_t tsize);
Matrix multiply_naive(Matrix const& mat1, Matrix const& mat2);
Matrix multiply_mkl(Matrix const& mat1, Matrix const& mat2);

// Matrix operator*(Matrix const & mat1, Matrix const & mat2);
// std::ostream & operator<<(std::ostream & os, std::vector<double> const & vec);
// std::vector<double> operator*(Matrix const & mat, std::vector<double> const & vec);


#endif
