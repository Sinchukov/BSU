#pragma once
#include <iostream>
#include <iomanip>
#include <vector>

void input(double** A, double* b, int n);
void print_system(double** A, double* b, int n);
double* gauss(double** A, double* b, int n);
void solve_auxiliary_system(double** A, double* x_prime, double*& x, int n);
double* residual(double** A, double* b, double* x, int n);
double calculateResidualNorm(double* residual, int n);


