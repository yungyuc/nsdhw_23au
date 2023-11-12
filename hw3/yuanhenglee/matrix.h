#ifndef MATRIX_H
#define MATRIX_H

class Matrix{
	public:
		Matrix(int nrow, int ncol);
		Matrix(const Matrix &m);
		// Matrix &operator=(const Matrix &m);
		~Matrix();

		// Getters
		double operator()(int i, int j) const;

		// Setters
		double &operator()(int i, int j);

		// Properties
		int nrow() const;
		int ncol() const;
		
		// Equality
		bool operator==(const Matrix &m) const;

		double *data_;
	private:
		int nrow_;
		int ncol_;

};

Matrix multiply_naive(const Matrix &mat1, const Matrix &mat2);

Matrix multiply_tile(const Matrix &mat1, const Matrix &mat2, int tile_size);

Matrix multiply_mkl(const Matrix &mat1, const Matrix &mat2);

#endif