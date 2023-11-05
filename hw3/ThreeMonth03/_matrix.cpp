#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <utility>
#include <mkl.h>

class Matrix {

public:

    Matrix(size_t nrow, size_t ncol)
      : m_nrow(nrow), m_ncol(ncol)
    {
        reset_buffer(nrow, ncol);
    }

    Matrix(size_t nrow, size_t ncol, std::vector<double> const & vec)
      : m_nrow(nrow), m_ncol(ncol)
    {
        reset_buffer(nrow, ncol);
        (*this) = vec;
    }

    Matrix & operator=(std::vector<double> const & vec)
    {
        if (size() != vec.size())
        {
            throw std::out_of_range("number of elements mismatch");
        }

        size_t k = 0;
        for (size_t i=0; i<m_nrow; ++i)
        {
            for (size_t j=0; j<m_ncol; ++j)
            {
                (*this)(i,j) = vec[k];
                ++k;
            }
        }

        return *this;
    }

    Matrix(Matrix const & other)
      : m_nrow(other.m_nrow), m_ncol(other.m_ncol)
    {
        reset_buffer(other.m_nrow, other.m_ncol);
        for (size_t i=0; i<m_nrow; ++i)
        {
            for (size_t j=0; j<m_ncol; ++j)
            {
                (*this)(i,j) = other(i,j);
            }
        }
    }

    Matrix & operator=(Matrix const & other)
    {
        if (this == &other) { return *this; }
        if (m_nrow != other.m_nrow || m_ncol != other.m_ncol)
        {
            reset_buffer(other.m_nrow, other.m_ncol);
        }
        for (size_t i=0; i<m_nrow; ++i)
        {
            for (size_t j=0; j<m_ncol; ++j)
            {
                (*this)(i,j) = other(i,j);
            }
        }
        return *this;
    }

    Matrix(Matrix && other)
      : m_nrow(other.m_nrow), m_ncol(other.m_ncol)
    {
        reset_buffer(0, 0);
        std::swap(m_nrow, other.m_nrow);
        std::swap(m_ncol, other.m_ncol);
        std::swap(m_buffer, other.m_buffer);
    }

    Matrix & operator=(Matrix && other)
    {
        if (this == &other) { return *this; }
        reset_buffer(0, 0);
        std::swap(m_nrow, other.m_nrow);
        std::swap(m_ncol, other.m_ncol);
        std::swap(m_buffer, other.m_buffer);
        return *this;
    }

    ~Matrix()
    {
        reset_buffer(0, 0);
    }

    double   operator() (size_t row, size_t col) const
    {
        return m_buffer[index(row, col)];
    }
    double & operator() (size_t row, size_t col)
    {
        return m_buffer[index(row, col)];
    }


    bool operator==(Matrix const &mat){
	    if((*this).nrow() != mat.nrow() || (*this).ncol() != mat.ncol()) return false;
        for(size_t i = 0; i < mat.nrow(); ++i){
            for(size_t j = 0; j < mat.ncol(); ++j){
	            if((*this)(i, j) != mat(i, j)) return false;
            }
        }
        return true;
    }

    Matrix operator+(Matrix const & other){
        if(( nrow() != other.nrow()) || ( ncol() != other.ncol())){
            throw std::out_of_range("Number of elements mismatch.");
        }    

        Matrix temp(m_nrow, m_ncol);
        for(size_t i = 0 ; i < m_nrow; ++i){
            for(size_t j = 0; j < m_ncol; ++j){
                temp(i,j) = (*this)(i,j) + other(i,j);
            }
        }
        return temp;
    }

    size_t nrow() const { return m_nrow; }
    size_t ncol() const { return m_ncol; }
    size_t size() const { return m_nrow * m_ncol; }
    double buffer(size_t i) const { return m_buffer[i]; }
    std::vector<double> buffer_vector() const
    {
        return std::vector<double>(m_buffer, m_buffer+size());
    }
    double* data() const { return m_buffer; }

private:

