#include<vector>
#include<cmath>
#include<iostream>
#include<iomanip>
using namespace std;
double timeDerivate(double* u, double t, int n);

void eulerMethod(double* u, int n) {
	double tau = 0, tk = 0;
	double Eps = 0.001, T = 1, tauMax = 0.01;
	double* yk = new double(n);
	yk[0] = u[0], yk[1] = u[1];
	do {
		double* tempArray = new double(n);
		for (int i = 0; i < n; i++){
			tempArray[i] = timeDerivate(yk, tk, i);
		}
		if (!(Eps / (abs(tempArray[0]) + Eps / tauMax) > Eps / (abs(tempArray[1]) + Eps / tauMax))){
			tau = Eps / (abs(tempArray[0]) + Eps / tauMax);
		}
		else{
			tau = Eps / (abs(tempArray[1]) + Eps / tauMax);
		}
		for (int i = 0; i < n; i++){
			yk[i] += tau * abs(tempArray[i]);
		}
		tk += tau;
		cout << "tk" << setw(15) << "yk[0]" << setw(15) << "yk[1]" << endl << endl;
		for (int i = 0; i < n; i++){
			if (i == 0) {
				cout << tk << setw(15);
			}				
			cout << setw(15) << yk[i];
			if (i == n - 1) {
				cout << endl;
			}
		}
		if (tk + tau > T && tk < T){
			tk = T - tau;
		}
	} while (tk < T);
}


double timeDerivate(double* u, double t, int n)
{
	double Om = 2.5 + 1 / 40;
	if (n == 0) {
		return -u[0] * u[1] + ((t < 1e-9) ? 0.0 : (sin(t) / t));
	}
	else if (n == 1) {
		return -u[1] * u[1] + (Om * t) / (1 + t * t);
	}
	return 0;
}