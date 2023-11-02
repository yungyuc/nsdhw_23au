#include <iostream>
#include <iomanip>
#include <mkl.h>
#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>


class Matrix {
public:

    Matrix(size_t nrow, size_t ncol)
    : m_nrow(nrow), m_ncol(ncol)
    {
        reset_buffer(nrow, ncol);
    }
    double   operator() (size_t row, size_t col) const
    {
        return m_buffer[index(row, col)];
    }
    double & operator() (size_t row, size_t col)
    {
        return m_buffer[index(row, col)];
    }
    size_t nrow() const { return m_nrow; }
    size_t ncol() const { return m_ncol; }
    size_t size() const { return m_nrow * m_ncol; }

    size_t index(size_t row, size_t col) const
    {
        return row * m_ncol + col;
    }
    double * m_buffer = nullptr;

private:
    size_t m_nrow = 0;
    size_t m_ncol = 0;
    void reset_buffer(size_t nrow, size_t ncol)
    {
        if (m_buffer) 
        { 
            delete[] m_buffer; 
        }
        const size_t nelement = nrow * ncol;
        if (nelement)
        { 
            m_buffer = new double[nelement]; 
        }
        else
        {
            m_buffer = nullptr;
        }
        m_nrow = nrow;
        m_ncol = ncol;
    }

};

/*
 * Implement a free function performing naive matrix-matrix multiplication. Name it multiply_naive()
 */

Matrix multiply_naive(Matrix const & mat_A, Matrix const & mat_B)
{
    if (mat_A.ncol() != mat_B.nrow())
    {
        throw std::out_of_range("shapes not aligned");
    }

    Matrix mat(mat_A.nrow(), mat_B.ncol());

    for (size_t i=0; i<mat_A.nrow(); ++i) 
    {
        for (size_t j=0; j<mat_B.ncol(); ++j) 
        {
            double v = 0;
            for (size_t k=0; k<mat_A.ncol(); ++k)
            {
                v = v + mat_A(i, k) * mat_B(k, j);
            }
            mat(i, j) = v;
        }
    }
    return mat;
}
/*
 * Implement a free function performing matrix-matrix multiplication with tiling. Name it multiply_tile()
 */

Matrix multiply_tile(Matrix const & mat_A, Matrix const & mat_B, size_t block_size)
{
    if (mat_A.ncol() != mat_B.nrow())
    {
        throw std::out_of_range("shapes not aligned");
    }

    if (block_size > mat_A.ncol() || block_size > mat_A.nrow() || block_size > mat_B.ncol())
    {
        throw std::out_of_range("block dimension is larger than number of rows and cols");
    }
    Matrix mat(mat_A.nrow(), mat_B.ncol());

    for(size_t row=0; row<mat_A.nrow(); row+=block_size)
        {
            for(size_t col=0; col<mat_B.ncol(); col+=block_size)
            {
                for(size_t inner=0; inner<mat_A.ncol(); inner+=block_size)
                {
                    for(size_t i=row; i< std::min(mat_A.nrow(), row+block_size); ++i)
                    {
                        for(size_t j=col; j< std::min(mat_B.ncol(), col+block_size); ++j)
                        {
                            for(size_t k=inner; k< std::min(mat_A.ncol(), inner+block_size); ++k)
                            {
                                mat(i, j) += mat_A(i, k) * mat_B(k, j);
                            }
                        }
                    }
                }
            }
        }
    return mat;
}
/*
 * Implement a free function performing matrix-matrix multiplication with mkl. Name it multiply_mkl()
 */
Matrix multiply_mkl(Matrix const & mat_A, Matrix const & mat_B)
{
    if (mat_A.ncol() != mat_B.nrow())
    {
        throw std::out_of_range("shapes not aligned");
        
    }
    Matrix mat(mat_A.nrow(), mat_B.ncol());

    cblas_dgemm(
        CblasRowMajor,
        CblasNoTrans,
        CblasNoTrans,
        mat_A.nrow(),
        mat_B.ncol(),
        mat_A.ncol(),
        1.0, // alpha
        mat_A.m_buffer,
        mat_A.ncol(),
        mat_B.m_buffer,
        mat_B.ncol(),
        0.0, //beta 
        mat.m_buffer,
        mat.ncol());
    return mat;
}

std::ostream & operator << (std::ostream & ostr, Matrix const & mat)
{
    for (size_t i=0; i<mat.nrow(); ++i) // the i-th row
    {
        ostr << std::endl << " ";
        for (size_t j=0; j<mat.ncol(); ++j) // the j-th column
        {
            ostr << " " << std::setw(2) << mat(i, j);
        }
    }

    return ostr;
}

std::ostream & operator << (std::ostream & ostr, std::vector<double> const & vec)
{
    for (size_t i=0; i<vec.size(); ++i)
    {
        std::cout << " " << vec[i];
    }

    return ostr;
}
bool operator == (Matrix const &mat_A, Matrix const &mat_B)
{
    if (mat_A.nrow() != mat_B.nrow() || mat_A.ncol() != mat_B.ncol())
        return false;
    for (size_t i = 0; i < mat_A.nrow(); ++i)
    {
        for (size_t j = 0; j < mat_A.ncol(); ++j)
        {
            if (mat_A(i, j) != mat_B(i, j))
                return false;
        }
    }
    return true;
}

bool operator != (Matrix const &mat_A, Matrix const &mat_B)
{
    return !(mat_A==mat_B);
}

PYBIND11_MODULE(_matrix, m)
{
    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_mkl", &multiply_mkl);
    m.def("multiply_tile", &multiply_tile);
    pybind11::class_<Matrix>(m, "Matrix")
        .def(pybind11::init<size_t, size_t>())
        .def("__setitem__", [](Matrix &self, std::pair<size_t, size_t> i, double val) {
            self(i.first, i.second) = val;
        })
        .def("__getitem__", [](Matrix &self, std::pair<size_t, size_t> i) {
            return self(i.first, i.second);
        })
        .def("__eq__", &operator==)
        .def_property("nrow", &Matrix::nrow, nullptr)
        .def_property("ncol", &Matrix::ncol, nullptr);
}