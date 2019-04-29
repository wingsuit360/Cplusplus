#ifndef MMATRIX_H_INCLUDED
#define MMATRIX_H_INCLUDED

#include<iostream>

struct Matrix {
	const int n;
	const int m;
	double* elements;

	Matrix() : n(1), m(1), elements(new double[1]) {elements[0] = 0;}
	Matrix(const Matrix&);
	Matrix(int, int);
	Matrix(const int, const int, double*);

	double& at(int, int);
	double at(int, int) const;

	void operator=(const Matrix&);
	Matrix transpose() const;

	Matrix operator*(double) const;
	Matrix operator+(const Matrix&) const;
	Matrix operator-(const Matrix&) const;
	Matrix operator*(const Matrix&) const;

	~Matrix() { delete[] elements; }
};

std::istream& operator >> (std::istream& is, Matrix& mat);
std::ostream& operator << (std::ostream& os, const Matrix& mat);

#endif // MMATRIX_H_INCLUDED
