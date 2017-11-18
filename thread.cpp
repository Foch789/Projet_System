#include "hpp/Analytique.hpp"
#include <chrono>

//void Plouffe(int iteration);
void *Chebyshev(void *arg);
void *SuiteUChebyshev(void *arg);
void *SuiteVChebyshev(void *arg);
void *FormuleChebyshev(void *arg);

struct Scheby
{
  int iteration = 0;
  double tS;
}typedef Scheby;

struct SchebyS
{
    int iteration = 0;
    double *suite;
}typedef SchebyS; //Simplifiage

struct SchebyF
{
  int iterationD = 0;
  int iterationF = 0;
  double resultat = 0;
  double *U;
  double *V;
}typedef SchebyF;

void ThreadCommun()
{
  cout << "==============================================================="<< endl;
  cout << "==========================LES THREADS=========================="<< endl;
  cout << "==============================================================="<< endl;

  int iteration = 0;
  float tT;
  pthread_t TChebyshev;
  Scheby lel;


  cout << "Combien d'iterations voulez-vous ? > ";
  cin >> iteration;

  lel.iteration = iteration;

  pthread_create(&TChebyshev,NULL,Chebyshev,static_cast<void*>(&lel));

  pthread_join(TChebyshev,NULL);

  // tT = ((float)lel.tS/CLOCKS_PER_SEC);
  tT = lel.tS;
  cout << "Temps total du programme :" << tT << " secondes." << endl;

}

void *Chebyshev(void *arg)
{

  Scheby *mp = (struct Scheby *) arg;
  double resultat = 0.0;

  SchebyS U;
  SchebyS V;

  U.iteration = mp->iteration;
//  U.suite = new double [mp->iteration];

  V.iteration = mp->iteration;
  //V.suite = new double [mp->iteration];

  pthread_t TU,TV;

  auto clockBegin = std::chrono::system_clock::now();;

  resultat += 8.0 * (pow(-1.0, 0) / (pow(10.0, 1.0)) * (1.0)) * ((4 * (99.0 / 100.0)) - (99.0 / 4780.0));

  pthread_create(&TU,NULL,SuiteUChebyshev,static_cast<void*>(&U));
  pthread_create(&TV,NULL,SuiteVChebyshev,static_cast<void*>(&V));

  pthread_join(TU,NULL);
  pthread_join(TV,NULL);

  if(mp->iteration == 2)
  {

    pthread_t TF1;

    SchebyF C1;
    C1.iterationD = 2;
    C1.iterationF = 2;
    C1.U = U.suite;
    C1.V = V.suite;

    pthread_create(&TF1,NULL,FormuleChebyshev,static_cast<void*>(&C1));
    pthread_join(TF1,NULL);

    resultat += C1.resultat;

  }
  else if (mp->iteration >=3)
  {
    pthread_t TF1,TF2;

    SchebyF C1;
    C1.iterationD = 2;
    C1.iterationF = (int)(mp->iteration)/2;
    C1.U = U.suite;
    C1.V = V.suite;

    SchebyF C2;
    C2.iterationD = ((int)(mp->iteration)/2)+1;
    C2.iterationF = mp->iteration;
    C2.U = U.suite;
    C2.V = V.suite;

    pthread_create(&TF1,NULL,FormuleChebyshev,static_cast<void*>(&C1));
    pthread_create(&TF2,NULL,FormuleChebyshev,static_cast<void*>(&C2));
    pthread_join(TF1,NULL);
    pthread_join(TF2,NULL);

    resultat += C1.resultat + C2.resultat;

  }

  mp->tS = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - clockBegin).count()/1000000000.0;

  cout << "Chebyshev = " << resultat << endl;
  cout << "Le calcul c'est fait en " << mp->tS << " secondes." << endl;

  delete [] U.suite;
  delete [] V.suite;


  return 0;
}

void *SuiteUChebyshev(void *arg)
{
  SchebyS *A = (SchebyS *) arg;

  A->suite=SuiteU(A->iteration);

  return 0;
}

void *SuiteVChebyshev(void *arg)
{
  SchebyS *A = (SchebyS *) arg;

  A->suite=SuiteV(A->iteration);

  return 0;
}

void *FormuleChebyshev(void *arg)
{

  SchebyF *A = (SchebyF *) arg;

  A->resultat = ChebyshevF(A->iterationD,A->iterationF,A->U,A->V);

  return 0;
}
