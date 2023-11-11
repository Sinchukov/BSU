#include "Gauss.h"
using namespace std;




int main()
{
    double** A, * b, * x;
    int n;
    cout << "Input equation count: ";
    cin >> n;
    A = new double* [n], b = new double[n];
    for (int i = 0; i < n; i++) {
        A[i] = new double[n];
    }
    input(A, b, n);
    x = gauss(A, b, n);
    for (int i = 0; i < n; i++) {
        cout << "x[" << i << "]=" << x[i] << endl;
    }
    double* roots1 = new double[n];
    for (int i = 0; i < n; i++){
        roots1[i] = x[i];
    }
    //double* F1 = new double[n];
    //F1 = residual(A, b, x, n);
    //// Вычисление нормы вектора невязки
    //cout << "residual vector: " << *F1 << endl;
    //cout << "Norma: " << calculateResidualNorm(F1,n) << endl;

    cout << "residual vector: " << *residual(A, b, x, n) << endl;
    cout << "Norma: " << calculateResidualNorm(residual(A, b, x, n), n) << endl;


    // Решаем вспомогательную систему для проверки
    double* x_prime = new double[n];
    for (int i = 0; i < n; i++) {
        x_prime[i] = 1;
    }
    double* roots2 = new double[n];
    solve_auxiliary_system(A, x_prime, x, n);
    for (int i = 0; i < n; i++)
    {
        roots2[i] = x[i];
    }
    cout << "Solution of Ax = Ax':" << endl;
    for (int i = 0; i < n; i++) {
        cout << "roots2[" << i << "] = " << roots2[i] << endl;
    }

    double max_error = 0;
    for (int i = 0; i < n; i++) {
        double error = abs((roots2[i] - roots1[i]) / roots1[i]);
        if (error > max_error) {
            max_error = error;
        }
    }
    cout << "Relative Error: " << max_error << endl;

    for (int i = 0; i < n; i++) {
        b[i] = A[i][i] * x_prime[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                b[i] -= A[i][j] * x_prime[j];
            }
        }
    }

    /*double* F2 = new double[n];
    F2 = residual(A, b, x, n);
    cout << "residual vector: " << *F2 << endl;
    cout << "Norma: " << calculateResidualNorm(F2, n) << endl;*/

    cout << "residual vector: " << *residual(A, b, x, n) << endl;
    cout << "Norma: " << calculateResidualNorm(residual(A, b, x, n), n) << endl;
    cin.get(); cin.get();

    delete[] roots1, roots2, x_prime;
    return 0;
}