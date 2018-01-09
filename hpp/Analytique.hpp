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
long double plouffe;
float Tp;
long double chebyshev;
float Tc;

result& operator=(const result& src) { plouffe = src.plouffe; Tp = src.Tp; chebyshev = src.chebyshev; Tc = src.Tc; return *this;}
};

result SequentielCommun(int iteration);
result ThreadCommun(int iteration);
result OpenMP_Commun(int iteration);

long double *SuiteU(int iteration);
long double *SuiteV(int iteration);
long double ChebyshevF(int iterationD,int iterationF,long double *tabU,long double *tabV);

long double PlouffeF(int iterationD,int iterationF);
