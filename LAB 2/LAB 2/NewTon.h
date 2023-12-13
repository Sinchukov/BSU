#ifndef NEWTON_H
#define NEWTON_H
#include<vector>
using namespace std;
#pragma once
double function1(const double& x01, const double& x02);

double function2(const double& x01, const double& x02);

double J1Dx01(const double& x01, const double& x02);

double J1Dx02(const double& x01, const double& x02);

double J2Dx01(const double& x01, const double& x02);

double J2Dx02(const double& x01, const double& x02);
void J(std::vector<double>& x0, std::vector<std::vector<double>>& matrix);
void J1(std::vector<double>& x0, std::vector<std::vector<double>>& matrix, double M);
double delta1(const std::vector<double>& x0);
double delta2(const std::vector<double>& x0, const std::vector<double>& xk1);
void PrintAnswer(const std::vector<double> x0, int k);
vector<double> gaussElimination(const vector<vector<double>>& A, const vector<double>& B);
vector<double> backSubstitution(const vector<vector<double>>& augmentedMatrix, int n);
void forwardElimination(vector<vector<double>>& augmentedMatrix, int n);

#endif /* NEWTON_H */