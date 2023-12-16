#include <mkl.h>
#include <vector>

class Matrix {
   public:
	size_t m_nrow;
	size_t m_ncol;

	Matrix(size_t _nrow, size_t _ncol)
		: m_nrow(_nrow), m_ncol(_ncol) {
		size_t nelement = m_nrow * m_ncol;
		m_buffer.resize(nelement);
	}

	~Matrix() = default;

	double *data() const { return (double *)&m_buffer[0]; }

	double operator()(size_t row, size_t col) const { return m_buffer[row * m_ncol + col]; }
	double &operator()(size_t row, size_t col) { return m_buffer[row * m_ncol + col]; }

	bool operator==(const Matrix &rhs) const {
		for (size_t row = 0; row < m_nrow; row++) {
			for (size_t col = 0; col < m_ncol; col++) {
				if ((*this)(row, col) != rhs(row, col)) {
					return false;
				}
			}
		}
		return true;
	}

	size_t nrow() const { return m_nrow; }
	size_t ncol() const { return m_ncol; }

   private:
	std::vector<double> m_buffer = std::vector<double>();
};

Matrix multiply_naive(Matrix& ma, Matrix& mb) {
	Matrix res(ma.nrow(), mb.ncol());
	for (size_t row = 0; row < ma.nrow(); row++) {
		for (size_t col = 0; col < mb.ncol(); col++) {
			for (size_t i = 0; i < ma.ncol(); i++) {
				res(row, col) += ma(row, i) * mb(i, col);
			}
		}
	}

	return res;
}

Matrix multiply_tile(const Matrix &A, const Matrix &B, size_t Block) {
    Matrix C(A.nrow(), B.ncol());
    size_t N = A.nrow();
    size_t s = Block;

    for (size_t i = 0; i < N; i += s) {
        for (size_t j = 0; j < N; j += s) {
            for (size_t k = 0; k < N; k += s) {
                for (size_t k1 = k; k1 < std::min(N, k + s); k1++) {
                    for (size_t i1 = i; i1 < std::min(N, i + s); i1++) {
                        for (size_t j1 = j; j1 < std::min(N, j + s); j1++) {
                            C(i1, j1) += A(i1, k1) * B(k1, j1);
                        }
                    }
                }
            }
        }
    }

    return C;

}

Matrix multiply_mkl(Matrix& A, Matrix& B) {
	int m = A.nrow();
	int k = A.ncol();
	int n = B.ncol();
	double alpha = 1.0, beta = 0.0;

	Matrix res(A.nrow(), B.ncol());
    
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
				m, n, k, alpha, A.data(), k, B.data(), n, beta, res.data(), n);

	return res;
}