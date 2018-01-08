#include "hpp/Analytique.hpp"
#include <fstream>
#include <sstream>

int main()
{

  //fstream ecrireFichier ("Resultat.txt",fstream::out);
  //fstream lireFichier;

  result sequentiel;
  result thread;
  result openMP;


  int iteration = 0;

  cout.precision(std::numeric_limits<double>::digits10 + 1);


  cout << "Combien d'iterations voulez-vous ? > ";
  cin >> iteration;



  //for(int i = 1; i < iteration+1;++i)
  //{

    sequentiel = SequentielCommun(iteration);
    thread = ThreadCommun(iteration);
    openMP = OpenMP_Commun(iteration);

    stringstream ss;
    ss.precision(std::numeric_limits<double>::digits10 + 1);
    double valeurP = sequentiel.plouffe;
    double valeurC = sequentiel.chebyshev;
    ss << sequentiel.plouffe;
    string plouffestring = ss.str();
    ss.str("");
    ss << sequentiel.chebyshev;
    string chebyshevstring = ss.str();
    int tailleP = plouffestring.size()-2;
    int tailleC = chebyshevstring.size()-2;

    cout << plouffestring << " et " << tailleP << endl;
    cout << chebyshevstring << " et " << tailleC << endl;

    valeurP = valeurP - 3.0;
    valeurC = valeurC - 3.0;


    valeurP*=pow(10,tailleP);
    valeurC*=pow(10,tailleC);

    size_t p = static_cast<size_t>(valeurP);
    size_t c = static_cast<size_t>(valeurC);


    ss.str("");
    ss << p;
    plouffestring = ss.str();
    ss.str("");
    ss << c;
    chebyshevstring = ss.str();

    cout << plouffestring << " et " << tailleP << endl;
    cout << chebyshevstring << " et " << tailleC << endl;

    int tailleT = tailleP>tailleC?tailleP:tailleC;
    int nombre_sansdiscon = 0;

    for(int i = 0; i < tailleT;++i)
    {
      if(plouffestring[i] == chebyshevstring[i])
        nombre_sansdiscon++;
      else
        break;
    }

    cout << "Il y a discon jusqu'a la decimal " << nombre_sansdiscon << endl;

    //Ecrit dans un fichier

  //   if(ecrireFichier.is_open())
  //   {
  //     ecrireFichier.precision(std::numeric_limits<double>::digits10 + 1);
  //     ecrireFichier << std::showpoint;
  //     ecrireFichier << std::fixed;
  //     ecrireFichier << "============================================================================================================\n";
  //     ecrireFichier << "====================================Pour " << iteration << " iterations.====================================\n";
  //     ecrireFichier << "============================================================================================================\n";
  //     ecrireFichier << "                    Sequentiel                    Thread                    openMP          \n";
  //     ecrireFichier << "Resultat Plouffe    "<<sequentiel.plouffe/*<<"         "<<thread.plouffe<<"          "<<openMP.plouffe*/<<"\n";
  //     ecrireFichier << "Temps Plouffe       "<<sequentiel.Tp/*<<"         "<<thread.Tp<<"          "<<openMP.Tp*/<<"\n";
  //     ecrireFichier << "Resultat Chebyshev  "<<sequentiel.chebyshev<<"          "<<thread.chebyshev<<"          "<<openMP.chebyshev<<"\n";
  //     ecrireFichier << "Temps Chebyshev     "<<sequentiel.Tc<<"         "<<thread.Tc<<"          "<<openMP.Tc<<"\n";
  //     ecrireFichier << "Temps realiser      "<<sequentiel.Tp+sequentiel.Tc<<"         "<</*thread.Tp+*/thread.Tc<<"          "<</*openMP.Tp+*/openMP.Tc<<"\n";
  //     ecrireFichier << endl << endl;
  //
  //
  //   }
  // }

  //ecrireFichier.close();

  return 0;
}
