#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QVector>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::makePlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

double* gauss(double** A, double* b, int n) {
    double* x = new double[n], max;
    int current = 0, indexMax;
    const double eps = 0.00001;
    for (int i = current; current < n; current++) {
        max = abs(A[current][current]);
        indexMax = current;
        for (int i = current + 1; i < n; i++) {
            if (abs(A[i][current]) > max) {
                max = abs(A[i][current]);
                indexMax = i;
            }
        }
        if (max < eps) {
            cout << "Cannot solve matrix ";
            cout << indexMax << " Matrix A" << endl;
            return 0;
        }
        for (int j = 0; j < n; j++) {
            swap(A[current][j], A[indexMax][j]);
        }
        swap(b[current], b[indexMax]);
        for (int i = current; i < n; i++) {
            double temp = A[i][current];
            if (abs(temp) < eps) {
                continue;
            }
            for (int j = 0; j < n; j++) {
                A[i][j] = A[i][j] / temp;
            }
            b[i] = b[i] / temp;

            if (i == current) {
                continue;
            }
            for (int j = 0; j < n; j++) {
                A[i][j] = A[i][j] - A[current][j];
            }
            b[i] = b[i] - b[current];
        }

    }
    for (current = n - 1; current >= 0; current--) {
        x[current] = b[current];
        for (int i = 0; i < current; i++) {
            b[i] = b[i] - A[i][current] * x[current];
        }
    }

    return x;
}
void MainWindow::makePlot(){
    // generate some data:
    // QApplication application((argc, argv));
    QCustomPlot* widget = ui->widget;
    if (widget->graphCount() == 0) {
        widget->addGraph();
    }
    const int N = 9, m = 2;
    double* PRAW = new double[m + 1];
    double x[N] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 }, y[N];
    for (int i = 0; i < N; i++) {
        y[i] = 1.0 / (1 + x[i]);
    }
    double* POWERX = new double[2 * m];
    for (int k = 0; k < 2 * m; k++) {
        POWERX[k] = 0;
        for (int i = 0; i < N; i++) {
            POWERX[k] += pow(x[i], k + 1);
        }
    }
    double** SUMX = new double* [m + 1];
    for (int i = 0; i < m + 1; i++) {
        SUMX[i] = new double[m + 1];
    }
    for (int l = 0; l < m + 1; l++) {
        for (int j = 0; j < m + 1; j++) {
            if (j + l) {
                SUMX[l][j] = POWERX[l + j - 1];
            }
            else {
                SUMX[l][j] = N;
            }
        }
    }
    for (int l = 0; l < m + 1; l++) {
        PRAW[l] = 0;
        for (int i = 0; i < N; i++) {
            PRAW[l] += y[i] * pow(x[i], l);
        }
    }
    double* a = gauss(SUMX, PRAW, m + 1);
    double S2 = 0;
    for (int i = 0; i < N; i++) {
        double sum = y[i];
        for (int j = 0; j < m + 1; j++) {
            sum -= a[j] * pow(x[i], j);
        }
        S2 += pow(sum, 2);
    }
    S2 /= N - m - 1;
    double sigma = sqrt(S2);
    QVector<double> xData(N), yData(N);
    for (int i = 0; i < N; i++) {
        xData[i] = x[i];
        yData[i] = y[i];
    }
    ui->widget->graph(0)->setData(xData, yData);
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");
    ui->widget->yAxis->setRange(0, 1);
    ui->widget->replot();
    ui->widget->show();
}




