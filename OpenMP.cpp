#include "hpp/Analytique.hpp"

#define MAXSIZE 2000

void OpenMP_Commun(int iteration)
{

  cout << "==============================================================="<< endl;
  cout << "==========================OpenMP==============================="<< endl;
  cout << "==============================================================="<< endl;

  float * tab = new float[MAXSIZE];

  #pragma omp parallel
  {
  	const int thread_id = omp_get_thread_num();

  	std::cerr << "Premier exemple, thread n°"<< omp_get_thread_num() <<"\n";

  	if ( thread_id == 0) { //processus initial
  		const int nthread = omp_get_num_threads();
  		std::cerr << "NBThreads = " << nthread << std::endl;
  	}

  	#pragma omp for
          for (unsigned int i = 0; i < MAXSIZE; ++i)
          {
              tab[i] = (float)(i);
          }

  #pragma omp barrier //on attend tout le monde
  #pragma omp master //pour le processus principal

  std::cerr << "Je suis enfin seul\n";

  } // après cette accolade il n'y a plus que le thread principal


  delete[] tab;


}
