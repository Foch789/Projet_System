#include <cmath>
#include <iostream>
#include <limits>
#include <pthread.h>
#include <chrono>
#include <omp.h>
#include <memory>

using namespace std;


struct result
{
double plouffe;
float Tp;
double chebyshev;
float Tc;

result& operator=(const result& src) { plouffe = src.plouffe; Tp = src.Tp; chebyshev = src.chebyshev; Tc = src.Tc; return *this;}
};

result SequentielCommun(int iteration);
result ThreadCommun(int iteration);
result OpenMP_Commun(int iteration);

double *SuiteU(int iteration);
double *SuiteV(int iteration);
double ChebyshevF(int iterationD,int iterationF,double *tabU,double *tabV);

double PlouffeF(int iterationD,int iterationF);
