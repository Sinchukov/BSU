#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include "Header.h"

using namespace std;

int main()
{
	int n = 2;
	vector<double> x, x1, deltx, F;
	vector<int> p;
	vector<vector<double>> J;
	J.resize(n);
	for (int i = 0; i < n; i++)
	{
		F.push_back(0);
		x1.push_back(0);
		deltx.push_back(0);
		p.push_back(i);
		for (int j = 0; j < n; j++)
			J[i].push_back(0);
	}
	x.push_back(1);
	x.push_back(1);
	double e1 = 0.000000001, e2 = 0.000000001, d1 = 1, d2 = 1;
	int k = 1, NIT = 100;
	cout << "k				d1				d2" << endl;
	while ((d1 > e1 || d2 > e2) && k < NIT)
	{
		Nev(F, x);
		//Jac(J, x);
		Jac2(J, x, 0.01);

		if (!Gaus(p, deltx, J, F))
			return 0;

		for (int i = 0; i < n; i++)
			x1[i] = x[i] + deltx[i];

		d1 = fd1(x);
		d2 = fd2(x, x1);
		cout << setprecision(20) << fixed << k << "\t\t" << d1 << "\t\t" << d2 << endl;
		k++;
		x = x1;
		if (k >= NIT)
			cout << "ERROR: IER = 2" << endl;
	}

	print(x);

}
