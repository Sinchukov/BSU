#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
using namespace std;

void    print(vector<double>);
void    print(vector<vector<double>>);
void    Nev(vector<double>&, vector<double>);
void    Jac(vector< vector<double>>&, vector<double>);
void    Jac2(vector< vector<double>>&, vector<double>, double);
double  fd1(vector<double>);
double  fd2(vector<double>, vector<double>);
bool    Gaus(vector<int>&, vector<double>&, vector<vector<double>>&, vector<double>&);
bool    GausSh(vector<int>&, vector<vector<double>>&, int, int);
void    In(vector<vector<double>>&, int);
void    print(vector<int>&, vector<vector<double>>&, int);
int     Max(vector<int>&, vector<vector<double>>&, int, int);
void    swap(vector<int>&, int, int);
