#include "hpp/Analytique.hpp"

int main()
{
  int iteration = 0;
  cout.precision(std::numeric_limits<double>::digits10 + 1);

  cout << "Combien d'iterations voulez-vous ? > ";
  cin >> iteration;

  SequentielCommun(iteration);
  ThreadCommun(iteration);
  OpenMP_Commun(iteration);

  return 0;
}
