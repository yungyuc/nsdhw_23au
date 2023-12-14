/*
 * Copyright (c) 2020, Yung-Yu Chen <yyc@solvcon.net>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of the copyright holder nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <pybind11/pybind11.h> // Must be the first include.
#include <pybind11/attr.h>
#include <pybind11/numpy.h>
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>

#include <atomic>
#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <cblas.h>

#ifdef __GNUG__
#define PYTHON_WRAPPER_VISIBILITY __attribute__((visibility("hidden")))
#else
#define PYTHON_WRAPPER_VISIBILITY
#endif

class Matrix
{
public:
    double *m_buffer = nullptr;
    size_t m_nrow = 0;
    size_t m_ncol = 0;

    Matrix(size_t nrow, size_t ncol)
        : m_nrow(nrow), m_ncol(ncol)
    {
        reset_buffer(nrow, ncol);
    }

    Matrix(size_t nrow, size_t ncol, std::vector<double> const &vec)
        : m_nrow(nrow), m_ncol(ncol)
    {
        reset_buffer(nrow, ncol);
        (*this) = vec;
    }

    Matrix &operator=(std::vector<double> const &vec)
    {
        if (size() != vec.size())
        {
            throw std::out_of_range("number of elements mismatch");
        }

        size_t k = 0;
        for (size_t i = 0; i < m_nrow; ++i)
        {
            for (size_t j = 0; j < m_ncol; ++j)
            {
                (*this)(i, j) = vec[k];
                ++k;
            }
        }

        return *this;
    }

    Matrix(Matrix const &other)
        : m_nrow(other.m_nrow), m_ncol(other.m_ncol)
    {
        reset_buffer(other.m_nrow, other.m_ncol);
        for (size_t i = 0; i < m_nrow; ++i)
        {
            for (size_t j = 0; j < m_ncol; ++j)
            {
                (*this)(i, j) = other(i, j);
            }
        }
    }

    Matrix &operator=(Matrix const &other)
    {
        if (this == &other)
        {
            return *this;
        }
        if (m_nrow != other.m_nrow || m_ncol != other.m_ncol)
        {
            reset_buffer(other.m_nrow, other.m_ncol);
        }
        for (size_t i = 0; i < m_nrow; ++i)
        {
            for (size_t j = 0; j < m_ncol; ++j)
            {
                (*this)(i, j) = other(i, j);
            }
        }
        return *this;
    }

    Matrix(Matrix &&other)
        : m_nrow(other.m_nrow), m_ncol(other.m_ncol)
    {
        reset_buffer(0, 0);
        std::swap(m_nrow, other.m_nrow);
        std::swap(m_ncol, other.m_ncol);
        std::swap(m_buffer, other.m_buffer);
    }

    Matrix &operator=(Matrix &&other)
    {
        if (this == &other)
        {
            return *this;
        }
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

    double operator()(size_t row, size_t col) const
    {
        return m_buffer[index(row, col)];
    }
    double &operator()(size_t row, size_t col)
    {
        return m_buffer[index(row, col)];
    }

    double operator[](size_t idx) const { return m_buffer[idx]; }
    double &operator[](size_t idx) { return m_buffer[idx]; }

    size_t nrow() const { return m_nrow; }
    size_t ncol() const { return m_ncol; }

    size_t size() const { return m_nrow * m_ncol; }
    double buffer(size_t i) const { return m_buffer[i]; }
    std::vector<double> buffer_vector() const
    {
        return std::vector<double>(m_buffer, m_buffer + size());
    }

    size_t index(size_t row, size_t col) const
    {
        return row + col * m_nrow;
    }

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

bool operator==(Matrix const &mat1, Matrix const &mat2)
{
    if ((mat1.ncol() != mat2.ncol()) && (mat1.nrow() != mat2.ncol()))
    {
        return false;
    }

    for (size_t i = 0; i < mat1.nrow(); ++i)
    {
        for (size_t j = 0; j < mat1.ncol(); ++j)
        {
            if (mat1(i, j) != mat2(i, j))
            {
                return false;
            }
        }
    }

    return true;
}

bool operator!=(Matrix const &mat1, Matrix const &mat2)
{
    return !(mat1 == mat2);
}

/*
 * Throw an exception if the shapes of the two matrices don't support
 * multiplication.
 */
void validate_multiplication(Matrix const &mat1, Matrix const &mat2)
{
    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }
}

/*
 * Naive matrix matrix multiplication.
 */
