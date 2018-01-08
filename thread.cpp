#include "hpp/Analytique.hpp"



//===========================================================================
//============================Structure Plouffe==============================
//===========================================================================

struct PLouffe
{
    int iteration = 0;
    double tP;
    double resultat = 0.0;
} typedef PLouffe;

struct PlouffeThreads
{
    int debutIteration = 0;
    int finalIteration = 0;
    double resultat = 0;

} typedef PlouffeThreads;


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
void FSimonPlouffe(int iteration,float &tP, double &resultat);
void *FormulePlouffe(void *arg);
void *SuiteUChebyshev(void *arg);
void *SuiteVChebyshev(void *arg);
void *FormuleChebyshev(void *arg);

//===========================================================================
//===========================================================================
//===========================================================================

result ThreadCommun(int iteration)
{
  result thread;
  cout << "==============================================================="<< endl;
  cout << "==========================LES THREADS=========================="<< endl;
  cout << "==============================================================="<< endl;

  double Cresultat=0;
  double Presultat=0;
  float tT,tS,tP;

  FSimonPlouffe(iteration,tP,Presultat);
  cout << "Simon Plouffe = " <<Presultat << endl;
  cout << "Le calcul Simon Plouffe c'est fait en " << tP << " secondes." << endl;

  FChebyshev(iteration,tS,Cresultat);
  cout << "Chebyshev = " << Cresultat << endl;
  cout << "Le calcul de Chebyshev c'est fait en " << tS << " secondes." << endl;



  tT = tS + tP;
  cout << "Temps total du programme :" << tT << " secondes." << endl;

  thread.plouffe = Presultat;
  thread.chebyshev = Cresultat;
  thread.Tc = tS;
  thread.Tp = tP;

  return thread;

}

//===========================================================================
//===========================================================================
//===========================================================================


void FSimonPlouffe(int iteration, float &tP, double &resultat){

  PlouffeThreads p1,p2;

  pthread_t Tp1,Tp2;



  p1.debutIteration = 0;
  p1.finalIteration = static_cast<int>(iteration/2);
  p2.debutIteration = p1.finalIteration+1;
  p2.finalIteration = iteration;

  auto clockBegin = std::chrono::system_clock::now();
  pthread_create(&Tp1,NULL,FormulePlouffe,static_cast<void*>(&p1));
  pthread_create(&Tp2,NULL,FormulePlouffe,static_cast<void*>(&p2));

  pthread_join(Tp1,NULL);
  pthread_join(Tp2,NULL);


  resultat = p1.resultat + p2.resultat;
  tP = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - clockBegin).count()/1000000000.0;




}

void *FormulePlouffe(void *arg)
{

  PlouffeThreads *fctPlouffe = (PlouffeThreads*) arg;

  fctPlouffe->resultat = PlouffeF(fctPlouffe->debutIteration,fctPlouffe->finalIteration);

  return 0;
}


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
