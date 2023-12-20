#include<iostream>
#include<iomanip>
#include<vector>
#include"Euler.h"
using namespace std;
int main() {
	int n = 2;
	double* u = new double(n);
	u[0] = 0, u[1] = -0.412;
	eulerMethod(u, 2);
	return 0;
}