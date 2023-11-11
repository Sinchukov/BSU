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
    const double eps = 0.00001;  // ��������
    for (int i = current; current < n; current++) {
        // ����� ������ � ������������ a[i][k]
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
        // ������������ �����
        if (max < eps) {
            // ��� ��������� ������������ ���������
            cout << "������� �������� ���������� ��-�� �������� ������� ";
            cout << indexMax << " ������� A" << endl;
            return 0;
        }
        for (int j = 0; j < n; j++) { //������ current ������ � max ��������� � current �������
            swap(A[current][j], A[indexMax][j]);
        }
        swap(b[current], b[indexMax]);
        // ������������ ���������
        for (int i = current; i < n; i++) {
            double temp = A[i][current];
            if (abs(temp) < eps) {  // ��� �������� ������������ ����������
                continue;
            }
            for (int j = 0; j < n; j++) { //�������� ��������� �������� �� ������� ���������
                A[i][j] = A[i][j] / temp;
            }
            b[i] = b[i] / temp;

            if (i == current) { // ��������� �� �������� ���� �� ����
                continue;
            }
            for (int j = 0; j < n; j++) {
                A[i][j] = A[i][j] - A[current][j];
            }
            b[i] = b[i] - b[current];
        }

    }
    // �������� �����������
    for (current = n - 1; current >= 0; current--) { //�������� � ���������� ��������� � ��������� � 1(�������� �� b[i] ��� ��������� x[j](j>i)
        x[current] = b[current];                    // ���������� �� ��������������� �������� ������� A
        for (int i = 0; i < current; i++) {
            b[i] = b[i] - A[i][current] * x[current];
        }
    }
    // ����� �������� �������
    cout << "--------------------------------------" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(8) << A[i][j] << "\t";
        }
        cout << "| " << b[i] << endl;
    }
    return x; // ���������� ������� ������� ��������� - ������ x. ���� ������� ����������, ������� ���������� 0. 
}

void solve_auxiliary_system(double** A, double* x_prime, double*& x, int n) {
    // ������ ������� Ax' = b ������� ������
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
    // ������ ������� Ly = z
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
    // ������ ������� Dz = y
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
    // ������ ������� Lt x = z
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < n; j++) {
            sum += L[j][i] * x[j];
        }
        x[i] = (y[i] - sum) / L[i][i];
    }
    // ����������� ������
    delete[] b, delete[] z, delete[] y;
    for (int i = 0; i < n; i++) {
        delete[] L[i];
    }
    delete[] L;
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