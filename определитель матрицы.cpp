#include <iostream>

using namespace std;

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

	void ch_rows(int row1, int row2);
	double det() const;

	~Matrix() { delete[] elements; }

};

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

double Matrix::at(int i, int j) const {
	return elements[i*m + j];
}

void Matrix::operator=(const Matrix& mat) {
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
	if (A.n != n || A.m != m) throw "Matrix::operator+ - wrong dimension";
	Matrix ans(n, m);
	for (int i = 0; i < n*m; ++i) {
		ans.elements[i] = elements[i]+A.elements[i];
	}
	return ans;
}

Matrix Matrix::operator-(const Matrix& A) const {
	if (A.n != n || A.m != m) throw "Matrix::operator+ - wrong dimension";
	return *this + (A*(double)(-1));
}

Matrix Matrix::operator*(const Matrix& A) const{
	if (m != A.n) throw "Matrix::operator* - wrong dimension";
	Matrix ans(n, A.m);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < A.m; ++j) {
			for (int k = 0; k < m; ++k) ans.at(i, j) += (double)(at(i, k) * A.at(k, j));
		}
	}
	return ans;
}

void Matrix::ch_rows(int row1, int row2) {
    for (int i = 0; i < m; ++i) {
        double tmp = at(row2, i);
        at(row2, i) = at(row1, i);
        at(row1, i) = tmp;
    }
}

double Matrix::det() const {
    if (n != m) throw "Matrix::det - wrong dimension";
    Matrix mat(n, m, elements);
    if (n != m) return 0;
    else {
        double det = 1;
        for (int i = 0; i < n; ++i) {
            if (mat.at(i, i) == 0) {
                bool flag = true;
                for (int j = i+1; j < n; ++j) {
                    if (mat.at(j, i) != 0) {
                        mat.ch_rows(i, j);
                        det *= -1;
                        flag = false;
                        break;
                    }
                }
                if (flag) throw "Warning! det = 0";
            }
            double a = mat.at(i, i);
            for (int j = i+1; j < n; ++j) {
                if (mat.at(j, i) != 0) {
                    double b = mat.at(j, i);
                    for (int k = i; k < m; ++k) mat.at(j, k) -= mat.at(i, k)*(b/a);
                }
            }
        }
        for (int i = 0; i < n; ++i) det *= mat.at(i, i);
        if (det == 0) throw "Warning! det = 0";
        if (det < 0) throw "Warning! det < 0";
        return det;
    }
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

int main()
{
    int n;
    cout << "Enter number of rows: ";
    cin >> n;
    Matrix A(n, n);
    cin >> A;
    try {
        cout << "Det(A) = " << A.det() << endl;
    } catch (const char * str) {
        cout << str << endl;
    }
}
