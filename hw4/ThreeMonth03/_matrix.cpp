#include "_matrix.hpp"

Matrix::Matrix(size_t row, size_t col) : m_nrow(row), m_ncol(col), m_buffer(MyAllocator){
    m_buffer.resize(row * col);
}

Matrix::Matrix(Matrix const &mat) : m_nrow(mat.nrow()), m_ncol(mat.ncol()), m_buffer(mat.m_buffer, MyAllocator){

}

double Matrix::operator()(size_t row, size_t col) const{ 
    return m_buffer[row*m_ncol + col];
}

double& Matrix::operator()(size_t row, size_t col){ 
    return m_buffer[row*m_ncol + col];
}

double* Matrix::data(){ 
    return m_buffer.data();
}

double const* Matrix::data() const{ 
    return m_buffer.data();
}

size_t Matrix::nrow() const{ 
    return m_nrow;
}

size_t Matrix::ncol() const{ 
    return m_ncol; 
}

bool Matrix::operator==(Matrix const &mat2) const{
    if (m_ncol != mat2.ncol() || m_nrow != mat2.ncol())
        return false;
    for (size_t i = 0; i < m_nrow; i++)
    {
        for (size_t j = 0; j < m_ncol; j++)
        {
            if (m_buffer[i * m_ncol + j] != mat2(i, j))
                return false;
        }
    }
    return true;
}

Matrix multiply_naive(Matrix const& mat1, Matrix const& mat2){
    Matrix result(mat1.nrow(), mat2.ncol());

    for (size_t i = 0; i < mat1.nrow(); ++i)
    {
        for (size_t j = 0; j < mat2.ncol(); ++j)
        {
	    double sum = 0.0;
            for (size_t k = 0; k < mat1.ncol(); ++k)
            {
                sum += mat1(i, k) * mat2(k, j);
            }
	    result(i, j) = sum;
        }
    }

    return result;
}

Matrix multiply_tile(Matrix const& mat1, Matrix const& mat2, size_t tsize){
    Matrix result(mat1.nrow(), mat2.ncol());

    size_t m = mat1.nrow(), n = mat2.ncol(), p = mat1.ncol();

    for (size_t i = 0; i < m; i += tsize)
    {
        for (size_t j = 0; j < n; j += tsize)
        {
            for (size_t k = 0; k < p; k += tsize)
            {
                for (size_t ii = i; ii < std::min(i + tsize, m); ++ii)
                {
                    for (size_t jj = j; jj < std::min(j + tsize, n); ++jj) 
		            {
		    	        double sum = 0.0;
                        for (size_t kk = k; kk < std::min(k + tsize, p); ++kk)
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

Matrix multiply_mkl(Matrix const& mat1, Matrix const& mat2){
    Matrix result(mat1.nrow(), mat2.ncol());

    cblas_dgemm(
        CblasRowMajor, 
        CblasNoTrans, 
        CblasNoTrans, 
        mat1.nrow(), 
        mat2.ncol(), 
        mat1.ncol(), 
        1.0, 
        mat1.data(), 
        mat1.ncol(), 
        mat2.data(), 
        mat2.ncol(), 
        0.0, 
        result.data(), 
        result.ncol()
    );

    return result;
}