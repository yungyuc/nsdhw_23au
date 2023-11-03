#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstddef>

#include "matrix.h"

using namespace std;

class Matrix {
public:
    Matrix() {
        this->m_row = 0;
        this->m_col = 0;
        this->m_buffer = NULL;
    }
    
    Matrix(size_t row, size_t col, vector<double> const value) {
        this->m_row = row;
        this->m_col = col;
        size_t nelement = row * col;
        this->m_buffer = new double[nelement];
        int cnt = 0;
        // this->m_buffer = (double*)malloc(sizeof(double) * value.size());
        // memset(this->m_buffer, 0, sizeof(double) * value.size());

        for (const double&v : value) {
            this->m_buffer[cnt++] = v;
        }
    }


    Matrix(size_t row, size_t col) {
        this->m_row = row;
        this->m_col = col;
        size_t nelement = row * col;
        this->m_buffer = new double[nelement];
    }

    ~Matrix() {
        this->m_row = 0, this->m_col = 0;
        delete[] this->m_buffer;
    }

    Matrix transpose() const {
        int row = this->m_row, col = this->m_col; 
        Matrix new_mat(col, row);

        for (int i=0; i<col; i++) {
            for (int j=0; j<row; j++) {
                size_t id = this->m_col * i + j;
                new_mat(j, i) = this->m_buffer[id];
            }
        }
        return new_mat;
    }

    double& operator() (size_t row, size_t col) const {
        return m_buffer[m_col * row + col];
    }

    bool operator == (const Matrix rhs) const {
        if (this->m_col != rhs.m_col) return false;
        if (this->m_row != rhs.m_row) return false;

        int row = this->m_row, col = this->m_col;
        for (int i=0; i<col; i++) {
            for (int j=0; j<row; j++) {
                size_t id = this->m_col * i + j;
                if (this->m_buffer[id] != rhs(i, j)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator != (const Matrix rhs) const {
        return !(*this == rhs);
    }

    const size_t& n_row() const {
        return this->m_row;
    }

    const size_t& n_col() const {
        return this->m_col;
    }

private:
    size_t m_row, m_col;
    double* m_buffer;
};

