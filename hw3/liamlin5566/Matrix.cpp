#include <cstring>
#include <stdexcept>

#include <mkl/mkl.h>
#include <mkl/mkl_lapack.h>
#include <mkl/mkl_lapacke.h>
#include <pybind11/pybind11.h>

#include "Matrix.h"


Matrix::Matrix(Matrix const & other): m_nrow(other.m_nrow), m_ncol(other.m_ncol)
{
    reset_buffer(other.m_nrow, other.m_ncol);
    for (std::size_t i=0; i<m_nrow; ++i)
    {
        for (std::size_t j=0; j<m_ncol; ++j)
        {
            (*this)(i,j) = other(i,j);
        }
    }
}

void Matrix::reset_buffer(std::size_t nrow, std::size_t ncol)
{
    if (m_buffer) { delete[] m_buffer; }
    const std::size_t nelement = nrow * ncol;
    if (nelement) 
    {
        m_buffer = new double[nelement]; 
        std::memset(m_buffer, 0, nrow * ncol* sizeof(double)); 
    }
    else         
    { 
        m_buffer = nullptr; 
    }
    m_nrow = nrow;
    m_ncol = ncol;
}


 Matrix & Matrix::operator=(Matrix const & other)
{
    if (this == &other) { return *this; }
    if (m_nrow != other.m_nrow || m_ncol != other.m_ncol)
    {
        reset_buffer(other.m_nrow, other.m_ncol);
    }
    for (std::size_t i=0; i<m_nrow; ++i)
    {
        for (std::size_t j=0; j<m_ncol; ++j)
        {
            (*this)(i,j) = other(i,j);
        }
    }
    return *this;
}


bool Matrix::operator==(Matrix const &other) const
{
    if (this == &other) {return true; }

    if (m_nrow != other.m_nrow || m_ncol != other.m_ncol)
    {
        return false;
    }

    //compare each element
    for (std::size_t i=0; i<m_nrow; i++)
    {
        for (std::size_t j=0; j<m_ncol; j++)
        {
            if ((*this)(i,j) != other(i,j))
            {   
                //std::cout << i << " " << j << " " << (*this)(i,j) << " "<<  other(i,j) << std::endl;
                return false;
            }
        }
    }
    return true;
}


std::string Matrix::toString() const
{
    std::string output = "";
    for (std::size_t i=0; i<m_nrow; i++)
    {
        for (std::size_t j=0; j<m_ncol; j++)
        {
            output = output + std::to_string((*this)(i, j)) + " ";
        }
        if (i < m_nrow-1)
            output = output + "\n";
    }
    //std::cout << output << std::endl;
    return output;
}


Matrix multiply_naive(Matrix const &mat1, Matrix const &mat2)
{
    if (mat1.ncol() != mat2.nrow())
        throw std::out_of_range("Mismatch, two matrix cannot be multiplied");
    
    Matrix ret(mat1.nrow(), mat2.ncol());

    for (std::size_t i = 0; i < mat1.nrow(); i++)
    {
        for (std::size_t j = 0; j < mat2.ncol(); j++)
        {
            for (std::size_t k = 0; k < mat1.ncol(); k++)
                ret(i, j) += mat1(i, k) * mat2(k, j);
        }
    }

    return ret;
}



// Matrix multiply_tile(Matrix const &mat1, Matrix const &mat2, std::size_t tsize)
// {
//     if (mat1.ncol() != mat2.nrow())
//         throw std::out_of_range("Mismatch, two matrix cannot be multiplied");
    
//     Matrix ret(mat1.nrow(), mat2.ncol());

//     for (std::size_t i = 0; i < mat1.nrow(); i+=tsize)
//     {
//         std::size_t it_bound = std::min(i+tsize, mat1.nrow());
        
//         for (std::size_t j = 0; j < mat2.ncol(); j+=tsize)
//         {
//             std::size_t jt_bound = std::min(j+tsize, mat2.ncol());
            
//             for (std::size_t k = 0; k < mat1.ncol(); k+=tsize)
//             {
//                 std::size_t kt_bound = std::min(k+tsize, mat1.ncol());
                
//                 for (std::size_t it = i; it < it_bound; it++)
//                 {
//                     for (std::size_t jt = j; jt < jt_bound ; jt++)
//                     {
//                         for (std::size_t kt = k; kt < kt_bound; kt++)
//                             ret(it, jt) += mat1(it, kt) * mat2(kt, jt);
//                     }
//                 }
//             }       
//         }
//     }

//     return ret;
// }

Matrix multiply_tile(const Matrix &mat1, const Matrix &mat2, size_t blocksize)
{
    Matrix ret(mat1.nrow(), mat2.ncol());

    for (size_t blocki = 0; blocki < mat1.nrow(); blocki += blocksize)
    {
        size_t i_bound = std::min(blocki + blocksize, mat1.nrow());
        for (size_t blockj = 0; blockj < mat2.ncol(); blockj += blocksize)
        {
            size_t j_bound = std::min(blockj + blocksize, mat2.ncol());
            for (size_t blockk = 0; blockk < mat1.ncol(); blockk += blocksize)
            {
                size_t k_bound = std::min(blockk + blocksize, mat1.ncol());
                for (size_t k = blockk; k < k_bound; k++)
                {
                    for (size_t i = blocki; i < i_bound; i++)
                    {
                        for (size_t j = blockj; j < j_bound; j++)
                        {
                            ret(i, j) += mat1(i, k) * mat2(k, j);
                        }
                    }
                }
            }
        }
    }

    return ret;
}


Matrix multiply_mkl(const Matrix& mat1, const Matrix& mat2)
{

    Matrix ret(mat1.nrow(), mat2.ncol());
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
                mat1.nrow(), mat2.ncol(), mat1.ncol(), 1.0, 
                mat1.data(), mat1.ncol(), mat2.data(), mat2.ncol(), 
                0.0, ret.data(), mat2.ncol());

    return ret;
}

namespace py = pybind11;

PYBIND11_MODULE(_matrix, m) 
{
    m.doc() = "Matirx class and Matrix multiplication func.";

   
    py::class_<Matrix>(m, "Matrix")
        .def(py::init<std::size_t, std::size_t>()) 
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol)
        .def_property_readonly("size", &Matrix::size)
        .def("__eq__", [](const Matrix &x, const Matrix &y) { return x == y; })
        .def("__setitem__", [](Matrix &self, std::pair<std::size_t, std::size_t> idx, double val) {
            self(idx.first, idx.second) = val;
        })
        .def("__getitem__", [](const Matrix &self, std::pair<std::size_t, std::size_t> idx) {
            return self(idx.first, idx.second);
        })
        .def("__str__", &Matrix::toString);

    
    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_tile", &multiply_tile);
    m.def("multiply_mkl", &multiply_mkl);
}