#ifndef MATRIX_H
#define MATRIX_H

#include "allocator.h"
#include <vector>

class Matrix{
	private:
		int nrow_;
		int ncol_;
		std::vector<double, Allocator<double>> data_;
	public:
		Matrix(int nrow, int ncol);
		Matrix(const Matrix &m);
		Matrix(Matrix &&m);
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

		// Get data
		double *data();
		const double *data() const;
};

Matrix multiply_naive(const Matrix &mat1, const Matrix &mat2);

Matrix multiply_tile(const Matrix &mat1, const Matrix &mat2, int tile_size);

Matrix multiply_mkl( Matrix &mat1,  Matrix &mat2);

#endif