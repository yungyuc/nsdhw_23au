#include <iostream>

class Matrix {
   public:
    Matrix(size_t nrow, size_t ncol)
        : m_nrow(nrow), m_ncol(ncol) {
        reset_buffer(nrow, ncol);
    }

    ~Matrix() {
        reset_buffer(0, 0);
    }

    Matrix(const Matrix &other) /* copy constructor */
        : m_nrow(other.nrow()), m_ncol(other.ncol()) {
        reset_buffer(other.nrow(), other.ncol());
        for (size_t i = 0; i < m_nrow; ++i) {
            for (size_t j = 0; j < m_ncol; ++j) {
                (*this)(i, j) = other(i, j);
            }
        }
    }

    Matrix(size_t nrow, size_t ncol, std::vector<double> const &vec)
        : m_nrow(nrow), m_ncol(ncol) {
        reset_buffer(m_nrow, m_nrow);
        size_t k = 0;
        for (size_t i = 0; i < m_nrow; ++i) {
            for (size_t j = 0; j < m_ncol; ++j) {
                (*this)(i, j) = vec[k];
                ++k;
            }
        }
    }

    Matrix &operator=(Matrix const &other) { /* copy */
        if (this == &other) {
            return *this;
        }
        if (m_nrow != other.m_nrow || m_ncol != other.m_ncol) {
            reset_buffer(other.m_nrow, other.m_ncol);
        }
        for (size_t i = 0; i < m_nrow; ++i) {
            for (size_t j = 0; j < m_ncol; ++j) {
                (*this)(i, j) = other(i, j);
            }
        }
        return *this;
    }

    Matrix &operator=(std::vector<double> const &vec) {
        if (size() != vec.size()) {
            throw std::out_of_range("number of elements mismatch");
        }

        size_t k = 0;
        for (size_t i = 0; i < m_nrow; ++i) {
            for (size_t j = 0; j < m_ncol; ++j) {
                (*this)(i, j) = vec[k];
                ++k;
            }
        }

        return *this;
    }

    double operator()(size_t row, size_t col) const {
        return m_buffer[row * m_ncol + col];
    }

    double &operator()(size_t row, size_t col) {
        return m_buffer[row * m_ncol + col];
    }

    bool operator==(const Matrix &other) const { /* determine equivalent  */
        if (other.nrow() != m_nrow || other.ncol() != m_ncol) return false;

        for (size_t i = 0; i < m_nrow; i++) {
            for (size_t j = 0; j < m_nrow; j++) {
                if ((*this)(i, j) != other(i, j)) return false;
            }
        }

        return true;
    }

    size_t nrow() const { return m_nrow; }
    size_t ncol() const { return m_ncol; }

    size_t size() const { return m_nrow * m_ncol; }
    double buffer(size_t i) const { return m_buffer[i]; }
    std::vector<double> buffer_vector() const {
        return std::vector<double>(m_buffer, m_buffer + size());
    }

    double *data() const { return m_buffer; }

   private:
    size_t index(size_t row, size_t col) const { return row * m_ncol + col; }

    void reset_buffer(size_t nrow, size_t ncol) {
        if (m_buffer) {
            delete[] m_buffer;
        }
        const size_t nelement = nrow * ncol;
        if (nelement) {
            m_buffer = new double[nelement]();
        } else {
            m_buffer = nullptr;
        }
        m_nrow = nrow;
        m_ncol = ncol;
    }
    size_t m_nrow;
    size_t m_ncol;
    double *m_buffer = nullptr;
};