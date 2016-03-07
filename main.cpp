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

void crearPiezas(vector<Pieza>& piezas){
	
	//PIEZAS JUGADOR 1

	Pieza peon1_1('P',1,0,1);
	piezas.push_back(peon1_1);
	Pieza peon2_1('P',1,1,1);
	piezas.push_back(peon2_1);
	Pieza peon3_1('P',1,2,1);
	piezas.push_back(peon3_1); 
	Pieza peon4_1('P',1,3,1);
	piezas.push_back(peon4_1);
	Pieza peon5_1('P',1,4,1);
	piezas.push_back(peon5_1);
	Pieza peon6_1('P',1,5,1);
	piezas.push_back(peon6_1);
	Pieza peon7_1('P',1,6,1);
	piezas.push_back(peon7_1);
	Pieza peon8_1('P',1,7,1);
	piezas.push_back(peon8_1);
	Pieza torre1_1('T',0,0,1);
	piezas.push_back(torre1_1);
	Pieza torre2_1('T',0,7,1);
	piezas.push_back(torre2_1);
	Pieza caballo1_1('C',0,1,1);
	piezas.push_back(caballo1_1);
	Pieza caballo2_1('C',0,6,1);
	piezas.push_back(caballo2_1);
	Pieza bishop1_1('B',0,2,1);
	piezas.push_back(bishop1_1);
	Pieza bishop2_1('B',0,5,1);
	piezas.push_back(bishop2_1);
	Pieza queen_1('Q',0,3,1);
	piezas.push_back(queen_1);
	Pieza king_1('K',0,4,1);
	piezas.push_back(king_1);
	
	//PIEZAS JUGADOR 2:

	Pieza peon1_2('P',6,0,2);
	piezas.push_back(peon1_2);
	Pieza peon2_2('P',6,1,2);
	piezas.push_back(peon2_2);
	Pieza peon3_2('P',6,2,2);
	piezas.push_back(peon3_2); 
	Pieza peon4_2('P',6,3,2);
	piezas.push_back(peon4_2);
	Pieza peon5_2('P',6,4,2);
	piezas.push_back(peon5_2);
	Pieza peon6_2('P',6,5,2);
	piezas.push_back(peon6_2);
	Pieza peon7_2('P',6,6,2);
	piezas.push_back(peon7_2);
	Pieza peon8_2('P',6,7,2);
	piezas.push_back(peon8_2);
	Pieza torre1_2('T',7,0,2);
	piezas.push_back(torre1_2);
	Pieza torre2_2('T',7,7,2);
	piezas.push_back(torre2_2);
	Pieza caballo1_2('C',7,1,2);
	piezas.push_back(caballo1_2);
	Pieza caballo2_2('C',7,6,2);
	piezas.push_back(caballo2_2);
	Pieza bishop1_2('B',7,2,2);
	piezas.push_back(bishop1_2);
	Pieza bishop2_2('B',7,5,2);
	piezas.push_back(bishop2_2);
	Pieza queen_2('Q',7,3,2);
	piezas.push_back(queen_2);
	Pieza king_2('K',7,4,2);
	piezas.push_back(king_2);

	return;
}

void llenarTablero(char** tablero, vector<Pieza> piezas){
	//llena el tablero de espacios
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			tablero[i][j]=' ';
		}
	}

	//agrega las piezas al tablero
	for (int i = 0; i < 32; ++i){
		for (int j = 0; j < 8; ++j){
			for (int k = 0; k < 8; ++k){
				tablero[piezas.at(i).getPosicioni()][piezas.at(i).getPosicionj()]=piezas.at(i).getTipo();
			}
		}
	}
	return;
}

void imprimirTablero(char** tablero){
	string espacio="      ";
	init_pair(1,COLOR_YELLOW,COLOR_WHITE);
	init_pair(2,COLOR_YELLOW,COLOR_BLACK);
	init_pair(3,COLOR_WHITE,COLOR_YELLOW);
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			if((i+j)%2==0){
				attrset(COLOR_PAIR(1));
				printw("%s%c%s",espacio.c_str(),tablero[i][j],espacio.c_str());	
			}
			else{
				attrset(COLOR_PAIR(2));
				printw("%s%c%s", espacio.c_str(),tablero[i][j],espacio.c_str());
			}
		}
		addch('\n');
	}
	attrset(COLOR_PAIR(3));
	return;
}