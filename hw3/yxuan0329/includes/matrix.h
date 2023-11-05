#ifndef MATRIX_H
#define MATRIX_H

#include <bits/stdc++.h>
#include <vector>
#include <cstddef>

using namespace std;

class Matrix {
public:
    Matrix();
    ~Matrix();

    Matrix(size_t, size_t, vector<double> const);
    Matrix(size_t, size_t);

    double operator() (size_t, size_t) const;
    double& operator() (size_t, size_t);
    bool operator==(const Matrix&) const;
    bool operator!=(const Matrix&) const;

    Matrix transpose() const;

    const size_t& n_row() const;
    const size_t& n_col() const;

    double *m_buffers() const { return m_buffer; }

private:
    size_t m_row;
    size_t m_col;
    double *m_buffer;
};

#endif