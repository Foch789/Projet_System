#include <cmath>
#include <iostream>
#include <limits>
#include <ctime>
#include <pthread.h>


using namespace std;

//void FormulePLouffe();
//void FormuleChebyshev();

void SequentielCommun();
void ThreadCommun();

double *SuiteU(int iteration);
double *SuiteV(int iteration);
double ChebyshevF(int iterationD,int iterationF,double *tabU,double *tabV);

double PlouffeF(int iterationD,int iterationF);
