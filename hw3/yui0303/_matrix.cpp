#include "_matrix.hpp"

namespace py = pybind11;

Matrix::Matrix(size_t nrow, size_t ncol) : m_nrow(nrow), m_ncol(ncol)
{
    size_t nelement = nrow * ncol;
    m_buffer = new double[nelement];
    for (size_t i=0; i<nelement; ++i)
    {
        m_buffer[i] = 0;
    }
}

Matrix::Matrix(size_t nrow, size_t ncol, std::vector<double> const & vec) : m_nrow(nrow), m_ncol(ncol)
{
    if (vec.size() != nrow * ncol)
    {
        throw std::out_of_range("Matrix::Matrix(): vector size differs from matrix size");
    }

    m_buffer = new double[nrow * ncol];

    for (size_t i=0; i<nrow; ++i)
    {
        for (size_t j=0; j<ncol; ++j)
        {
            m_buffer[i*ncol + j] = vec[i*ncol + j];
        }
    }

}

Matrix::Matrix(Matrix const &mat) : m_nrow(mat.m_nrow), m_ncol(mat.m_ncol)
{
    m_buffer = new double[m_nrow * m_ncol];
    std::copy(mat.m_buffer, mat.m_buffer + m_nrow * m_ncol, m_buffer);
}

Matrix & Matrix::operator=(Matrix const & mat)
{
    m_nrow = mat.nrow();
    m_ncol = mat.ncol();
    m_buffer = new double[m_nrow * m_ncol];

    for (size_t i=0; i<m_nrow; ++i)
    {
        for (size_t j=0; j<m_ncol; ++j)
        {
            m_buffer[i*m_ncol + j] = mat(i,j);
        }
    }
    return *this;
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

// std::ostream & operator<<(std::ostream & os, Matrix const &mat)
// {
//     for (size_t i = 0; i < mat.m_nrow; ++i)
//     {
//         for (size_t j = 0; j < mat.m_ncol; ++j)
//         {
//             os << mat(i, j) << " ";
//         }
//         os << std::endl;
//     }
//     return os;
// }

Matrix::~Matrix()
{
    delete[] m_buffer;
}

double   Matrix::operator() (size_t row, size_t col) const
{
    //add the boundary check
    if (row >= m_nrow || col >= m_ncol)
    {
        throw std::out_of_range("Matrix::operator(): index out of range");
    }

    return m_buffer[row*m_ncol + col];
}

double & Matrix::operator() (size_t row, size_t col)
{
    //add the boundary check
    if (row >= m_nrow || col >= m_ncol)
    {
        throw std::out_of_range("Matrix::operator(): index out of range");
    }

    return m_buffer[row*m_ncol + col];
}

double* Matrix::data() const { return m_buffer; }

size_t Matrix::nrow() const { return m_nrow; }
size_t Matrix::ncol() const { return m_ncol; }

// ============================ Matrix Matrix Multiplication ===========================


//function to multiply two matrix m*n & n*p with tile size and m, n, p are all multiples of tile size
Matrix multiply_tile(Matrix const& mat1, Matrix const& mat2, size_t tsize)
{
    // Check if the dimensions of the matrices are valid for tiling.
    /*if (mat1.nrow() % tsize != 0 || mat1.ncol() % tsize != 0 || mat2.ncol() % tsize != 0 || mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range("invalid matrix dimensions for tiling");
    }
    */

    // Create a new matrix to store the result of the multiplication.
    Matrix result(mat1.nrow(), mat2.ncol());
    size_t m = mat1.nrow();
    size_t n = mat2.ncol();
    size_t p = mat1.ncol();
    // Divide the matrices into tiles of size tile_m x tile_n and tile_n x tile_p.
    for (size_t i = 0; i < m; i += tsize)
    {
        for (size_t j = 0; j < n; j += tsize)
        {
            for (size_t k = 0; k < p; k += tsize)
            {
                // Multiply each tile of mat1 with the corresponding tile of mat2 and add the result to the corresponding tile of the result matrix.
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

Matrix multiply_naive(Matrix const& mat1, Matrix const& mat2)
{
    // Check if the dimensions of the matrices are valid for multiplication.
    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range("invalid matrix dimensions for multiplication");
    }

    // Create a new matrix to store the result of the multiplication.
    Matrix result(mat1.nrow(), mat2.ncol());

    // Multiply each element of mat1 with the corresponding element of mat2 and add the result to the corresponding element of the result matrix.
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

Matrix multiply_mkl(Matrix const& mat1, Matrix const& mat2)
{
    // Check if the dimensions of the matrices are valid for multiplication.
    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range("invalid matrix dimensions for multiplication");
    }

    // Create a new matrix to store the result of the multiplication.
    Matrix result(mat1.nrow(), mat2.ncol());

    // Compute the matrix multiplication using DGEMM.
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


PYBIND11_MODULE(_matrix, m) {
    py::class_<Matrix>(m, "Matrix")
        .def(py::init<size_t, size_t>())
        .def(py::init<size_t, size_t, std::vector<double> const &>())
	.def(py::init<Matrix const&>())
	/*
        .def("__getitem__", [](Matrix &m, std::tuple<size_t, size_t> i) -> double {
            size_t row = std::get<0>(i);
            size_t col = std::get<1>(i);
            return m(row, col);
        })
        .def("__setitem__", [](Matrix &m, std::tuple<size_t, size_t> i, double val) {
            size_t row = std::get<0>(i);
            size_t col = std::get<1>(i);
            m(row, col) = val;
        })
	*/
	.def("__getitem__", [](Matrix &mat, std::pair<size_t, size_t> index) -> double{
	    return mat(index.first, index.second);
	})
	.def("__setitem__", [](Matrix &mat, std::pair<size_t, size_t> index, double val){
		mat(index.first, index.second) = val;
	})
        .def("__eq__", &Matrix::operator==)
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol)
        ;
    m.def("multiply_tile", &multiply_tile);
    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_mkl", &multiply_mkl);
}



//operator overloading for vector
// std::ostream & operator<<(std::ostream & os, std::vector<double> const & vec)
// {
//     for (size_t i=0; i<vec.size(); ++i)
//     {
//         os << vec[i] << " ";
//     }
//     os << std::endl;
//     return os;
// }

// std::vector<double> operator*(Matrix const & mat, std::vector<double> const & vec)
// {
//     if (mat.ncol() != vec.size())
//     {
//         throw std::out_of_range("matrix column differs from vector size");
//     }

//     std::vector<double> ret(mat.nrow());

//     for (size_t i=0; i<mat.nrow(); ++i)
//     {
//         double v = 0;
//         for (size_t j=0; j<mat.ncol(); ++j)
//         {
//             v += mat(i,j) * vec[j];
//         }
//         ret[i] = v;
//     }

//     return ret;
// }