Matrix operator*(Matrix const &mat1, Matrix const &mat2)
{
    validate_multiplication(mat1, mat2);

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

Matrix multiply_naive(Matrix const &mat1, Matrix const &mat2)
{
    return mat1 * mat2;
}

Matrix multiply_mkl(Matrix const &mat1, Matrix const &mat2)
{
    validate_multiplication(mat1, mat2);

    Matrix ret(mat1.nrow(), mat2.ncol());

    cblas_dgemm(
        CblasRowMajor, /* const CBLAS_LAYOUT Layout */
        CblasNoTrans,  /* const CBLAS_TRANSPOSE transa */
        CblasNoTrans,  /* const CBLAS_TRANSPOSE transb */
        mat1.nrow(),   /* const MKL_INT m */
        mat2.ncol(),   /* const MKL_INT n */
        mat1.ncol(),   /* const MKL_INT k */
        1.0,           /* const double alpha */
        mat1.m_buffer, /* const double *a */
        mat1.ncol(),   /* const MKL_INT lda */
        mat2.m_buffer, /* const double *b */
        mat2.ncol(),   /* const MKL_INT ldb */
        0.0,           /* const double beta */
        ret.m_buffer,  /* double * c */
        ret.ncol()     /* const MKL_INT ldc */
    );

    return ret;
}

/*
 * Tiled matrix matrix multiplication.
 */
Matrix multiply_tile(Matrix const &mat1, Matrix const &mat2, size_t block_size)
{
    if (block_size <= 0)
    {
        throw std::out_of_range("tile size must be positive");
    }

    validate_multiplication(mat1, mat2);

    const size_t nrow1 = mat1.nrow();
    const size_t ncol1 = mat1.ncol();
    const size_t ncol2 = mat2.ncol();

    Matrix ret(mat1.nrow(), mat2.ncol());

    for (size_t i = 0; i < nrow1; i++)
        for (size_t j = 0; j < ncol2; j++)
            ret(i, j) = 0;

    for (size_t i = 0; i < nrow1; i += block_size)
        for (size_t j = 0; j < ncol2; j += block_size)
            for (size_t l = 0; l < ncol1; l += block_size)
                for (size_t ii = i; ii < i + block_size && ii < nrow1; ii++)
                    for (size_t jj = j; jj < j + block_size && jj < ncol2; jj++)
                        for (size_t ll = l; ll < l + block_size && ll < ncol1; ll++)
                            ret(ii, jj) += mat1(ii, ll) * mat2(ll, jj);

    return ret;
}
namespace python
{

    struct calltag
    {
    };

} /* end namespace python */

namespace pybind11
{
    namespace detail
    {

        template <>
        struct process_attribute<python::calltag>
            : process_attribute_default<python::calltag>
        {

            static void postcall(function_call &call, handle &)
            {
                mark(call);
            }

        private:
            static void mark(function_call const &call)
            {
                object o = module::import("_matrix");
                std::string name = std::string(str(call.func.scope.attr("__name__")));
                name += std::string(call.func.name) + "_post_count";
                const size_t count = getattr(o, name.c_str(), int_(0)).cast<size_t>() + 1;
                setattr(o, name.c_str(), int_(count));
            }
        };

    } /* end namespace detail */
} /* end namespace pybind11 */

namespace python
{

    /**
     * Helper template for pybind11 class wrappers.
     */
    template <
        class Wrapper, class Wrapped, class Holder = std::unique_ptr<Wrapped>, class WrappedBase = Wrapped>
    /*
     * Use CRTP to detect type error during compile time.
     */
    class
        PYTHON_WRAPPER_VISIBILITY
            WrapBase
    {

    public:
        using wrapper_type = Wrapper;
        using wrapped_type = Wrapped;
        using wrapped_base_type = WrappedBase;
        using holder_type = Holder;
        using root_base_type = WrapBase<
            wrapper_type, wrapped_type, holder_type, wrapped_base_type>;
        using class_ = typename std::conditional_t<
            std::is_same<Wrapped, WrappedBase>::value, pybind11::class_<wrapped_type, holder_type>, pybind11::class_<wrapped_type, wrapped_base_type, holder_type>>;

        static wrapper_type &commit(pybind11::module &mod)
        {
            static wrapper_type derived(mod);
            return derived;
        }

        static wrapper_type &commit(pybind11::module &mod, char const *pyname, char const *pydoc)
        {
            static wrapper_type derived(mod, pyname, pydoc);
            return derived;
        }

        WrapBase() = delete;
        WrapBase(WrapBase const &) = default;
        WrapBase(WrapBase &&) = delete;
        WrapBase &operator=(WrapBase const &) = default;
        WrapBase &operator=(WrapBase &&) = delete;
        ~WrapBase() = default;

#define DECL_PYBIND_CLASS_METHOD_UNTAGGED(METHOD)                             \
    template <class... Args> /* NOLINTNEXTLINE(bugprone-macro-parentheses) */ \
    wrapper_type &METHOD(Args &&...args)                                      \
    {                                                                         \
        m_cls.METHOD(std::forward<Args>(args)...);                            \
        return *static_cast<wrapper_type *>(this);                            \
    }

#define DECL_PYBIND_CLASS_METHOD_TAGGED(METHOD)                               \
    template <class... Args> /* NOLINTNEXTLINE(bugprone-macro-parentheses) */ \
    wrapper_type &METHOD##_tagged(Args &&...args)                             \
    {                                                                         \
        m_cls.METHOD(std::forward<Args>(args)..., calltag());                 \
        return *static_cast<wrapper_type *>(this);                            \
    }

#define DECL_PYBIND_CLASS_METHOD(METHOD)      \
    DECL_PYBIND_CLASS_METHOD_UNTAGGED(METHOD) \
    DECL_PYBIND_CLASS_METHOD_TAGGED(METHOD)

        DECL_PYBIND_CLASS_METHOD(def)
        DECL_PYBIND_CLASS_METHOD(def_static)

        DECL_PYBIND_CLASS_METHOD(def_readwrite)
        DECL_PYBIND_CLASS_METHOD(def_readonly)
        DECL_PYBIND_CLASS_METHOD(def_readwrite_static)
        DECL_PYBIND_CLASS_METHOD(def_readonly_static)

        DECL_PYBIND_CLASS_METHOD(def_property)
        DECL_PYBIND_CLASS_METHOD(def_property_static)
        DECL_PYBIND_CLASS_METHOD(def_property_readonly)
        DECL_PYBIND_CLASS_METHOD(def_property_readonly_static)

#undef DECL_PYBIND_CLASS_METHOD
#undef DECL_PYBIND_CLASS_METHOD_TAGGED
#undef DECL_PYBIND_CLASS_METHOD_UNTAGGED

        class_ &cls() { return m_cls; }

    protected:
        template <typename... Extra>
        WrapBase(pybind11::module &mod, char const *pyname, char const *pydoc, const Extra &...extra)
            : m_cls(mod, pyname, pydoc, extra...)
        {
        }

    private:
        class_ m_cls;

    }; /* end class WrapBase */

    /**
     * Wrapper for the Matrix class.
     */
    class
        PYTHON_WRAPPER_VISIBILITY
            WrapMatrix
        : public WrapBase<WrapMatrix, Matrix>
    {

        friend root_base_type;

        WrapMatrix(pybind11::module &mod, char const *pyname, char const *pydoc)
            : root_base_type(mod, pyname, pydoc, pybind11::buffer_protocol())
        {

            namespace py = pybind11;

            (*this)
                // The Python constructor will be counted!
                .def_tagged(py::init<size_t, size_t>())
                .def_property_readonly("nrow", &Matrix::nrow)
                .def_property_readonly("ncol", &Matrix::ncol)
                .def_property_readonly("array", [](Matrix const &self)
                                       { return py::array_t<double>({self.nrow(), self.ncol()}, {sizeof(double) * self.ncol(), sizeof(double)}, self.m_buffer, py::cast(self)); })
                .def("__eq__", [](Matrix const &self, Matrix const &other)
                     { return self == other; })
                .def(
                    "__getitem__", [](Matrix const &self, std::tuple<size_t, size_t> idx)
                    { return self(std::get<0>(idx), std::get<1>(idx)); })
                .def(
                    "__setitem__", [](Matrix &self, std::tuple<size_t, size_t> idx, double value)
                    { return self(std::get<0>(idx), std::get<1>(idx)) = value; });

            mod.def("multiply_mkl", &multiply_mkl);
            mod.def("multiply_naive", &multiply_naive);
            mod.def("multiply_tile", &multiply_tile);
        }

    }; /* end class WrapMatrix */

} /* end namespace python */

PYBIND11_MODULE(_matrix, mod)
{
    python::WrapMatrix::commit(mod, "Matrix", "Matrix");
}

// vim: set ff=unix fenc=utf8 et sw=4 ts=4 sts=4: