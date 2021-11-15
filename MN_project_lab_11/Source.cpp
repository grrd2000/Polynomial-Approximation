#include<iostream>
#include<fstream>

using namespace std;

void gauss(double** AB, double* a, int n)
{
	int i, j, k;
	double q, s;

	for (i = 0; i < n - 1; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			q = -AB[j][i] / AB[i][i];

			for (k = i + 1; k <= n; k++)
				AB[j][k] += q * AB[i][k];
		}
	}

	for (i = n - 1; i >= 0; i--)
	{
		s = AB[i][n];

		for (j = n - 1; j >= i + 1; j--)
			s -= AB[i][j] * a[j];

		a[i] = s / AB[i][i];
	}
}

void approximation(double* X, double* Y, int n, int d, double *a)
{
	double** AB, ** pxi, * sxy, * sx;
	sxy = new double[d + 1];
	sx = new double[2 * d + 1];
	AB = new double* [d + 1];
	pxi = new double* [2 * d + 1];
	for (int i = 0; i < d + 1; i++) AB[i] = new double[d + 2];
	
	for (int i = 0; i < 2 * d + 1; i++)
	{
		sx[i] = 0;
		pxi[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			pxi[i][j] = 1;
		}
	}

	for (int i = 0; i < d + 1; i++)
	{
		sxy[i] = 0;
	}

	for (int i = 1; i < 2 * d + 1; i++)
	{
		for (int k = i; k < 2 * d + 1; k++)
		{
			for (int j = 0; j < n; j++)
			{
				pxi[k][j] *= X[j];
			}
		}
	}
	
	for (int i = 0; i < 2 * d + 1; i++)
	{
		for (int j = 0; j < n; j++)
		{
			sx[i] += pxi[i][j];
		}
	}

	for (int i = 0; i < d + 1; i++)
	{
		for (int j = 0; j < n; j++)
		{
			sxy[i] += pxi[i][j] * Y[j];
		}
	}

	for (int i = 0; i < d + 1; i++)
	{
		for (int k = 0; k < d + 1; k++)
		{
			AB[i][k] = sx[i + k];
		}
		AB[i][d + 1] = sxy[i];
	}

	gauss(AB, a, d + 1);

	//cout << "\n";
	//for (int i = 0; i < 2 * d + 1; i++)
	//{
	//	cout << sx[i] << endl;
	//}
	//
	//cout << "\n";
	//for (int i = 0; i < d + 1; i++)
	//{
	//	cout << sxy[i] << endl;
	//}
	//
	//cout << "\n";
	//for (int i = 0; i < d + 1; i++)
	//{
	//	for (int j = 0; j < d + 2; j++)
	//	{
	//		cout << AB[i][j] << endl;
	//	}
	//}

	//deletion
	for (int i = 0; i < d + 1; i++) delete[] AB[i];
	delete[] AB;
	for (int i = 0; i < 2 * d + 1; i++) delete[] pxi[i];
	delete[] pxi;
	delete[] sxy;
	delete[] sx;
}

int main()
{
	int n, d;
	double* X, * Y, *a;

	fstream data;
	data.open("data_complex.txt", ios::in);

	if (!data.good())
	{
		cout << "Couldn't find the file!" << endl;
		exit(0);
	}

	data >> d;
	data >> n;

	a = new double[d + 1];
	X = new double[n];
	Y = new double[n];

	for (int i = 0; i < n; i++)
	{
		data >> X[i];
		data >> Y[i];
	}

	data.close();

	cout << "NUMBER OF DATA: " << n << endl;

	for (int i = 0; i < n; i++)
		cout << X[i] << "\t" << Y[i] << endl;

	approximation(X, Y, n, d, a);

	cout << endl;
	for (int i = d; i >= 0; i--)
		cout << a[i] << endl;

	delete[] a;
	delete[] X;
	delete[] Y;

	return 0;
}