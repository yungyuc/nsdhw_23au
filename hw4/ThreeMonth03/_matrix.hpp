#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <vector>
#include <mkl.h>
#include "_allocator.hpp"

static CustomAllocator<double> MyAllocator;

class Matrix{
public:
    Matrix(size_t row, size_t col);
    Matrix(Matrix const &mat);
    double operator()(size_t row, size_t col) const;
    double &operator()(size_t row, size_t col);
    bool operator==(Matrix const &mat2) const;
    double *data();
    double const *data() const;
    size_t nrow() const;
    size_t ncol() const;

private:
    size_t m_nrow;
    size_t m_ncol;
    std::vector<double, CustomAllocator<double>> m_buffer;
};

inline size_t bytes(){ 
    return MyAllocator.counter.bytes(); 
}
inline size_t allocated(){ 
    return MyAllocator.counter.allocated();
}
inline size_t deallocated(){
    return MyAllocator.counter.deallocated();
}

Matrix multiply_tile(Matrix const& mat1, Matrix const& mat2, size_t tsize);
Matrix multiply_naive(Matrix const& mat1, Matrix const& mat2);
Matrix multiply_mkl(Matrix const& mat1, Matrix const& mat2);

#endif