main.exe: main.o sequentiel.o thread.o FonctionChebyshev.o FonctionPlouffe.o OpenMP.o
	g++ -Wall -lpthread -lm -fopenmp -o main.exe main.o FonctionChebyshev.o FonctionPlouffe.o sequentiel.o thread.o OpenMP.o

OpenMP.o: OpenMP.cpp
	g++ -Wall -c -std=c++11 -fopenmp OpenMP.cpp

thread.o: thread.cpp
	g++ -Wall -c -std=c++11 thread.cpp

sequentiel.o: sequentiel.cpp
	g++ -Wall -c -std=c++11 sequentiel.cpp

FonctionChebyshev.o: FonctionChebyshev.cpp
	g++ -Wall -c -std=c++11 FonctionChebyshev.cpp

FonctionPlouffe.o: FonctionPlouffe.cpp
	g++ -Wall -c -std=c++11 FonctionPlouffe.cpp

main.o:	main.cpp
	g++ -Wall -c -std=c++11 main.cpp

clean: cleano cleane

cleano: *.o
	rm *.o

cleane: main.exe
	rm main.exe
