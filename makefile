main.exe: main.o sequentiel.o thread.o FonctionChebyshev.o FonctionPlouffe.o OpenMP.o
	g++ -Wall -lpthread -lm -fopenmp -o main.exe main.o FonctionChebyshev.o FonctionPlouffe.o sequentiel.o thread.o OpenMP.o

OpenMP.o: OpenMP.cpp
	g++ -Wall -c -std=c++14 -fopenmp OpenMP.cpp

thread.o: thread.cpp
	g++ -Wall -c -std=c++14 thread.cpp

sequentiel.o: sequentiel.cpp
	g++ -Wall -c -std=c++14 sequentiel.cpp

FonctionChebyshev.o: FonctionChebyshev.cpp
	g++ -Wall -c -std=c++14 FonctionChebyshev.cpp

FonctionPlouffe.o: FonctionPlouffe.cpp
	g++ -Wall -c -std=c++14 FonctionPlouffe.cpp

main.o:	main.cpp
	g++ -Wall -c -std=c++14 main.cpp

clean: cleano cleane

cleano: *.o
	rm *.o

cleane: main.exe
	rm main.exe
