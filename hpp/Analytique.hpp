#include <cmath>
#include <iostream>
#include <limits>
#include <pthread.h>
#include <chrono>


using namespace std;

//void FormulePLouffe();
//void FormuleChebyshev();

void SequentielCommun();
void ThreadCommun();

double *SuiteU(int iteration);
double *SuiteV(int iteration);
double ChebyshevF(int iterationD,int iterationF,double *tabU,double *tabV);

double PlouffeF(int iterationD,int iterationF);
