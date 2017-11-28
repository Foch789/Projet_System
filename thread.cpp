#include "hpp/Analytique.hpp"

//===========================================================================
//============================Structure Chebyshev============================
//===========================================================================

struct SCheby
{
  int iteration;
  float tS;
  double resultat;
}typedef SCheby;

struct SChebySuite
{
    int iteration;
    double *suite;
}typedef SChebySuite;

struct SChebyFormule
{
  int iterationD;
  int iterationF;
  double resultat;
  double *U;
  double *V;
}typedef SChebyFormule;

//===========================================================================
//===========================================================================
//===========================================================================

void FChebyshev(int iteration,float &tS,double &resultat);
void *SuiteUChebyshev(void *arg);
void *SuiteVChebyshev(void *arg);
void *FormuleChebyshev(void *arg);

//===========================================================================
//===========================================================================
//===========================================================================

void ThreadCommun(int iteration)
{
  cout << "==============================================================="<< endl;
  cout << "==========================LES THREADS=========================="<< endl;
  cout << "==============================================================="<< endl;

  double Cresultat=0;
  float tT,tS;


  FChebyshev(iteration,tS,Cresultat);

  cout << "Chebyshev = " << Cresultat << endl;
  cout << "Le calcul c'est fait en " << tS << " secondes." << endl;

  tT = tS;
  cout << "Temps total du programme :" << tT << " secondes." << endl;

}

//===========================================================================
//===========================================================================
//===========================================================================


void FChebyshev(int iteration,float &tS,double &resultat)
{

  SChebySuite U;
  SChebySuite V;

  U.iteration = iteration;

  V.iteration = iteration;

  pthread_t TU,TV;

  auto clockBegin = std::chrono::system_clock::now();

  resultat = 8.0 * (pow(-1.0, 0) / (pow(10.0, 1.0)) * (1.0)) * ((4 * (99.0 / 100.0)) - (99.0 / 4780.0));

  pthread_create(&TU,NULL,SuiteUChebyshev,static_cast<void*>(&U));
  pthread_create(&TV,NULL,SuiteVChebyshev,static_cast<void*>(&V));

  pthread_join(TU,NULL);
  pthread_join(TV,NULL);

  if(iteration == 2)
  {

    pthread_t TF1;

    SChebyFormule C1;
    C1.iterationD = 2;
    C1.iterationF = 2;
    C1.resultat = 0;
    C1.U = U.suite;
    C1.V = V.suite;

    pthread_create(&TF1,NULL,FormuleChebyshev,static_cast<void*>(&C1));
    pthread_join(TF1,NULL);

    resultat += C1.resultat;

  }
  else if (iteration >=3)
  {
    pthread_t TF1,TF2;

    SChebyFormule C1;
    C1.iterationD = 2;
    C1.iterationF = (int)(iteration)/2;
    C1.resultat = 0;
    C1.U = U.suite;
    C1.V = V.suite;

    SChebyFormule C2;
    C2.iterationD = ((int)(iteration)/2)+1;
    C2.iterationF = iteration;
    C2.resultat = 0;
    C2.U = U.suite;
    C2.V = V.suite;

    pthread_create(&TF1,NULL,FormuleChebyshev,static_cast<void*>(&C1));
    pthread_create(&TF2,NULL,FormuleChebyshev,static_cast<void*>(&C2));
    pthread_join(TF1,NULL);
    pthread_join(TF2,NULL);

    resultat += C1.resultat + C2.resultat;

  }

  tS = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - clockBegin).count()/1000000000.0;

  delete [] U.suite;
  delete [] V.suite;


}

void *SuiteUChebyshev(void *arg)
{
  SChebySuite *U = (SChebySuite *) arg;

  U->suite=SuiteU(U->iteration);

  return 0;
}

void *SuiteVChebyshev(void *arg)
{
  SChebySuite *V = (SChebySuite *) arg;

  V->suite=SuiteV(V->iteration);

  return 0;
}

void *FormuleChebyshev(void *arg)
{

  SChebyFormule *C = (SChebyFormule *) arg;

  C->resultat = ChebyshevF(C->iterationD,C->iterationF,C->U,C->V);

  return 0;
}
