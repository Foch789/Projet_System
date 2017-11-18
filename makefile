all: main.exe clean

clean: *.o
	rm *.o

main.exe: main.o sequentiel.o thread.o FonctionChebyshev.o FonctionPlouffe.o
	g++ -Wall -o main.exe main.o FonctionChebyshev.o FonctionPlouffe.o sequentiel.o thread.o -lpthread -lm

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
