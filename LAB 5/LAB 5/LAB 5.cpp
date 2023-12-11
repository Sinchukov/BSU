#include <iostream>
#include <iomanip>
#include <math.h>
#include "Integral.h"
using namespace std;

int main()
{
	double a =  1.3, b = 2.621; //borders [a,b] & [c,d]
	double a2 = -1, b2 = 1, c2 = -1, d2 = 1;
	double epsilon = pow(10, -4); //error
	cout << "epsilon = 10^-4" << endl;
	cout << "Trapeze: " << trapeze(a, b, fun, epsilon) << endl;
	cout << "basicSimp: " << basicSimp(a, b, fun, epsilon) << endl;
	cout << "cubeSimp: " << cubeSimp(a2, b2, c2, d2, DoubleFunkAgrument) << endl;
	epsilon = pow(10, -5);
	cout << endl << "epsilon = 10^-5" << endl;
	cout << "Trapeze: " << trapeze(a, b, fun, epsilon) << endl;
	cout << "basicSimp: " << basicSimp(a, b, fun, epsilon) << endl;
	cout << "cubeSimp: " << cubeSimp(a2, b2, c2, d2, DoubleFunkAgrument) << endl;
	cout << endl;
}

