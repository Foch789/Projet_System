#include "hpp/Analytique.hpp"

result SequentielCommun(int iteration)
{
  result sequentiel;

  cout << "==============================================================="<< endl;
  cout << "==========================Sequentiel==========================="<< endl;
  cout << "==============================================================="<< endl;

  // Variable programme
  float tS,tP;
  float tT;

  // Variable Plouffe
  long double Plouffe = 0.0;

  // Variable Chebyshev
  long double Chebyshev = 0.0;
  long double *U ,*V;
  long double U1 = (99.0 / 100.0);
  long double V1 = (99.0 / 4780.0);


    // CAlCUL DE PLOUFFE
    cout << "Debut du calcul de Plouffe..." << endl;
    auto clockBegin = std::chrono::system_clock::now();
    Plouffe = PlouffeF(0,iteration);
    tP = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - clockBegin).count()/1000000000.0;
    cout << "Plouffe = " << Plouffe << endl;
    cout << "Le calcul c'est fait en " << tP << " secondes." << endl;

    // CAlCUL DE CHEBYSHEV

    cout << "Debut du calcul de Chebyshev..." << endl;
    auto clockBegin2 = std::chrono::system_clock::now();
    Chebyshev += 8.0 * (pow(-1.0, 0) / (pow(10.0, 1.0)) * (1.0)) * ((4 * U1) - V1);

    U = SuiteU(iteration);
    V = SuiteV(iteration);
    Chebyshev += ChebyshevF(2,iteration,U,V);

    tS = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - clockBegin2).count()/1000000000.0;
    cout << "Chebyshev = " << Chebyshev << endl;
    cout << "Le calcul c'est fait en " << tS << " secondes." << endl;

    tT =  tS + tP;
    cout << "Temps total du programme :" << tT << " secondes." << endl;

    if(tS > tP)
    {
      cout << "Plouffe est plus rapide de " << tS - tP << " secondes." << endl;
    }
    else
    {
      cout << "Chebyshev est plus rapide de " << tP - tS << " secondes." << endl;
    }

    sequentiel.plouffe = Plouffe;
    sequentiel.Tp = tP;
    sequentiel.chebyshev = Chebyshev;
    sequentiel.Tc = tS;


  delete [] U;
  delete [] V;

  return sequentiel;

}
