#include "hpp/Analytique.hpp"

long double PlouffeF(int iterationD,int iterationF)
{

  long double resultat =0.0;

  for (int i = iterationD; i < iterationF; ++i)
  {
    resultat += (1.0 / pow(16.0, i)) * ((4.0 / ((8.0 * i) + 1.0)) - (2.0 / ((8.0 * i) + 4.0)) - (1.0 / ((8.0 * i) + 5.0)) - (1.0 / ((8.0 * i) + 6.0)));
  }

  return resultat;
}
