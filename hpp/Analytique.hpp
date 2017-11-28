#include <cmath>
#include <iostream>
#include <limits>
#include <pthread.h>
#include <chrono>
#include <omp.h>

using namespace std;

void SequentielCommun(int iteration);
void ThreadCommun(int iteration);
void OpenMP_Commun(int iteration);

double *SuiteU(int iteration);
double *SuiteV(int iteration);
double ChebyshevF(int iterationD,int iterationF,double *tabU,double *tabV);

double PlouffeF(int iterationD,int iterationF);
