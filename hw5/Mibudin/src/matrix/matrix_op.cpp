#include"matrix/matrix_op.hpp"

#include<stdexcept>

#include<mkl/mkl.h>


namespace matrix
{
void validate_multiply(const Matrix& mat1, const Matrix& mat2)
{
    if(mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }
}

Matrix multiply_naive(const Matrix& mat1, const Matrix& mat2)
{
    validate_multiply(mat1, mat2);

    Matrix ret(mat1.nrow(), mat2.ncol());

    const std::size_t nrow1 = mat1.nrow();
    const std::size_t ncol1 = mat1.ncol();
    const std::size_t ncol2 = mat2.ncol();

    for(std::size_t i = 0; i < nrow1; ++i)
    {
        for(std::size_t j = 0; j < ncol1; ++j)
        {
            for(std::size_t k = 0; k < ncol2; ++k)
            {
                ret(i, j) += mat1(i, k) * mat2(k, j);
            }
        }
    }

    return ret;
}

Matrix multiply_tile(
    const Matrix& mat1, const Matrix& mat2, std::size_t tile_size)
{
    validate_multiply(mat1, mat2);

    Matrix ret(mat1.nrow(), mat2.ncol());

    const std::size_t nrow1 = mat1.nrow();
    const std::size_t ncol1 = mat1.ncol();
    const std::size_t ncol2 = mat2.ncol();

    for(std::size_t i = 0; i < nrow1; i += tile_size)
    {
        for(std::size_t j = 0; j < ncol2; j += tile_size)
        {
            for(std::size_t k = 0; k < ncol1; k += tile_size)
            {
                for(std::size_t ti = i;
                    ti < std::min(i + tile_size, nrow1); ++ti)
                {
                    for(std::size_t tk = k;
                        tk < std::min(k + tile_size, ncol1); ++tk)
                    {
                        for(std::size_t tj = j;
                            tj < std::min(j + tile_size, ncol2); ++tj)
                        {
                            ret(ti, tj) += mat1(ti, tk) * mat2(tk, tj);
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
    validate_multiply(mat1, mat2);

    Matrix ret(mat1.nrow(), mat2.ncol());

    cblas_dgemm(
        CblasRowMajor,
        CblasNoTrans, CblasNoTrans,
        mat1.nrow(), mat1.ncol(), mat2.ncol(),
        1,
        mat1.data(), mat1.ncol(),
        mat2.data(), mat2.ncol(),
        0,
        ret.data(), ret.ncol()
    );

    return ret;
}

std::size_t bytes()
{
    return Matrix::buffer_type::allocator_type::bytes();
}

std::size_t allocated()
{
    return Matrix::buffer_type::allocator_type::allocated();
}

std::size_t deallocated()
{
    return Matrix::buffer_type::allocator_type::deallocated();
}
}  // namespace matrix
