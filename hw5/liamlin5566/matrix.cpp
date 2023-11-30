#include <cstring>
#include <stdexcept>

#include <mkl/mkl.h>
#include <mkl/mkl_lapack.h>
#include <mkl/mkl_lapacke.h>
#include <pybind11/pybind11.h>

#include "matrix.h"



// template <class T> std::size_t CustomAllocator<T>::m_allocated = 0;
// template <class T> std::size_t CustomAllocator<T>::m_deallocated = 0;

// template <class T> T *CustomAllocator<T>::allocate(std::size_t n)
// {
//     if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
//     {
//         throw std::bad_alloc();
//     }

//     const std::size_t bytes = n*sizeof(T);
//     T * ptr = static_cast<T *>(std::malloc(bytes));
//     if (ptr != nullptr)
//     {   
//         //std::cout << "allocate0 " << m_allocated << std::endl;
//         m_allocated += bytes;
//         //std::cout << "allocate1 " << m_allocated << std::endl;
//         return ptr;
//     }
//     else
//     {
//         throw std::bad_alloc();
//     }
// }





Matrix::Matrix(Matrix const & other): m_nrow(other.m_nrow), m_ncol(other.m_ncol)
{
    //reset_buffer(other.m_nrow, other.m_ncol);
    //std::cout << "copy construct" << std::endl;

    m_buffer = std::vector<double>(m_nrow * m_ncol, 0.0); 
    for (std::size_t i=0; i<m_nrow; ++i)
    {
        for (std::size_t j=0; j<m_ncol; ++j)
        {
            (*this)(i,j) = other(i,j);
        }
    }
}


Matrix & Matrix::operator=(Matrix const & other)
{
    //std::cout << "copy assignment" << std::endl;
    if (this == &other) { return *this; }
    if (m_nrow != other.m_nrow || m_ncol != other.m_ncol)
    {
        m_nrow = other.m_nrow;
        m_ncol = other.m_ncol;
        m_buffer =std::vector<double>(m_nrow * m_ncol, 0.0); 
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


Matrix::Matrix(Matrix && other): m_nrow(other.m_nrow), m_ncol(other.m_ncol)
{
    //reset_buffer(other.m_nrow, other.m_ncol);
    //std::cout << "move construct" << std::endl;
    m_buffer = std::vector<double>(m_nrow * m_ncol, 0.0); 
    for (std::size_t i=0; i<m_nrow; ++i)
    {
        for (std::size_t j=0; j<m_ncol; ++j)
        {
            (*this)(i,j) = other(i,j);
        }
    }

    other.m_nrow = 0;
    other.m_ncol = 0;
    other.m_buffer.clear();
}


Matrix & Matrix::operator=(Matrix && other)
{
    //std::cout << "move assignment" << std::endl;
    if (this == &other) { return *this; }
    if (m_nrow != other.m_nrow || m_ncol != other.m_ncol)
    {
        m_nrow = other.m_nrow;
        m_ncol = other.m_ncol;
        m_buffer =std::vector<double>(m_nrow * m_ncol, 0.0); 
    }
    for (std::size_t i=0; i<m_nrow; ++i)
    {
        for (std::size_t j=0; j<m_ncol; ++j)
        {
            (*this)(i,j) = other(i,j);
        }
    }

    other.m_nrow = 0;
    other.m_ncol = 0;
    other.m_buffer.clear();
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



Matrix multiply_tile(Matrix const &mat1, Matrix const &mat2, std::size_t tsize)
{
    if (mat1.ncol() != mat2.nrow())
        throw std::out_of_range("Mismatch, two matrix cannot be multiplied");
    
    Matrix ret(mat1.nrow(), mat2.ncol());

    for (std::size_t i = 0; i < mat1.nrow(); i+=tsize)
    {
        std::size_t it_bound = std::min(i+tsize, mat1.nrow());
        
        for (std::size_t j = 0; j < mat2.ncol(); j+=tsize)
        {
            std::size_t jt_bound = std::min(j+tsize, mat2.ncol());
            
            for (std::size_t k = 0; k < mat1.ncol(); k+=tsize)
            {
                std::size_t kt_bound = std::min(k+tsize, mat1.ncol());
                
                for (std::size_t it = i; it < it_bound; it++)
                {
                    for (std::size_t jt = j; jt < jt_bound ; jt++)
                    {
                        double v = 0;
                        for (std::size_t kt = k; kt < kt_bound; kt++)
                            v += mat1(it, kt) * mat2(kt, jt);
                        ret(it, jt) += v;
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

// namespace py = pybind11;

// PYBIND11_MODULE(_matrix, m) 
// {
//     m.doc() = "Matirx class and Matrix multiplication func.";

   
//     py::class_<Matrix>(m, "Matrix")
//         .def(py::init<std::size_t, std::size_t>()) 
//         .def_property_readonly("nrow", &Matrix::nrow)
//         .def_property_readonly("ncol", &Matrix::ncol)
//         .def_property_readonly("size", &Matrix::size)
//         .def("__eq__", [](const Matrix &x, const Matrix &y) { return x == y; })
//         .def("__setitem__", [](Matrix &self, std::pair<std::size_t, std::size_t> idx, double val) {
//             self(idx.first, idx.second) = val;
//         })
//         .def("__getitem__", [](const Matrix &self, std::pair<std::size_t, std::size_t> idx) {
//             return self(idx.first, idx.second);
//         })
//         .def("__str__", &Matrix::toString);

    
//     m.def("multiply_naive", &multiply_naive);
//     m.def("multiply_tile", &multiply_tile);
//     m.def("multiply_mkl", &multiply_mkl);

//     m.def("bytes", &CustomAllocator<double>::bytes);
//     m.def("allocated", &CustomAllocator<double>::allocated);
//     m.def("deallocated", &CustomAllocator<double>::deallocated);
// }
