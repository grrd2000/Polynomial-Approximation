#include<iostream>
#include"algorithms.h"

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

void approximation(double* X, double* Y, int n, int d, double* a)
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
	//	std::cout << sx[i] << std::endl;
	//}
	//
	//cout << "\n";
	//for (int i = 0; i < d + 1; i++)
	//{
	//	std::cout << sxy[i] << std::endl;
	//}
	//
	//std::cout << "\n";
	//for (int i = 0; i < d + 1; i++)
	//{
	//	for (int j = 0; j < d + 2; j++)
	//	{
	//		std::cout << AB[i][j] << std::endl;
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