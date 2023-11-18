#pragma once
#include <iostream>
#include <iomanip>


void    input(double** A, double* b, int n);
void    printSystem(double** A, double* b, int n);
double* gauss(double** A, double* b, int n);
double* residual(double** A, double* b, double* x, int n);
double  calculateResidualNorm(double* residual, int n);
double  relativeError(double *trueValue, double *approximateValue, int n);
void    solveAuxiliarySystem(double** A, double*& x, int n);
