#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

void input(double** A, double* b, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "a[" << i << "][" << j << "]= ";
            cin >> A[i][j];
        }
    }
    for (int i = 0; i < n; i++) {       //b
        cout << "y[" << i << "]= ";
        cin >> b[i];
    }
}

void print_system(double** A, double* b, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << A[i][j] << "x" << j + 1;
            if (j != n - 1) {
                cout << " + ";
            }
        }
        cout << " = " << b[i] << endl;
    }
}

double* gauss(double** A, double* b, int n) {
    double* x = new double[n], max;
    int current = 0, indexMax;
    const double eps = 0.00001;  // точность
    for (int i = current; current < n; current++) {
        // Поиск строки с максимальным a[i][k]
        max = abs(A[current][current]);
        indexMax = current;
        for (int i = current + 1; i < n; i++) {
            if (abs(A[i][current]) > max) {
                max = abs(A[i][current]);
                indexMax = i;
            }
        }
        cout << "--------------------------------------" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << setw(8) << A[i][j] << "\t";
            }
            cout << "| " << b[i] << endl;
        }
        // Перестановка строк
        if (max < eps) {
            // нет ненулевых диагональных элементов
            cout << "Решение получить невозможно из-за нулевого столбца ";
            cout << indexMax << " матрицы A" << endl;
            return 0;
        }
        for (int j = 0; j < n; j++) { //меняем current строку с max элементом в current столбце
            swap(A[current][j], A[indexMax][j]);
        }
        swap(b[current], b[indexMax]);
        // Нормализация уравнений
        for (int i = current; i < n; i++) {
            double temp = A[i][current];
            if (abs(temp) < eps) {  // для нулевого коэффициента пропустить
                continue;
            }
            for (int j = 0; j < n; j++) { //получаем единичные элементы на главной диагонали
                A[i][j] = A[i][j] / temp;
            }
            b[i] = b[i] / temp;

            if (i == current) { // уравнение не вычитать само из себя
                continue;
            }
            for (int j = 0; j < n; j++) {
                A[i][j] = A[i][j] - A[current][j];
            }
            b[i] = b[i] - b[current];
        }

    }
    // обратная подстановка
    for (current = n - 1; current >= 0; current--) { //начинаем с последнего уравнения и двигаемся к 1(вычитаем из b[i] уже найденные x[j](j>i)
        x[current] = b[current];                    // умноженных на соответствующие элементы матрицы A
        for (int i = 0; i < current; i++) {
            b[i] = b[i] - A[i][current] * x[current];
        }
    }
    // Вывод значений матрицы
    cout << "--------------------------------------" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(8) << A[i][j] << "\t";
        }
        cout << "| " << b[i] << endl;
    }
    return x; // возвращают решение системы уравнений - вектор x. Если решение невозможно, функции возвращают 0. 
}

void solve_auxiliary_system(double** A, double*& x, int n) {
    gauss(A, x, n);
    cout << "Solution of Ax = Ax':" << endl;
}

double* residual(double** A, double* b, double* x, int n) {
    double* r = new double[n];
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < n; j++) {
            sum += A[i][j] * x[j];
        }
        r[i] = -sum + b[i];
    }
    return r;
}

double calculateResidualNorm(double* residual, int n) {
    double norm = 0.0;
    for (int i = 0; i < n; i++) {
        norm += residual[i] * residual[i];
    }
    return sqrt(norm);
}

double relativeError(double roots1, double roots2) {
    return abs(roots1 - roots2) / abs(roots1);
}