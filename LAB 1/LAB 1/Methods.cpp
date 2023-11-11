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