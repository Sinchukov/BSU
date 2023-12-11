﻿#include <QApplication>
#include "qcustomplot.h"
#include <iomanip>
#include "MNK.h"
using namespace std;
int main(int argc, char* argv[])
{
    QApplication w(argc, argv);
    QCustomPlot* customPlot = new QCustomPlot();
    customPlot->addGraph();
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
    customPlot->graph(0)->setData(xData, yData);
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    customPlot->xAxis->setRange(0, 8);
    customPlot->yAxis->setRange(0, 1);
    customPlot->replot();
    customPlot->show();
    return w.exec();
}