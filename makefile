main.exe: main.o FonctionPlouffe.o FonctionChebyshev.o sequentiel.o thread.o OpenMP.o hpp/Analytique.hpp
	g++ -Wall -lpthread -lm -fopenmp -o main.exe main.o FonctionPlouffe.o FonctionChebyshev.o sequentiel.o thread.o OpenMP.o

OpenMP.o: OpenMP.cpp hpp/Analytique.hpp
	g++ -Wall -c -std=c++14 -lm -fopenmp OpenMP.cpp

thread.o: thread.cpp hpp/Analytique.hpp
	g++ -Wall -c -std=c++14 thread.cpp

sequentiel.o: sequentiel.cpp hpp/Analytique.hpp
	g++ -Wall -c -std=c++14 sequentiel.cpp

FonctionChebyshev.o: FonctionChebyshev.cpp hpp/Analytique.hpp
	g++ -Wall -c -std=c++14 FonctionChebyshev.cpp

FonctionPlouffe.o: FonctionPlouffe.cpp hpp/Analytique.hpp
	g++ -Wall -c -std=c++14 FonctionPlouffe.cpp

main.o:	main.cpp hpp/Analytique.hpp
	g++ -Wall -c -std=c++14 main.cpp

clean: cleano cleane

cleano: *.o
	rm *.o

cleane: main.exe
	rm main.exe
