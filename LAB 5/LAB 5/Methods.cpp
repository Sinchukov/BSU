#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

double fun(double x) //default function
{
	double f = pow(pow(x,3) - 1, -1 / 2);
	return f;
}

double DoubleFunkAgrument(int i, int j, int n) //F(x,y) ���
{
	double a = -1, b = -1, A = 1, B = 1;
	double h = (A - a) / (2 * n), k = (B - b) / (2 * n);
	double x = a + i * h, y = b + j * k;
	double F = 4 - pow(x, 2) - pow(y, 2);
	if (x > 1 || y > 1)
		return 0;
	else
		return F;
}

double trapeze(double a, double b, double(*function)(double), double e)
{
	int n = 2;
	double h = (b - a) / n, I = function(a) + function(b), I2, x = a;
	for (int i = 0; i < n - 1; i++)
	{
		x += h;
		I += 2 * function(x);
	}
	I *= h / 2;

	do
	{
		n *= 2;
		h = (b - a) / n;
		I2 = I;
		I = function(a) + function(b);
		x = a;
		for (int i = 0; i < n - 1; i++)
		{
			x += h;
			I += 2 * function(x);
		}
		I *= h / 2;
	} while (abs(I - I2) > 3 * e);
	double R;

	R = abs((I2 - I) / (pow(0.5, 2) - 1));

	cout << " (Error " << R << ")" << "\t";
	return I;
}

double basicSimp(double a, double b, double(*function)(double), double e)
{
	int splitNumber = 4;
	double h = (b - a) / splitNumber, I = function(a) + function(b), I2, x = a;
	for (int i = 0; i < splitNumber - 1; i += 2)
	{
		x += h;
		I += 4 * function(x);
		x += h;
		I += 2 * function(x);
	}
	I *= h / 3;

	do
	{
		splitNumber *= 2;				//splitNumber == n
		cout << splitNumber << endl; 
		h = (b - a) / splitNumber;
		I2 = I;
		I = function(a) + function(b);
		x = a;
		for (int i = 0; i < splitNumber - 1; i += 2)
		{
			x += h;
			I += 4 * function(x);
			x += h;
			I += 2 * function(x);
		}
		I *= h / 3;
	} while (abs(I - I2) > 15 * e);
	double R;

	R = (I2 - I) / (pow(0.5, 4) - 1);

	cout << " (Error " << R << ")" << "\t";
	return I;
}

double cubeSimp(double a, double b, double c, double d, double (*function)(int, int, int), double e)
{
	int splitNumber = 4, m = splitNumber;
	double h = (b - a) / (2 * splitNumber), k = (d - c) / (2 * m);    //splitNumber == n
	double I = 0, I2;

	for (int i = 0; i <= splitNumber; i++)
	{
		for (int j = 0; j <= m; j++)
		{
			I += function(2 * i, 2 * j, splitNumber) + function(2 * i + 2, 2 * j, splitNumber) + function(2 * i + 2, 2 * j + 2, splitNumber) + function(2 * i, 2 * j + 2, splitNumber) +
				4 * (function(2 * i + 1, 2 * j, splitNumber) + function(2 * i + 2, 2 * j + 1, splitNumber) + function(2 * i + 1, 2 * j + 2, splitNumber) + function(2 * i, 2 * j + 1, splitNumber)) +
				16 * function(2 * i + 1, 2 * j + 1, splitNumber);
		}
	}
	I *= h * k / 9;

	do
	{
		splitNumber *= 2;
		h = (b - a) / (2 * splitNumber);
		k = (d - c) / (2 * m);
		I2 = I;
		I = 0;
		for (int i = 0; i <= splitNumber; i++)
		{
			for (int j = 0; j <= m; j++)
			{
				I += function(2 * i, 2 * j, splitNumber) + function(2 * i + 2, 2 * j, splitNumber) + function(2 * i + 2, 2 * j + 2, splitNumber) + function(2 * i, 2 * j + 2, splitNumber) +
					4 * (function(2 * i + 1, 2 * j, splitNumber) + function(2 * i + 2, 2 * j + 1, splitNumber) + function(2 * i + 1, 2 * j + 2, splitNumber) + function(2 * i, 2 * j + 1, splitNumber)) +
					16 * function(2 * i + 1, 2 * j + 1, splitNumber);
			}
		}
		I *= h * k / 9;
	} while (abs(I - I2) > 15 * e);

	cout << "\t";
	return I;
}