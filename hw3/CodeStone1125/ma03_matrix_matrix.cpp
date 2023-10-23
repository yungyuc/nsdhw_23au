#include <iostream>
#include <pybind11/pybind11.h> 
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <iomanip>
#include <vector>
#include <stdexcept>
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

    double *val_addr() {return &(this->m_buffer[0]);}
    
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

    size_t nrow() const { return m_nrow; }
    size_t ncol() const { return m_ncol; }

    size_t size() const { return m_nrow * m_ncol; }
    // 返回缓冲区中指定索引位置的元素
    double buffer(size_t i) const {
        if (i < m_nrow * m_ncol) {
            return m_buffer[i];
        } else {
            // 检查索引是否越界，如果越界则返回默认值（根据需要更改）
            return 0.0;
        }
    }

    std::vector<double> buffer_vector() const
    {
        if (m_buffer) {
            return std::vector<double>(m_buffer, m_buffer + size());
        } else {
            // 返回空向量，因为没有有效数据
            return std::vector<double>();
        }
    }


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

// Basic matrix multiplication
Matrix operator*(Matrix const & mat1, Matrix const & mat2)
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
/*
 * Naive matrix matrix multiplication.
 */
Matrix multiply_naive(Matrix const & mat1, Matrix const & mat2)
{
    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of the second matrix row");
    }

    Matrix ret(mat1.nrow(), mat2.ncol());

    for (size_t i = 0; i < ret.nrow(); ++i)
    {
        for (size_t k = 0; k < ret.ncol(); ++k)
        {
            double v = 0;
            for (size_t j = 0; j < mat1.ncol(); ++j)
            {
                v += mat1(i, j) * mat2(j, k);
            }
            ret(i, k) = v;
        }
    }

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

// Function for matrix-matrix multiplication with tiling
Matrix multiple_tile(const Matrix& mat1, const Matrix& mat2, size_t tileSize) {
    size_t n = mat1.nrow();
    size_t m = mat1.ncol();
    size_t p = mat2.ncol();

    if (m != mat2.nrow()) {
        throw std::invalid_argument("Matrix dimensions are not compatible for multiplication.");
    }

    Matrix result(n, p);

    for (size_t i0 = 0; i0 < n; i0 += tileSize) {
        for (size_t j0 = 0; j0 < p; j0 += tileSize) {
            for (size_t k0 = 0; k0 < m; k0 += tileSize) {
                for (size_t i = i0; i < std::min(i0 + tileSize, n); ++i) {
                    for (size_t j = j0; j < std::min(j0 + tileSize, p); ++j) {
                        double v = 0;
                        for (size_t k = k0; k < std::min(k0 + tileSize, m); ++k) {
                            v += mat1(i, k) * mat2(k, j);
                        }
                        result(i, j) += v;
                    }
                }
            }
        }
    }

    return result;
}

Matrix multiply_mkl(Matrix & mat1, Matrix & mat2)
{
    //check_multibility(mat1, mat2);
    Matrix res(mat1.nrow(), mat2.ncol());
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, mat1.nrow(), mat2.ncol(), mat1.ncol(), 1, mat1.val_addr(), mat1.ncol(), mat2.val_addr(), mat2.ncol(), 0, res.val_addr(), res.ncol());
    return res;
}


int main(int argc, char ** argv)
{
    std::cout << ">>> Naive algo for A(2x3) times B(3x2):" << std::endl;
    Matrix mat1(2, 3, std::vector<double>{1, 2, 3, 4, 5, 6});
    Matrix mat2(3, 2, std::vector<double>{1, 2, 3, 4, 5, 6});
    std::cout << "matrix A (2x3):" << mat1 << std::endl;
    std::cout << "matrix B (3x2):" << mat2 << std::endl;
    Matrix mat3 = multiply_naive(mat1, mat2);
    std::cout << "result matrix C (2x2) = AB:" << mat3 << std::endl;

    std::cout << ">>> Tiling algo for A(2x3) times B(3x2):" << std::endl;
    Matrix mat4 = multiple_tile(mat1, mat2, 4);
    std::cout << "result matrix C (2x2) = AB:" << mat4 << std::endl;

    std::cout << ">>> DGEMM for A(2x3) times B(3x2):" << std::endl;
    Matrix mat5 = multiply_mkl(mat1, mat2);
    std::cout << "result matrix C (2x2) = AB:" << mat5 << std::endl;

    return 0;
}

//pybind
PYBIND11_MODULE(ma03_matrix_matrix, m)
{
    m.doc() = "Matrix Multiplication funciton unit test.";

    pybind11::class_<Matrix>(m, "Matrix")
        .def(pybind11::init<>())
        .def(pybind11::init<size_t, size_t>())
        .def(pybind11::self == pybind11::self)
        .def("__getitem__", &Matrix::getvalue)
        .def("__setitem__", &Matrix::setvalue)
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol);

    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_tile", &multiply_tile);
    m.def("multiply_mkl", &multiply_mkl);
}