#pragma once

double fun(double x);
double DoubleFunkAgrument(int i, int j, int n);
double trapeze(double a, double b, double(*f)(double), double e);
double basicSimp(double a, double b, double(*f)(double), double e);
double cubeSimp(double a, double A, double b, double B, double(*f)(int, int, int), double e);
