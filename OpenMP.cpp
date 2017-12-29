#include "hpp/Analytique.hpp"

void OpenMP_Chebyshev(int iteration, result &R);

result OpenMP_Commun(int iteration)
{
  result openMP;
  cout << "==============================================================="<< endl;
  cout << "==========================OpenMP==============================="<< endl;
  cout << "==============================================================="<< endl;

  OpenMP_Chebyshev(iteration,openMP);

  return openMP;
}

void OpenMP_Chebyshev(int iteration,result &R)
{

  double Chebyshev = 0.0;
  double *suiteU = new double [iteration];
  double *suiteV = new double [iteration];
  double  U1 = (99.0 / 100.0);
  double  V1 = (99.0 / 4780.0);
  Chebyshev += 8.0 * (pow(-1.0, 0) / (pow(10.0, 1.0)) * (1.0)) * ((4 * U1) - V1);

  float tP;

  auto clockBegin = std::chrono::system_clock::now();
  #pragma omp parallel
  {

    	//const int thread_id = omp_get_thread_num();
    	//const int nthread = omp_get_num_threads();

      #pragma omp sections
      {

        #pragma omp section
        suiteU = SuiteU(iteration);

        #pragma omp section
        suiteV = SuiteV(iteration);

      }

      int p =0;
      #pragma omp for reduction(+: Chebyshev)
      for (int i = 2; i < iteration; ++i)
      {
        Chebyshev += 8.0 * (pow(-1.0, (i - 1.0)) / (pow(10.0, ((2.0 * i) - 1.0)) * ((2.0 * i) - 1.0))) * ((4.0 * suiteU[p]) - suiteV[p]);
        p++;
      }

  }


  tP = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - clockBegin).count()/1000000000.0;
  cout << "Chebyshev = " << Chebyshev << endl;
  cout << "Le calcul c'est fait en " << tP << " secondes." << endl;

  R.chebyshev = Chebyshev;
  R.Tc = tP;

  delete [] suiteU;
  delete [] suiteV;

}
