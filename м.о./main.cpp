#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>
#include "mmatrix.h"

using namespace std;

double to_double(string s)
{
    double n;
    stringstream ss;
    ss << s;
    ss >> n;
    return n;
}

void load(istream& in, Matrix& X, Matrix& y)
{
    string str;
    for (int i = 0; i < X.n; ++i)
    {
        getline(in, str);
        X.at(i, 0) = 1;
        for (int j = 1; j < X.m; ++j)
        {
            int n;
            string x = str.substr(0, n = str.find(','));
            str = str.substr(n+1);
            X.at(i, j) = to_double(x);
        }
        y.at(i, 0) = to_double(str);
    }
}

double cost(const Matrix& X, const Matrix& y, const Matrix& th)
{
	return ((((X*th - y).transpose())*(X*th - y))*(1/(2*(X.n)))).at(0, 0);
}

Matrix& grad(const Matrix& X, const Matrix& y, Matrix& th, double a, int it)
{
	for (int i = 0; i < it; ++i)
    {
        th = th - (((X.transpose())*(X*th - y))*(a/X.n));
	}
	return th;
}

Matrix normalize(const Matrix& X, vector<double>& mu, vector<double>& mean)
{
    mu.push_back(0);
    mean.push_back(1);
    Matrix nX(X);
    for (int i = 1; i < X.m; ++i)
    {
        double Min, Max, Sum;
        for (int j = 0; j < X.n; ++j)
        {
            if (j == 0) {
                Min = X.at(j, i);
                Min = X.at(j, i);
                Min = X.at(j, i);
            }
            else
            {
                if (X.at(j, i) > Max) Max = X.at(j, i);
                if (X.at(j, i) < Min) Min = X.at(j, i);
                Sum += X.at(j, i);
            }
        }
        for (int j = 0; j < X.n; ++j)
        {
            nX.at(j, i) = (X.at(j, i) - (Sum/X.n))/(Max - Min);
        }
        mu.push_back(Max-Min);
        mean.push_back(Sum/X.n);
    }
    return nX;
}

int main()
{
    Matrix X(97, 2);
	Matrix y(97, 1);
	ifstream in("data1.txt");
	load(in, X, y);
	in.close();
	Matrix th(2, 1);
	th = grad(X, y, th, 0.01, 1500);
	Matrix x(1, 2);
	x.at(0, 0) = 1;
	cout << "Enter the population: ";
	cin >> x.at(0, 1);
	cout << "\nResult for " << x.at(0, 1) << ": ";
	x.at(0, 1) /= 10000;
	cout << (x*th)*10000 << endl;
	in.close();

	Matrix XM(47, 3);
	Matrix ym(47, 1);
	ifstream inm("data2.txt");
	load(inm, XM, ym);
	Matrix NXM(XM);
	vector<double> mu;
	vector<double> mean;
	NXM = normalize(XM, mu, mean);
	Matrix thm(3, 1);
	thm = grad(NXM, ym, thm, 1, 700);
	Matrix xm(1, 3);
	xm.at(0, 0) = 1;
	cout << "Enter space: ";
	cin >> xm.at(0, 1);
	xm.at(0, 1) = (xm.at(0, 1) - mean[1])/mu[1];
	cout << "Enter number of rooms: ";
	cin >> xm.at(0, 2);
	xm.at(0, 2) = (xm.at(0, 2) - mean[2])/mu[2];
	cout << "Price: " << xm*thm;
}
