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

void SuiteU(int iterationD,int iterationF,double &tab);
void SuiteV(int iterationD,int iterationF,double &tab);
double ChebyshevF(int iterationD,int iterationF,double *tabU,double *tabV);

double PlouffeF(int iterationD,int iterationF);
