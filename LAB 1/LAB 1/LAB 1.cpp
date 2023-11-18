#include "Gauss.h"
#include <iostream>
using namespace std;
//3 1 2 1 -1 -2 2 0 1 1 1 1 2
int main()
{
    double** A, * b, * x, *roots2, *roots1, fullError = 0.0;
    int n;
    cout << "Input equation count: ";
    cin >> n;
    A = new double* [n], b = new double[n], roots2 = new double[n], roots1 = new double[n];
    for (int i = 0; i < n; i++) {
        A[i] = new double[n];
    }
    input(A, b, n);
    x = gauss(A, b, n);
    for (int i = 0; i < n; i++) {
        cout << "x[" << i << "]=" << x[i] << endl;
        roots1[i] = x[i];
    }
    cout << "residual vector: " << *residual(A, b, x, n) << endl;
    cout << "Norma: " << calculateResidualNorm(residual(A, b, x, n), n) << endl;
    solveAuxiliarySystem(A, x, n);
    for (int i = 0; i < n; i++){
        roots2[i] = x[i];
        cout << "roots2[" << i << "] = " << roots2[i] << endl;
    }

    cout << "Relative Error: " << relativeError(roots1, roots2, n) << endl;
    cin.get(); cin.get();

    delete[] roots1, roots2;
    return 0;
    //void solve_auxiliary_system(double** A, double* x_prime, double*& x, int n) {
    //    // Решаем систему Ax' = b методом Гаусса
    //    double* b = new double[n];
    //    for (int i = 0; i < n; i++) {
    //        b[i] = A[i][i] * x_prime[i];
    //        for (int j = 0; j < n; j++) {
    //            if (i != j) {
    //                b[i] -= A[i][j] * x_prime[j];
    //            }
    //        }
    //    }
    //    double* z = gauss(A, b, n);
    //    // Решаем систему Ly = z
    //    double** L = new double* [n];
    //    for (int i = 0; i < n; i++) {
    //        L[i] = new double[n];
    //        for (int j = 0; j < n; j++) {
    //            if (i == j) {
    //                L[i][j] = 1;
    //            }
    //            else {
    //                L[i][j] = A[i][j];
    //            }
    //        }
    //    }
    //    double* y = new double[n];
    //    for (int i = 0; i < n; i++) {
    //        double sum = 0;
    //        for (int j = 0; j < i; j++) {
    //            sum += L[i][j] * y[j];
    //        }
    //        y[i] = z[i] - sum;
    //    }
    //    // Решаем систему Dz = y
    //    double* d = new double[n];
    //    for (int i = 0; i < n; i++) {
    //        d[i] = A[i][i];
    //        for (int j = 0; j < i; j++) {
    //            d[i] -= L[i][j] * L[i][j] * d[j];
    //        }
    //    }
    //    for (int i = 0; i < n; i++) {
    //        y[i] /= d[i];
    //    }
    //    // Решаем систему Lt x = z
    //    for (int i = n - 1; i >= 0; i--) {
    //        double sum = 0;
    //        for (int j = i + 1; j < n; j++) {
    //            sum += L[j][i] * x[j];
    //        }
    //        x[i] = (y[i] - sum) / L[i][i];
    //    }
    //    // Освобождаем память
    //    delete[] b, delete[] z, delete[] y;
    //    for (int i = 0; i < n; i++) {
    //        delete[] L[i];
    //    }
    //    delete[] L;
    //}
}
