#include "Gauss.h"
#include <iostream>
using namespace std;

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
    // Решаем вспомогательную систему для проверки  
    solve_auxiliary_system(A, x, n);
    for (int i = 0; i < n; i++) {
        roots2[i] = x[i];
        cout << "roots2[" << i << "] = " << roots2[i] << endl;
        fullError += relativeError(roots1[i], roots2[i]);
    }
    cout << "Relative Error: " << fullError << endl;
    for (int i = 0; i < n; i++) {
        b[i] = A[i][i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                b[i] -= A[i][j];
            }
        }
    }
    cout << "residual vector: " << *residual(A, b, x, n) << endl;
    cout << "Norma: " << calculateResidualNorm(residual(A, b, x, n), n) << endl;
    cin.get(); cin.get();

    delete[] roots1, roots2;
    return 0;
}
