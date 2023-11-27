#include "_matrix.hpp"

Matrix multiply_naive(Matrix const& mat1, Matrix const& mat2){
    Matrix result(mat1.nrow(), mat2.ncol());

    for (size_t i = 0; i < mat1.nrow(); ++i)
    {
        for (size_t j = 0; j < mat2.ncol(); ++j)
        {
	    double sum = .0;
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
		    	        double sum = .0;
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