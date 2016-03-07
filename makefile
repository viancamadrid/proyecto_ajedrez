exe: main.o pieza.o
	g++ main.o pieza.o -lncurses

main.o: main.cpp pieza.h
	g++ -c main.cpp -lncurses

pieza.o:	pieza.h pieza.cpp
	g++ -c pieza.cpp