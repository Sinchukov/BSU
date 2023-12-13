#include <cmath>
#include <vector>
#include<iostream>
using namespace std;
vector<double> gaussElimination(const vector<vector<double>>& A, const vector<double>& B);
vector<double> backSubstitution(const vector<vector<double>>& augmentedMatrix, int n);
void forwardElimination(vector<vector<double>>& augmentedMatrix, int n);

double function1(const double& x01, const double& x02) {

    return 2 * pow(x01, 3) - pow(x02, 2) - 1;
}
double function2(const double& x01, const double& x02) {

    return x01 * pow(x02, 3) - x02 - 4;
}
double J1Dx01(const double& x01, const double& x02) {
    return 6 * x01 * x01;
}

double J1Dx02(const double& x01, const double& x02) {
    return -2 * x02 * x02;
}

double J2Dx01(const double& x01, const double& x02) {
    return pow(x02, 3);
}

double J2Dx02(const double& x01, const double& x02) {
    return  3 * x02 * x02 - 1;
}
void J(vector<double>& x0, vector<vector<double>>& matrix) {
    matrix[0][0] = J1Dx01(x0[0], x0[1]);
    matrix[0][1] = J1Dx02(x0[0], x0[1]);
    matrix[1][0] = J2Dx01(x0[0], x0[1]);
    matrix[1][1] = J2Dx02(x0[0], x0[1]);
}
void J1(vector<double>& x0, vector<vector<double>>& matrix, double M) {
    matrix[0][0] = (function1(x0[0] + M * x0[0], x0[1]) - function1(x0[0], x0[1])) / M * x0[0];
    matrix[0][1] = (function1(x0[0], x0[1] + M * x0[1]) - function1(x0[0], x0[1])) / M * x0[1];
    matrix[1][0] = (function2(x0[0] + M * x0[0], x0[1]) - function2(x0[0], x0[1])) / M * x0[0];
    matrix[1][1] = (function2(x0[0], x0[1] + M * x0[1]) - function2(x0[0], x0[1])) / M * x0[1];
}
double delta1(const vector<double>& x0) {
    double f1 = function1(x0[0], x0[1]), f2 = function2(x0[0], x0[1]);
    if (abs(f1) > abs(f2))return f1;
    else return f2;
}
double delta2(const vector<double>& x0, const vector<double>& xk1) {
    double max = 0;
    for (int i = 0; i < x0.size(); i++) {
        if (abs(xk1[i]) < 1) {
            if (abs(xk1[i] - x0[i] > max)) {
                max = abs(xk1[i] - x0[i]);
            }
        }
        else {
            if ((abs(xk1[i] - x0[i]) / xk1[i] > max)) {
                max = abs(xk1[i] - x0[i]) / xk1[i];
            }
        }
    }
    return max;
}

void forwardElimination(vector<vector<double>>& augmentedMatrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double ratio = augmentedMatrix[j][i] / augmentedMatrix[i][i];
            for (int k = 0; k <= n; k++) {
                augmentedMatrix[j][k] -= ratio * augmentedMatrix[i][k];
            }
        }
    }
}
vector<double> gaussElimination(const vector<vector<double>>& A, const vector<double>& B) {
    int n = A.size();
    // Создаем расширенную матрицу [A | B]
    vector<vector<double>> augmentedMatrix(n, vector<double>(n + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmentedMatrix[i][j] = A[i][j];
        }
        augmentedMatrix[i][n] = B[i];
    }

    // Прямой ход
    forwardElimination(augmentedMatrix, n);

    // Обратный ход
    vector<double> solution = backSubstitution(augmentedMatrix, n);

    return solution;
}

vector<double> backSubstitution(const vector<vector<double>>& augmentedMatrix, int n) {
    vector<double> solution(n);
    for (int i = n - 1; i >= 0; i--) {
        solution[i] = augmentedMatrix[i][n];
        for (int j = i + 1; j < n; j++) {
            solution[i] -= augmentedMatrix[i][j] * solution[j];
        }
        solution[i] /= augmentedMatrix[i][i];
    }
    return solution;
}

void PrintAnswer(const vector<double> x0, int k) {
    std::cout << "\nx1 = " << x0[0] << "\nx2 = " << x0[1] << "\nk = " << k;
}