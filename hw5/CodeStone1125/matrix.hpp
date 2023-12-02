#include <stdexcept>
#include <vector>
#include <mkl.h>

using namespace std;

class Matrix {

public:
    size_t m_nrow = 0;
    size_t m_ncol = 0;
    double* m_buffer = nullptr;

    Matrix(size_t nrow, size_t ncol): m_nrow(nrow), m_ncol(ncol){
        size_t nelement = nrow * ncol;

        m_buffer = new double[nelement];}
    void reset_buffer(size_t nrow, size_t ncol){
        if(m_buffer) {delete[] m_buffer;}
         m_buffer = new double[nrow * ncol];}
    size_t nrow() const { return m_nrow; }
    size_t ncol() const { return m_ncol; }
    double  operator() (size_t row, size_t col) const{return m_buffer[row*m_ncol + col];}
    double &operator() (size_t row, size_t col){return m_buffer[row*m_ncol + col];}

    bool operator==(const Matrix &other) const
    {
        for (size_t i = 0; i < m_nrow; i++){for (size_t j = 0; j < m_ncol; j++){
                size_t index = i * m_ncol + j;
                if (m_buffer[index] != other.m_buffer[index]) return false;}}
        return true;
    }  
};

// Matrix multiply_naive
Matrix multiply_naive(Matrix const & mat1, Matrix const & mat2) {
    if (mat1.ncol() != mat2.nrow()) {throw out_of_range("wrong dimensions!!!");}
    Matrix ret(mat1.nrow(), mat2.ncol());
    for (size_t i = 0; i < ret.nrow(); i++){
        for (size_t k = 0; k < ret.ncol(); k++){
            double v = 0;
            for (size_t j = 0; j < mat1.ncol(); j++) {v += mat1(i,j) * mat2(j,k);}
            ret(i,k) = v;
        }
    }

    return ret;
}

// Matrix multiply_tile
Matrix multiply_tile(const Matrix &mat1, const Matrix &mat2,  size_t tile_size) {
    if (mat1.ncol() != mat2.nrow()){throw out_of_range("wrong dimensions!!!");}
    Matrix ret(mat1.nrow(), mat2.ncol());
    for (size_t i = 0; i < mat1.nrow(); i += tile_size){
        for (size_t j = 0; j < mat2.ncol(); j += tile_size)
            for (size_t k = 0; k < mat1.ncol(); k += tile_size){
                for(size_t l = i; l < min((i + tile_size), mat1.nrow()); l++)
                    for(size_t m = j; m < min((j + tile_size), mat2.ncol()); m++){
                        for(size_t n = k; n < min((k + tile_size), mat1.ncol()); n++){ret(l, m) += mat1(l, n) * mat2(n, m);}
    }}}
    return ret;
}

Matrix multiply_mkl(Matrix const & mat1, Matrix const & mat2){
    if (mat1.ncol() != mat2.nrow()) {throw out_of_range("wrong dimensions!!!");}
    else{
        Matrix ret(mat1.nrow(), mat2.ncol());
        size_t m = mat1.nrow();
        size_t n = mat2.ncol();
        size_t k = mat1.ncol();
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, k, 1.0, mat1.m_buffer, k, mat2.m_buffer, n, 0.0, ret.m_buffer, n);
        return ret;
    }
}
