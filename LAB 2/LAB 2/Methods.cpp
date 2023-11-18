#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

bool  Gaus(vector<int>&, vector<double>&, vector<vector<double>>&, vector<double>&);
bool  GausSh(vector<int>&, vector<vector<double>>&, int, int);
void  print(vector<int>&, vector<vector<double>>&, int);
int   Max(vector<int>&, vector<vector<double>>&, int, int);
void  swap(vector<int>&, int, int);

bool Gaus(vector<int>& p, vector<double>& x, vector<vector<double>>& J, vector<double>& F)
{
	vector<vector<double>> a = J;
	int n = p.size(), i, j;
	double sumx;
	for (int i = 0; i < n; i++) {
		a[i].push_back(F[i] * -1);
	}
	for (int k = 0; k < n; k++){
		if (GausSh(p, a, n, k)){
			print(p, a, n);
		}
		else {
			return 0;
		}
	}
	for (i = n - 1; i >= 0; i--){
		sumx = 0;
		for (j = i + 1; j < n; j++) {
			sumx += a[p[i]][j] * x[j];
		}
		cout << a[p[i]][n] - sumx << " = " << a[p[i]][n] << " - " << sumx << endl;
		x[i] = a[p[i]][n] - sumx;
	}
	for (i = 0; i < n; i++) {
		cout << "x" << i << " = " << setprecision(20) << fixed << x[i] << endl;
	}
	return 1;
}

bool GausSh(vector<int>& p, vector<vector<double>>& a, int n, int k)
{
	cout << "k = " << k << endl;
	cout << "------" << endl;
	print(p, a, n);
	int max = Max(p, a, n, k);
	cout << max << endl;
	swap(p, p[k], max);

	double del = a[max][k];
	cout << del << endl;
	for (int j = k; j < n + 1; j++) {
		a[max][j] /= del;
	}
	print(p, a, n);

	for (int i = k + 1; i < n; i++){
		del = a[p[i]][k];
		cout << "del = " << del << endl;
		for (int j = k; j < n + 1; j++){
			cout << a[p[i]][j] << " -= " << a[p[k]][j] << " * " << del << " [ "<< (a[p[k]][j] * del) <<" ] "<< endl;
			a[p[i]][j] -= (a[p[k]][j] * del);
		}
		print(p, a, n);
	}

	return 1;
}

void print(vector<int>& p, vector<vector<double>>& a, int n){
	int i, j;
	for (i = 0; i < n; i++){
		cout << p[i] << "   ";
		for (j = 0; j < n; j++)
			cout << setprecision(4) << fixed << setw(8) << a[i][j];
		cout << " = " << a[i][n];
		cout << endl;
	}
	cout << endl;
}

int Max(vector<int>& p, vector<vector<double>>& a, int n, int k){
	double max = 0;
	int maxs = p[k];
	cout << "  " << maxs << endl;
	for (int i = k; i < n; i++){
		if (abs(a[p[i]][k]) > max){
			cout << abs(a[p[i]][k]) << " > " << max << endl;
			max = abs(a[p[i]][k]);
			maxs = p[i];
		}
	}

	return maxs;
}

void swap(vector<int>& p, int k1, int k2){
	int s1 = 0, s2 = 0;;
	while (p[s1] != k1) {
		s1++;
	}
	while (p[s2] != k2) {
		s2++;
	}
	p[s1] = k2;
	p[s2] = k1;
}


void print(vector<double> mas) {
	for (int i = 0; i < mas.size(); i++) {
		cout << mas[i] << " ";
	}
	cout << endl << endl;
}

void print(vector<vector<double>> mas) {
	int n = mas[0].size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << mas[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Nev(vector<double>& F, vector<double> x) {
	F[0] = 1.5 * pow(x[0], 3) - pow(x[1], 2) - 1;
	F[1] = x[0] * pow(x[1], 3) - x[1] - 4;
}

void Jac(vector< vector<double>>& J, vector<double> x) {
	J[0][0] = 4.5 * pow(x[0], 2);
	J[0][1] = -2 * x[1];
	J[1][0] = pow(x[1], 3);
	J[1][1] = 3 * x[0] * pow(x[1], 2) - 1;
}

void Jac2(vector< vector<double>>& J, vector<double> x, double M) {
	J[0][0] = ((1.5 * pow(x[0] + M * x[0], 3) - pow(x[1], 2) - 1) - (1.5 * pow(x[0], 3) - pow(x[1], 2) - 1)) / (M * x[0]);
	J[0][1] = ((1.5 * pow(x[0], 3) - pow(x[1] + M * x[1], 2) - 1) - (1.5 * pow(x[0], 3) - pow(x[1], 2) - 1)) / (M * x[1]);
	J[1][0] = (((x[0] + M * x[0]) * pow(x[1], 3) - x[1] - 4) - (x[0] * pow(x[1], 3) - x[1] - 4)) / (M * x[0]);
	J[1][1] = ((x[0] * pow(x[1] + M * x[1], 3) - (x[1] + M * x[1]) - 4) - (x[0] * pow(x[1], 3) - x[1] - 4)) / (M * x[1]);
}

double findSystemMax(vector<double> x) {
	double x1 = 1.5 * pow(x[0], 3) - pow(x[1], 2) - 1;
	double x2 = x[0] * pow(x[1], 3) - x[1] - 4;
	if (abs(x1) > abs(x2)) {
		return abs(x1);
	}
	else {
		return abs(x2);
	}
}

double findAbsMax(vector<double> x, vector<double> x1) {
	int n = x.size();
	double max = 0;
	for (int i = 0; i < n; i++) {
		if (abs(x1[i]) < 1) {
			if (abs(x1[i] - x[i]) > max) {
				max = abs(x1[i] - x[i]);
			}
		}
		else {
			if (abs((x1[i] - x[i]) / x1[i]) > max)
				max = abs((x1[i] - x[i]) / x1[i]);
		}
	}
	return max;
}
