#include<iostream>
#include<fstream>
#include"algorithms.h"

int main()
{
	int n, d;
	double* X, * Y, *a;

	std::fstream data;
	data.open("data_complex.txt", std::ios::in);

	if (!data.good())
	{
		std::cout << "Couldn't find the file!" << std::endl;
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

	std::cout << "NUMBER OF DATA: " << n << std::endl;

	for (int i = 0; i < n; i++)
		std::cout << X[i] << "\t" << Y[i] << std::endl;

	approximation(X, Y, n, d, a);

	std::cout << std::endl;
	for (int i = d; i >= 0; i--)
		std::cout << a[i] << std::endl;

	delete[] a;
	delete[] X;
	delete[] Y;

	return 0;
}