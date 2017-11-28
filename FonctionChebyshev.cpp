#include "hpp/Analytique.hpp"

void SuiteU(int iterationD,int iterationF,double *tab)
{


  int p=1;
  double U = 0.0, U1 = (99.0 / 100.0), U2 = (4801.0 / 5000.0);

  for(int i = iterationD; i < iterationF;++i)
  {
    while (p < 2) {

      U = ((99.0 / 50.0) * U2) - U1;
      U1 = U2;
      U2 = U;

      p++;
    }
    p=0;
    tab[i] = U;
  }

}


void SuiteV(int iterationD,int iterationF,double *tab)
{

  int p=1;
  double V = 0.0, V1 = (99.0 / 4780.0), V2 = -(11414399.0 / 11424200.0);

  for(int i = iterationD; i < iterationF;++i)
  {
    while (p < 2) {

      V = ((99.0 / 2390.0) * V2) - V1;
      V1 = V2;
      V2 = V;

      p++;
    }
    p=0;
    tab[i]=V;
  }

}


double ChebyshevF(int iterationD,int iterationF,double *tabU,double *tabV)
{

  double resultat=0.0;
  int p= iterationD-2;

  for (int i = iterationD; i <= iterationF; ++i)
  {
    resultat += 8.0 * (pow(-1.0, (i - 1.0)) / (pow(10.0, ((2.0 * i) - 1.0)) * ((2.0 * i) - 1.0))) * ((4.0 * tabU[p]) - tabV[p]);
    p++;
  }

  return resultat;
}
