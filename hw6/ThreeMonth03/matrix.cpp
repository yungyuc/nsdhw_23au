#include "matrix.hpp"

void Matrix::reset_buffer(size_t nrow, size_t ncol){
    if (m_buffer) { delete[] m_buffer; }
        const size_t nelement = nrow * ncol;
    if (nelement) { m_buffer = new double[nelement]; }
    else          { m_buffer = nullptr; }
        m_nrow = nrow;
        m_ncol = ncol;
}

Matrix::Matrix(size_t nrow, size_t ncol) : m_nrow(nrow), m_ncol(ncol)
{
    size_t nelement = nrow * ncol;
    reset_buffer(nrow, ncol);
    memset(m_buffer, 0, nelement * sizeof(double));
}

Matrix::Matrix(size_t nrow, size_t ncol, std::vector<double> const & vec) : m_nrow(nrow), m_ncol(ncol)
{
    //if (vec.size() != nrow * ncol)
    //{
    //    throw std::out_of_range("Matrix::Matrix(): vector size differs from matrix size");
    //}
        reset_buffer(nrow, ncol);
        (*this) = vec;

}


Matrix & Matrix::operator=(Matrix && other){
        if (this == &other) { return *this; }
        reset_buffer(0, 0);
        std::swap(m_nrow, other.m_nrow);
        std::swap(m_ncol, other.m_ncol);
        std::swap(m_buffer, other.m_buffer);
        return *this;
}

Matrix & Matrix::operator=(std::vector<double> const & vec)
{
    //if (size() != vec.size())
    //{
    //    throw std::out_of_range("number of elements mismatch");
    //}
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

Matrix::Matrix(Matrix const &mat) : m_nrow(mat.m_nrow), m_ncol(mat.m_ncol)
{
    reset_buffer(mat.m_nrow, mat.m_ncol);
    for (size_t i=0; i<m_nrow; ++i){
        for (size_t j=0; j<m_ncol; ++j)
        {
            (*this)(i,j) = mat(i,j);
        }
    }
}

Matrix & Matrix::operator=(Matrix const & other)
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

Matrix::Matrix(Matrix && other)
  : m_nrow(other.m_nrow), m_ncol(other.m_ncol)
{
    reset_buffer(0, 0);
    std::swap(m_nrow, other.m_nrow);
    std::swap(m_ncol, other.m_ncol);
    std::swap(m_buffer, other.m_buffer);
}


Matrix Matrix::operator+(Matrix const & other){
    //if(( nrow() != other.nrow()) || ( ncol() != other.ncol())){
    //    throw std::out_of_range("Number of elements mismatch.");
    //}    
    Matrix temp(m_nrow, m_ncol);
    for(size_t i = 0 ; i < m_nrow; ++i){
        for(size_t j = 0; j < m_ncol; ++j){
            temp(i,j) = (*this)(i,j) + other(i,j);
        }
    }
    return temp;
}

bool Matrix::operator==(Matrix const & mat) const
{
    if (mat.m_ncol != m_ncol || mat.m_nrow != m_nrow) return false;
    for (size_t i = 0; i < mat.m_nrow; ++i)
    {
        for (size_t j = 0; j < mat.m_ncol; ++j)
        {
            if(mat(i, j) != m_buffer[i*m_nrow+j])return false;
        }
    }
    return true;
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

Matrix::~Matrix()
{
    reset_buffer(0, 0);
}

double   Matrix::operator() (size_t row, size_t col) const
{
    //if (row >= m_nrow || col >= m_ncol)
    //{
    //    throw std::out_of_range("Matrix::operator(): index out of range");
    //}

    return m_buffer[index(row, col)];
}

double & Matrix::operator() (size_t row, size_t col)
{
    //if (row >= m_nrow || col >= m_ncol)
    //{
    //    throw std::out_of_range("Matrix::operator(): index out of range");
    //}

    return m_buffer[index(row, col)];
}

double* Matrix::data() const { return m_buffer; }

size_t Matrix::nrow() const { return m_nrow; }
size_t Matrix::ncol() const { return m_ncol; }

Matrix multiply_tile(Matrix const& mat1, Matrix const& mat2, size_t tsize)
{

    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }

    Matrix result(mat1.nrow(), mat2.ncol());
    size_t max_i = mat1.nrow();
    size_t max_j = mat2.ncol();
    size_t max_k = mat1.ncol();

    for (size_t i = 0; i < max_i; i += tsize)
    {
        for (size_t j = 0; j < max_j; j += tsize)
        {
            for (size_t k = 0; k < max_k; k += tsize)
            {
                size_t upper_i = std::min(i + tsize, max_i);
                size_t upper_j = std::min(j + tsize, max_j);
                size_t upper_k = std::min(k + tsize, max_k);
                for (size_t ii = i; ii < upper_i ; ++ii)
                {
                    for (size_t jj = j; jj < upper_j ; ++jj) 
		            {
		    	        double sum = .0;
                        for (size_t kk = k; kk < upper_k; ++kk)
                        {
                            sum += mat1(ii, kk) * mat2(kk, jj);
                        }
			            result(ii, jj) += sum;
                    }
                }
            }
        }
    }

    return result;
}

Matrix multiply_naive(Matrix const& mat1, Matrix const& mat2)
{
    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }

    Matrix ret(mat1.nrow(), mat2.ncol());

    for (size_t j=0; j<mat1.nrow(); ++j)
    {
        for (size_t k=0; k<ret.ncol(); ++k)
        {
            //double v = 0;
            for (size_t i=0; i<ret.ncol(); ++i)
            {
                ret(i,k) += mat1(i,j) * mat2(j,k);
            }
            //ret(i,k) = v;
        }
    }

    return ret;
}

Matrix multiply_mkl(Matrix const& mat1, Matrix const& mat2)
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