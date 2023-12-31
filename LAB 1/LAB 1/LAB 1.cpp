#include "Gauss.h"
#include <iostream>
using namespace std;
// 1 2 1 -1 -2 2 0 1 1 1 1 2
int main()
{
    double** A, * b, * copyB, * x, *roots2, *roots1, fullError = 0.0;
    int n;
    cout << "Input equation count: ";
    cin >> n;
    A = new double* [n], b = new double[n], roots2 = new double[n], roots1 = new double[n], copyB = new double[n];
    double** copyA = new double *[n];
    for (int i = 0; i < n; i++) {
        A[i] = new double[n];
        copyA[i] = new double[n];
    }
    input(A, b, n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            copyA[i][j] = A[i][j];
        }
    }
    x = gauss(A, b, n);
    for (int i = 0; i < n; i++) {
        cout << "x[" << i << "]=" << x[i] << endl;
        roots1[i] = x[i];
    }
    cout << "residual vector: " << *residual(copyA, b, roots1, n, copyB) << endl;
    cout << "Norma: " << calculateResidualNorm(residual(A, b, roots1, n, copyB), n) << endl;
    solveAuxiliarySystem(A, x, n);
    for (int i = 0; i < n; i++){
        roots2[i] = x[i];
        cout << "roots2[" << i << "] = " << roots2[i] << endl;
    }

    cout << "Relative Error: " << relativeError(roots1, roots2, n) << endl;
    cin.get(); cin.get();

    delete[] roots1, roots2;
    return 0;
    
}
