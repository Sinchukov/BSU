#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

double fun(double x){ //default function
	double f = pow(pow(x,3) - 1, -1 / 2);
	return f;
}

double DoubleFunkAgrument(int i, int j, int n){ //F(x,y) тло
	double a = -1, b = -1, A = 1, B = 1;
	double h = (A - a) / (2.0 * n), k = (B - b) / (2.0 * n);
	double x = a + i * h, y = b + j * k;
	double F = 4 - pow(x, 2) - pow(y, 2);
	if (x > 1 || y > 1) {
		return 0;
	}
	else {
		return F;
	}
}

double trapeze(double a, double b, double(*function)(double), double e){
	int n = 2;
	double h = (b - a) / n, I = function(a) + function(b), I2, x = a, R;
	for (int i = 0; i < n - 1; i++){
		x += h;
		I += 2 * function(x);
	}
	I *= h / 2;
	do{
		n *= 2;
		h = (b - a) / n;
		I2 = I;
		I = function(a) + function(b);
		x = a;
		for (int i = 0; i < n - 1; i++){
			x += h;
			I += 2 * function(x);
		}
		I *= h / 2;
	} while (abs(I - I2) > 3 * e);
	R = abs((I2 - I) / (pow(0.5, 2) - 1));
	cout << " (Error " << R << ")" << "\t";
	return I;
}

double basicSimp(double a, double b, double(*function)(double), double e){
	int n = 4;
	double h = (b - a) / n, x = a + h, I2 = 0.0, I = function(a) + function(b);
	for (int i = 1; i < n; i++){
		if (i % 2 == 0){
			I2 += 2 * function(x);
		}
		else{
			I2 += 4 * function(x);
		}
		x += h;
	}
	I = (I + I2) * h / 3;
	do{
		n *= 2;
		h = (b - a) / n;
		double Inew = function(a) + function(b), xnew = a + h;;
		for (int i = 1; i < n; i++){
			if (i % 2 == 0){
				Inew += 2 * function(xnew);
			}
			else{
				Inew += 4 * function(xnew);
			}
			xnew += h;
		}
		Inew = (Inew + I2) * h / 3;
		I2 = I;
		I = Inew;
	} while (abs(I - I2) > 15 * e);
	double R = (I - I2) / 15;
	cout << " (Error " << R << ")" << "\t";
	return I;
}

double cubeSimp(double a, double b, double c, double d, double (*DoubleFunkAgrument)(int, int, int)){

	int splitNumber = 4, m = splitNumber;
	double h = (b - a) / (2.0 * splitNumber), k = (d - c) / (2.0 * m);    //splitNumber == n
	double I = 0;
	for (int i = 0; i < splitNumber; i++){
		for (int j = 0; j < m; j++){
			I += DoubleFunkAgrument(2 * i, 2 * j, splitNumber) + DoubleFunkAgrument(2 * i + 2, 2 * j, splitNumber) + DoubleFunkAgrument(2 * i + 2, 2 * j + 2, splitNumber) + DoubleFunkAgrument(2 * i, 2 * j + 2, splitNumber) +
			4 * (DoubleFunkAgrument(2 * i + 1, 2 * j, splitNumber) + DoubleFunkAgrument(2 * i + 2, 2 * j + 1, splitNumber) + DoubleFunkAgrument(2 * i + 1, 2 * j + 2, splitNumber) + DoubleFunkAgrument(2 * i, 2 * j + 1, splitNumber)) +
			16 * DoubleFunkAgrument(2 * i + 1, 2 * j + 1, splitNumber);
		}	
	}
	I *= h * k / 9;
	cout << "I: " << I << endl;
	return I;
  }