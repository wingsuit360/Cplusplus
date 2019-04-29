#include "mmatrix.h"

using namespace std;

Matrix::Matrix(const Matrix& M) :
    n(M.n),
    m(M.m),
    elements(new double[n*m])
{
    for (int i = 0; i < n*m; i++)
        elements[i] = M.elements[i];
}

Matrix::Matrix(int rows, int columns) :
    n(rows),
    m(columns),
    elements(new double[n * m])
{
	for (int i = 0; i < n*m; i++)
		elements[i] = 0;
}

Matrix::Matrix(const int rows, const int columns, double* el) :
    n(rows),
    m(columns),
    elements(new double[n * m])
{
    for (int i = 0; i < n*m; i++)
        elements[i] = el[i];
}

double& Matrix::at(int i, int j) {
    return elements[i*m + j];
}

double Matrix::at(int i, int j) const {				//??????????? ?????
	return elements[i*m + j];
}

void Matrix::operator=(const Matrix& mat) {    // Copy-operator
	for (int i = 0; i < m*n; i++) {
		elements[i] = mat.elements[i];
	}
}

Matrix Matrix::transpose() const {
	Matrix a(m, n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			a.at(j, i) = at(i, j);
		}
	}
	return a;
}

Matrix Matrix::operator*(double k) const {
	Matrix ans(n, m);
	for (int i = 0; i < n*m; ++i) {
		ans.elements[i] = elements[i]*k;
	}
	return ans;
}

Matrix Matrix::operator+(const Matrix& A) const{
	if (A.n != n || A.m != m) throw "Matrix::operator+ - wrong dimention";
	Matrix ans(n, m);
	for (int i = 0; i < n*m; ++i) {
		ans.elements[i] = elements[i]+A.elements[i];
	}
	return ans;
}

Matrix Matrix::operator-(const Matrix& A) const {
	if (A.n != n || A.m != m) throw "Matrix::operator+ - wrong dimention";
	return *this + (A*(double)(-1));
}

Matrix Matrix::operator*(const Matrix& A) const{
	if (m != A.n) throw "Matrix::operator* - wrong dimention";
	Matrix ans(n, A.m);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < A.m; ++j) {
			for (int k = 0; k < m; ++k) ans.at(i, j) += (double)(at(i, k) * A.at(k, j));
		}
	}
	return ans;
}

istream& operator >> (istream& is, Matrix& mat)
{
	for (int row = 0; row < mat.n; ++row)
		for (int col = 0; col < mat.m; ++col)
			is >> mat.at(row, col);
	return is;
}

ostream& operator << (ostream& os, const Matrix& mat)
{
	//os << mat.n << ' ' << mat.m << endl;

	for (int row = 0; row < mat.n; ++row)
	{
		for (int col = 0; col < mat.m; ++col)
			os << mat.at(row, col) << ' ';
		os << endl;
	}
	return os;
}
