#include <ncurses.h>
#include "pieza.h"
#include <vector>
#include <string>
#include <cmath>

using std::vector;
using std::string;
using std::abs;

char* crearMover();
char** crearTablero();
void crearPiezas(vector<Pieza>&);
void llenarTablero(char**, vector<Pieza>);
void imprimirTablero(char**);
void makeMove(vector<Pieza>&, char**, int, char*);
bool movePeon(int,int,int,int,int);
int convertir(char);
bool moveTorre(int,int,int,int);
bool moveCaballo(int,int,int,int);
bool moveBishop(int,int,int,int);
bool moveQueen();
bool moveKing(int, int, int, int);
void eliminarMover(char*);
bool muerteRey(int ,int,int, char** , vector<Pieza>);
bool jaque(char**, vector<Pieza>, int);

int main(int argc, char const *argv[]){
	initscr();
	start_color();
	vector<Pieza> piezas;
	crearPiezas(piezas);
	char**tablero=crearTablero();
	llenarTablero(tablero, piezas);
	imprimirTablero(tablero);
	int turno=1;
	
	while(!(jaque())){
		move(10,10);
		char* mover=crearMover();
		makeMove(piezas,tablero,turno,mover);
		clear();
		llenarTablero(tablero,piezas);
		imprimirTablero(tablero);
		eliminarMover(mover);
		refresh();
		turno++;
		if(turno%2==0){
			turno=2;
		}else{
			turno=1;
		}
	}

	clear();
	refresh();
	getch();
	endwin();
	return 0;
}

char* crearMover(){
	char* mover= new char[4];
	return mover;
}

char** crearTablero(){
	char**tablero=new char*[8];
	for (int i = 0; i < 8; ++i){
		tablero[i]=new char[8];
	}
	return tablero;	
}
