#include <iostream>
#include <iomanip>
#include <math.h>
#include "Header.h"
using namespace std;

int main()
{
	double a = 1.3, b = 2.621 , c = -1, d = 1; //borders [a,b] & [c,d]
	double epsilon = pow(10, -4); //error
	cout << "epsilon = 10^-4" << endl;
	cout << "Trapeze: " << trapeze(a, b, fun, epsilon) << endl;
	cout << "basicSimp: " << basicSimp(a, b, fun, epsilon) << endl;
	cout << "cubeSimp: " << cubeSimp(a, b, c, d, DoubleFunkAgrument, epsilon) << endl;
	epsilon = pow(10, -5);
	cout << endl << "epsilon = 10^-5" << endl;
	cout << "Trapeze: " << trapeze(a, b, fun, epsilon) << endl;
	cout << "basicSimp: " << basicSimp(a, b, fun, epsilon) << endl;
	cout << "cubeSimp: " << cubeSimp(a, b, c, d, DoubleFunkAgrument, epsilon) << endl;
	cout << endl;
}