    size_t index(size_t row, size_t col) const
    {
        return row + col * m_nrow;
    }

    void reset_buffer(size_t nrow, size_t ncol)
    {
        if (m_buffer) { delete[] m_buffer; }
        const size_t nelement = nrow * ncol;
        if (nelement) { m_buffer = new double[nelement]; }
        else          { m_buffer = nullptr; }
        m_nrow = nrow;
        m_ncol = ncol;
    }

    size_t m_nrow = 0;
    size_t m_ncol = 0;
    double * m_buffer = nullptr;

};

/*
 * Naive matrix matrix multiplication.
 */
Matrix multiply_tile(Matrix const & mat1, Matrix const & mat2, size_t tile_shape)
{
    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }

    Matrix ret(mat1.nrow(), mat2.ncol());

    const size_t max_i = mat1.nrow();
    const size_t max_k = mat2.ncol();
    const size_t max_j = mat1.ncol();

    for (size_t i=0; i<ret.nrow(); i += tile_shape)
    {
        for (size_t k=0; k<ret.ncol(); k += tile_shape)
        {
            for (size_t j=0; j<mat1.ncol(); j += tile_shape)
            {
                for (size_t tile_i = i; tile_i < std::min(i + tile_shape, max_i); ++tile_i)
                {
                    for (size_t tile_j = j; tile_j < std::min(j + tile_shape, max_k); ++tile_j) 
		            {
		    	        double sum = .0;
                        for (size_t tile_k = k; tile_k < std::min(k + tile_shape, max_j); ++tile_k)
                        {
                            sum += mat1(tile_i, tile_k) * mat2(tile_k, tile_j);
                        }
			            ret(tile_i, tile_j) += sum;
                    }
                }
            }
        }
    }

    return ret;
}

Matrix multiply_naive(Matrix const & mat1, Matrix const & mat2)
{
    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }

    Matrix ret(mat1.nrow(), mat2.ncol());

    for (size_t i=0; i<ret.nrow(); ++i)
    {
        for (size_t k=0; k<ret.ncol(); ++k)
        {
            double v = 0;
            for (size_t j=0; j<mat1.ncol(); ++j)
            {
                v += mat1(i,j) * mat2(j,k);
            }
            ret(i,k) = v;
        }
    }

    return ret;
}

Matrix multiply_mkl(Matrix const & mat1, Matrix const & mat2)
{
    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }

    Matrix ret(mat1.nrow(), mat2.ncol());

    cblas_dgemm(
        CblasRowMajor, 
        CblasNoTrans, 
        CblasNoTrans, 
        mat1.nrow(), 
        mat2.ncol(), 
        mat2.nrow(), 
        1.0, 
        mat1.data(), 
        mat1.ncol(), 
        mat2.data(), 
        mat1.nrow(), 
        0.0, 
        ret.data(), 
        ret.ncol()
        );

    return ret;
}

std::ostream & operator << (std::ostream & ostr, Matrix const & mat)
{
    for (size_t i=0; i<mat.nrow(); ++i)
    {
        ostr << std::endl << " ";
        for (size_t j=0; j<mat.ncol(); ++j)
        {
            ostr << " " << std::setw(2) << mat(i, j);
        }
    }

    return ostr;
}

namespace py = pybind11;

PYBIND11_MODULE(_matrix, m){
    py::class_<Matrix>(m,"Matrix")
        .def(py::init<size_t, size_t>())
        .def(py::init<size_t, size_t, std::vector<double> const &>())
        .def(py::init<Matrix const&>())
        .def("__getitem__", [](Matrix &mat, std::pair<size_t, size_t> index) -> double{
	        return mat(index.first, index.second);
	    })
	    .def("__setitem__", [](Matrix &mat, std::pair<size_t, size_t> index, double val){
		    mat(index.first, index.second) = val;
	    })
        .def("__eq__", &Matrix::operator==)
        .def("__add__", &Matrix::operator+)
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol)
        ;
    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_tile", &multiply_tile);
    m.def("multiply_mkl", &multiply_mkl);
}
