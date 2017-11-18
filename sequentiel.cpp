#include "hpp/Analytique.hpp"

void SequentielCommun()
{
  cout << "==============================================================="<< endl;
  cout << "==========================Sequentiel==========================="<< endl;
  cout << "==============================================================="<< endl;

  // Variable programme
  int iteration = 0;
  clock_t tS,tP;
  float tT;

  // Variable Plouffe
  double Plouffe = 0.0;

  // Variable Chebyshev
  double Chebyshev = 0.0;
  double *U ,*V;
  double U1 = (99.0 / 100.0);
  double V1 = (99.0 / 4780.0);


  cout << "Combien d'iterations voulez-vous ? > ";
  cin >> iteration;

  // CAlCUL DE PLOUFFE
  cout << "Debut du calcul de Plouffe..." << endl;
  tP= clock();
  Plouffe = PlouffeF(0,iteration);
  tP = clock() - tP;
  cout << "Plouffe = " << Plouffe << endl;
  cout << "Le calcul c'est fait en " << ((float)tP/CLOCKS_PER_SEC) << " secondes." << endl;

  // CAlCUL DE CHEBYSHEV

  cout << "Debut du calcul de Chebyshev..." << endl;
  tS = clock();
  Chebyshev += 8.0 * (pow(-1.0, 0) / (pow(10.0, 1.0)) * (1.0)) * ((4 * U1) - V1);

  U = SuiteU(iteration);
  V = SuiteV(iteration);
  Chebyshev += ChebyshevF(2,iteration,U,V);
  delete [] U;
  delete [] V;

  tS= clock() - tS;
  cout << "Chebyshev = " << Chebyshev << endl;
  cout << "Le calcul c'est fait en " << ((float)tS/CLOCKS_PER_SEC) << " secondes." << endl;

  tT = ((float)tS/CLOCKS_PER_SEC) + ((float)tP/CLOCKS_PER_SEC);
  cout << "Temps total du programme :" << tT << " secondes." << endl;

  if(((float)tS/CLOCKS_PER_SEC) > ((float)tP/CLOCKS_PER_SEC))
  {
    cout << "Plouffe est plus rapide de " << (((float)tS/CLOCKS_PER_SEC) - ((float)tP/CLOCKS_PER_SEC)) << " secondes." << endl;
  }
  else
  {
    cout << "Chebyshev est plus rapide de " << (((float)tP/CLOCKS_PER_SEC) - ((float)tS/CLOCKS_PER_SEC)) << " secondes." << endl;
  }

}
