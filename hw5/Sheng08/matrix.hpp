#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <vector>

using namespace std;

class Matrix {

public:
    Matrix()
        : m_nrow(0), m_ncol(0) {}

    Matrix(size_t nrow, size_t ncol) /* constructor */
        : m_nrow(nrow), m_ncol(ncol) {
        m_buffer.resize(m_nrow * m_ncol);
    }

    ~Matrix() { /* destructor */
        m_buffer.clear();
    }

    Matrix(const Matrix &other) /* copy constructor */
        : m_nrow(other.nrow()), m_ncol(other.ncol()), m_buffer(other.m_buffer) {
    }

    Matrix(Matrix &&other) /* move constructor */
        : m_nrow(other.nrow()), m_ncol(other.ncol()), m_buffer(std::move(other.m_buffer)) {
    }

    Matrix &operator=(Matrix const &other) { /* copy */
        if (this == &other) {
            return *this;
        }

        m_nrow = other.nrow();
        m_ncol = other.ncol();
        m_buffer = other.m_buffer;

        return *this;
    }

    Matrix &operator=(Matrix &&other) { /* move */
        if (this == &other) {
            return *this;
        }

        m_nrow = other.nrow();
        m_ncol = other.ncol();
        m_buffer = other.m_buffer;

        return *this;
    }

    double operator()(size_t row, size_t col) const {
        return m_buffer[row * m_ncol + col];
    }

    double &operator()(size_t row, size_t col) {
        return m_buffer[row * m_ncol + col];
    }

    bool operator==(const Matrix &other) const {
        return m_buffer == other.m_buffer;
    }

    size_t nrow() const { return m_nrow; }

    size_t ncol() const { return m_ncol; }

    double buffer(size_t i) const { return m_buffer[i]; }

    double *data() { return &m_buffer[0]; }

private:
    size_t m_nrow;
    size_t m_ncol;
    vector<double> m_buffer;
};

Matrix multiply_naive(Matrix const & , Matrix const& );
Matrix multiply_tile(const Matrix & , const Matrix & , size_t );
Matrix multiply_mkl(Matrix& , Matrix& );

#endif