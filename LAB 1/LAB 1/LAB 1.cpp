#include <iostream>
#include <iomanip>
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

double* gauss(double** A, double* b, int n) {
    double* x = new double[n], max;
    int current = 0, indexMax;
    const double eps = 0.00001;  // точность
    while (current < n) {
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
            double temp = A[current][j];
            A[current][j] = A[indexMax][j];
            A[indexMax][j] = temp;
        }
        double temp = b[current];
        b[current] = b[indexMax];
        b[indexMax] = temp;
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
        current++;
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

void solve_auxiliary_system(double** A, double* x_prime, double*& x, int n) {
    // Решаем систему Ax' = b методом Гаусса
    double* b = new double[n];
    for (int i = 0; i < n; i++) {
        b[i] = A[i][i] * x_prime[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                b[i] -= A[i][j] * x_prime[j];
            }
        }
    }
    double* z = gauss(A, b, n);
    // Решаем систему Ly = z
    double** L = new double* [n];
    for (int i = 0; i < n; i++) {
        L[i] = new double[n];
        for (int j = 0; j < n; j++) {
            if (i == j) {
                L[i][j] = 1;
            }
            else {
                L[i][j] = A[i][j];
            }
        }
    }
    double* y = new double[n];
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < i; j++) {
            sum += L[i][j] * y[j];
        }
        y[i] = z[i] - sum;
    }
    // Решаем систему Dz = y
    double* d = new double[n];
    for (int i = 0; i < n; i++) {
        d[i] = A[i][i];
        for (int j = 0; j < i; j++) {
            d[i] -= L[i][j] * L[i][j] * d[j];
        }
    }
    for (int i = 0; i < n; i++) {
        y[i] /= d[i];
    }
    // Решаем систему Lt x = z
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < n; j++) {
            sum += L[j][i] * x[j];
        }
        x[i] = (y[i] - sum) / L[i][i];
    }
    // Освобождаем память
    delete[] b, delete[] z, delete[] y;
    for (int i = 0; i < n; i++) {
        delete[] L[i];
    }
    delete[] L;
}

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
    for (int i = 0; i < n; i++)
    {
        roots1[i] = x[i];
    }
    double* F1 = new double[n];
    for (int i = 0; i < n; i++) {   //Невязка - это вектор r, равный разности между вектором b и произведением матрицы A на вектор x.
        F1[i] = -b[i];
        for (int j = 0; j < n; j++) {
            F1[i] += A[i][j] * x[j];
        }
    }
    // Вычисление нормы вектора невязки
    double norm1 = 0;
    for (int i = 0; i < n; i++) {
        norm1 += F1[i] * F1[i];
    }
    cout << "Norm of the residual vector: " << sqrt(norm1) << endl;




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

    double* F2 = new double[n];
    for (int i = 0; i < n; i++) {   //Невязка - это вектор r, равный разности между вектором b и произведением матрицы A на вектор x.
        F2[i] = -b[i];
        for (int j = 0; j < n; j++) {
            F2[i] += A[i][j] * roots2[j];
        }
    }
    // Вычисление нормы вектора невязки
    double norm2 = 0;
    for (int i = 0; i < n; i++) {
        norm2 += F2[i] * F2[i];
    }
    cout << "Norm of the residual vector: " << sqrt(norm2) << endl;

    cin.get(); cin.get();
    return 0;
}