#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>

using namespace std; 

class Matrix {

public:

    Matrix(int rows, int cols) : m_rows(rows), m_cols(cols), m_data(new double[rows*cols]){
        memset(m_data, 0, sizeof(double)*rows*cols);
    }

    Matrix(const Matrix &m) : m_cols(m.ncol()), m_rows(m.nrow()){
        m_data = new double[m_rows*m_cols];

        for (int i = 0; i < m_rows; i++){
            for (int j = 0; j < m_cols; j++){
                m_data[i*m_cols+j] = m(i, j);
            }
        }
    }

    ~Matrix(){
        delete[] m_data;
    }

    double &operator()(int x, int y){
        return m_data[y*m_cols+x];
    }

    double operator()(int x, int y) const{
        return m_data[y*m_cols+x];
    }

    bool operator ==(const Matrix &m) const{
        if (m_rows != m.nrow() || m_cols != m.ncol()){
            return false;
        }
        for (int i = 0; i < m_rows; i++){
            for (int j = 0; j < m_cols; j++){
                if ((*this)(i, j) != m(i, j)){
                    return false;
                }
            }
        }
        return true;
    }

    int nrow() const{ 
        return m_rows; 
    }

    int ncol() const{ 
        return m_cols;
    }

    double* data() const{
        return m_data;
    }

private:
    int m_rows;
    int m_cols;
    double *m_data;
};