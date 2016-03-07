#include <ncurses.h>
#include "pieza.h"
#include <vector>
#include <string>
#include <cmath>

using std::vector;
using std::string;
using std::abs;

int menu();
int menu2();
int instrucciones();
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
	//imprimirTablero(tablero);
	int turno=1;
	int op=menu();

	if(op==51){
		op=instrucciones();
	}
	if(op==49){
		clear();
		imprimirTablero(tablero);
		int op2=menu2();
		while(op2!=50 && op2!=51){
			clear();
			imprimirTablero(tablero);
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
			op2=menu2();
		}
	}else if(op==52){

	}
	clear();
	refresh();
	getch();
	endwin();
	return 0;
}

int menu(){
	init_pair(1,COLOR_BLACK,COLOR_WHITE);
	init_pair(2,COLOR_YELLOW,COLOR_BLACK);
	attrset(COLOR_PAIR(1));
	int x,y;
	getmaxyx(stdscr,y,x);
	move(y/2,(x/2)-20);
	printw("---MENU AJEDREZ---");
	move(1+y/2,(x/2)-20);
	attrset(COLOR_PAIR(2));
	printw("1. Nueva Partida");
	move(2+y/2,(x/2)-20);
	printw("2. Cargar Partida");
	move(3+y/2,(x/2)-20);
	printw("3. Como Jugar Ajedrez");
	move(4+y/2,(x/2)-20);
	printw("4. Salir");
	move(5+y/2,(x/2)-20);
	printw("Opcion: ");
	int opcion = getch();
	return opcion;
}

int menu2(){
	int x,y;
	getmaxyx(stdscr,y,x);
	move(y/2,(x/2)-20);
	printw("1. Continuar");
	move(1+y/2,(x/2)-20);
	printw("2. Guardar Partida y Salir");
	move(2+y/2,(x/2)-20);
	printw("3. Salir");
	move(3+y/2,(x/2)-20);
	printw("Opcion: ");
	int opcion = getch();
	return opcion;
}

int instrucciones(){
	clear();
	int x,y;
	init_pair(1,COLOR_BLACK,COLOR_WHITE);
	init_pair(2,COLOR_YELLOW,COLOR_BLACK);
	attrset(COLOR_PAIR(1));
	getmaxyx(stdscr,y,x);
	move(y/2,(x/2)-20);
	printw("--MOVIMIENTOS--");
	attrset(COLOR_PAIR(2));
	move(1+y/2,(x/2)-20);
	printw("PEON: una casilla enfrente");
	move(2+y/2,(x/2)-20);
	printw("TORRE: en linea recta horizontal o vertical");
	move(3+y/2,(x/2)-20);
	printw("CABALLO: una casilla arriba y dos a un lado o al reves");
	move(4+y/2,(x/2)-20);
	printw("ALFIL: en diagonal");
	move(5+y/2,(x/2)-20);
	printw("REINA: cualquier casilla");
	move(6+y/2,(x/2)-20);
	printw("REY: una casilla hacia cualquier lado");
	move(7+y/2,(x/2)-20);
	printw("PRESIONE ENTER");
	if((getch())=='\n'){
		clear();
		int avanzar=menu();
		return avanzar;	
	}
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
	//init_pair(3,COLOR_WHITE,COLOR_YELLOW);
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
	attrset(COLOR_PAIR(2));
	return;
}

void makeMove(vector<Pieza>&  piezas, char** tablero, int jugador, char* mover){
	int i1, j1, i2, j2;
	bool bandera=false;
	printw("%s%d%s","Ingrese Coordenada Jugador ",jugador," : ");
	char ingresada=getch();
	while(!(((int)ingresada>=65 && (int)ingresada<=72))){
		ingresada=getch();
	}
	mover[0]=ingresada;

	ingresada=getch();
	while(!(((int)ingresada>=49 && (int)ingresada<=56))){
		ingresada=getch();
	}
	mover[1]=ingresada;

	ingresada=getch();
	while(!(((int)ingresada>=65 && (int)ingresada<=72))){
		ingresada=getch();
	}
	mover[2]=ingresada;

	ingresada=getch();
	while(!(((int)ingresada>=49 && (int)ingresada<=56))){
		ingresada=getch();
	}
	mover[3]=ingresada;

	move(15,15);
	i1=convertir(mover[1]);
	j1=convertir(mover[0]);
	i2=convertir(mover[3]);
	j2=convertir(mover[2]);
	
	char pieza=tablero[i1][j1];
	if(pieza=='P'){
		bool movimiento=movePeon(i1,i2,j1,j2,jugador);
		if(movimiento){
			for (int i = 0; i < 32; ++i){
				if((piezas.at(i).getTipo()==pieza) && (piezas.at(i).getPosicioni()==i1) && (piezas.at(i).getPosicionj()==j1) && (piezas.at(i).getJugador()==jugador)){
					piezas.at(i).setPosicioni(i2);
					piezas.at(i).setPosicionj(j2);
				}
			}
		}else{
			move(15,15);
			printw("%s","NO PUEDES MOVERLA! PERDISTE EL TURNO");
		}
	}else if(pieza=='T'){
		bool movimiento=moveTorre(i1,i2,j1,j2);
		if(movimiento){
			for (int i = 0; i < 32; ++i){
				if((piezas.at(i).getTipo()==pieza) && (piezas.at(i).getPosicioni()==i1) && (piezas.at(i).getPosicionj()==j1) && (piezas.at(i).getJugador()==jugador)){
					piezas.at(i).setPosicioni(i2);
					piezas.at(i).setPosicionj(j2);
				}
			}
		}else{
			move(15,15);
			printw("%s","NO PUEDES MOVERLA! PERDISTE EL TURNO");
		}
	}else if(pieza=='C'){
		if(moveCaballo(i1,i2,j1,j2)){
			for (int i = 0; i < 32; ++i){
				if((piezas.at(i).getTipo()==pieza) && (piezas.at(i).getPosicioni()==i1) && (piezas.at(i).getPosicionj()==j1) && (piezas.at(i).getJugador()==jugador)){
					piezas.at(i).setPosicioni(i2);
					piezas.at(i).setPosicionj(j2);
				}
			}
		}else{
			move(15,15);
			printw("%s","NO PUEDES MOVERLA! PERDISTE EL TURNO");
		}
	}else if(pieza=='B'){
		if(moveBishop(i1,i2,j1,j2)){
			for (int i = 0; i < 32; ++i){
				if((piezas.at(i).getTipo()==pieza) && (piezas.at(i).getPosicioni()==i1) && (piezas.at(i).getPosicionj()==j1) && (piezas.at(i).getJugador()==jugador)){
					piezas.at(i).setPosicioni(i2);
					piezas.at(i).setPosicionj(j2);
				}
			}
		}else{
			move(15,15);
			printw("%s","NO PUEDES MOVERLA! PERDISTE EL TURNO");
		}
	}else if(pieza=='Q'){
		if(moveQueen()){
			for (int i = 0; i < 32; ++i){
				if((piezas.at(i).getTipo()==pieza) && (piezas.at(i).getPosicioni()==i1) && (piezas.at(i).getPosicionj()==j1) && (piezas.at(i).getJugador()==jugador)){
					piezas.at(i).setPosicioni(i2);
					piezas.at(i).setPosicionj(j2);
				}
			}
		}else{
			move(15,15);
			printw("%s","NO PUEDES MOVERLA! PERDISTE EL TURNO");
		}
	}else if(pieza=='K'){
		if(moveKing(i1,i2,j1,j2)){
			for (int i = 0; i < 32; ++i){
				if((piezas.at(i).getTipo()==pieza) && (piezas.at(i).getPosicioni()==i1) && (piezas.at(i).getPosicionj()==j1) && (piezas.at(i).getJugador()==jugador)){
					piezas.at(i).setPosicioni(i2);
					piezas.at(i).setPosicionj(j2);
				}
			}
		}else{
			move(15,15);
			printw("%s","NO PUEDES MOVERLA! PERDISTE EL TURNO");
		}
	}
}

void eliminarMover(char* mover){
	delete[] mover;
	return;
}

bool movePeon(int i1, int i2, int j1, int j2, int jugador){
	bool mover=false;
	if(jugador==1){
		if((j1==j2) && (i2==i1+1))
			mover=true;
	}else{
		if((j1==j2) && (i1==i2+1))
			mover=true;
	}
	return mover;
}

bool moveTorre(int i1, int i2, int j1, int j2){
	//bool mover=false;
	if((j1==j2) || (i1==i2)){
		 return true;
	}
	return false;
}

bool moveCaballo(int i1, int i2, int j1, int j2){

	if(((i1==i2+2) && (j2==j1+1)) || ((i1==i2+2)&& (j2=j1-1))){
		return true;
	}else if(((i2==i1+2) && (j1==j2+1)) || ((i2==i1+2)&& (j1==j2-1))){
		return true;
	}else if(((i2==i1-1) && (j2==j1+2)) || ((i1==i2+1) && (j2==j1+2))){
		return true;
	}else if(((i2==i1+1)&&(j2==j1+2)) || ((i2==i1+1)&&(j2==j1-2))){
		return true;
	}
	return false;
}

bool moveBishop(int i1, int i2, int j1, int j2){
	if((i1+j1)==(i2+j2)){
		return true;
	}else if(abs(i1-j1)==abs(i2-j2)){
		return true;
	}
	return false;
}

bool moveQueen(){
	return true;
}

bool moveKing(int i1, int i2, int j1, int j2){
	if((i2==i1-1) && (j2==j1-1)){
		return true;
	}else if((j1==j2) && (i2==i1-1)){
		return true;
	}else if((i2==i1-1) && (j2==j1+1)){
		return true;
	}else if((i1==i2) && (j2==j1-1)){
		return true;
	}else if((i1==i2) && (j2=j1+1)){
		return true;
	}else if((i2==i1+1) && (j2==j1-1)){
		return true;
	}else if((i2==i1+1) && (j2==j1)){
		return true;
	}else if((i2==i1+1) && (j2==j1+1)){
		return true;
	}
}

int convertir(char caracter){
	if(caracter=='A' || caracter=='8'){
		return 0;
	}else if(caracter=='B' || caracter=='7'){
		return 1;
	}else if(caracter=='C' || caracter=='6'){
		return 2;
	}else if(caracter=='D' || caracter=='5'){
		return 3;
	}else if(caracter=='E' || caracter=='4'){
		return 4;
	}else if(caracter=='F' || caracter=='3'){
		return 5;
	}else if(caracter=='G' || caracter=='2'){
		return 6;
	}else if(caracter=='H' || caracter=='1'){
		return 7;
	}
}

bool jaque(char** tablero, vector<Pieza> piezas, int jugador){
	for (int i = 0; i < 32; ++i){
		for (int j = 0; j < 8; ++j){
			for (int k = 0; k < 8; ++k){
				if(piezas.at(i).getTipo()=='K' && piezas.at(i).getJugador()==jugador){
					if(muerteRey(i,j,jugador,tablero,piezas)){
						return true;
					}else{
						return false;
					}
				}
			}			
		}
	}
}


bool muerteRey(int i1,int j1,int jugador, char** tablero, vector<Pieza> piezas){
	int contrario=1;
	if(jugador==1){
		contrario=2;
	}

	for (int i = 0; i < 32; ++i){
		if(piezas.at(i).getTipo()=='B' && piezas.at(i).getJugador()==contrario){//alfil del otro jugador
			if(abs(piezas.at(i).getPosicioni()-piezas.at(i).getPosicionj()) == abs(i1-j1)){//alfil en la diagonal izquierda
				return true;
			}else if((piezas.at(i).getPosicioni()+piezas.at(i).getPosicionj())== (i1+j1)){//alfil en la diagonal derecha
				return true;
			}
		}else if(piezas.at(i).getTipo()=='T' && piezas.at(i).getJugador()==contrario){//torre del otro jugador
			if(piezas.at(i).getPosicioni()==i1){//torre en la misma linea horizontal
				return true;
			}else if(piezas.at(i).getPosicionj()==j1){//torre en la misma linea vertical
				return true;
			}
		}else if(piezas.at(i).getTipo()=='Q' && piezas.at(i).getJugador()==contrario){//reina del otro jugador
			if(abs(piezas.at(i).getPosicioni()-piezas.at(i).getPosicionj()) == abs(i1-j1)){//reina en la diagonal izquierda
				return true;
			}else if((piezas.at(i).getPosicioni()+piezas.at(i).getPosicionj())== (i1+j1)){//reina en la diagonal derecha
				return true;
			}else if(piezas.at(i).getPosicioni()==i1){//reina en la misma linea horizontal
				return true;
			}else if(piezas.at(i).getPosicionj()==j1){//reina en la misma linea vertical
				return true;
			}
		}else if(piezas.at(i).getTipo()=='Q' && piezas.at(i).getJugador()==contrario){//caballo del otro juagdor
			if(((i1==piezas.at(i).getPosicioni()+2) && (piezas.at(i).getPosicionj()==j1+1)) || ((i1==piezas.at(i).getPosicioni()+2)&& (piezas.at(i).getPosicionj()==j1-1))){
				return true;
			}else if(((piezas.at(i).getPosicioni()==i1+2) && (j1==piezas.at(i).getPosicionj()+1)) || ((piezas.at(i).getPosicioni()==i1+2)&& (j1=piezas.at(i).getPosicionj()-1))){
				return true;
			}else if(((piezas.at(i).getPosicioni()==i1-1) && (piezas.at(i).getPosicionj()==j1+2)) || ((i1==piezas.at(i).getPosicioni()+1) && (piezas.at(i).getPosicionj()==j1+2))){
				return true;
			}else if(((piezas.at(i).getPosicioni()==i1+1)&&(piezas.at(i).getPosicionj()==j1+2)) || ((piezas.at(i).getPosicioni()==i1+1)&&(piezas.at(i).getPosicionj()==j1-2))){
				return true;
			}
		}else if(piezas.at(i).getTipo()=='P' && piezas.at(i).getJugador()==contrario){//peon del otro jugador
			if(contrario==1){//si el jugador contrario el es el jugador 1
				if((j1==piezas.at(i).getPosicionj()) && (piezas.at(i).getPosicioni()==i1+1)){//peon arriba del rey
					return true;
				}
			}else if((j1==piezas.at(i).getPosicionj()) && (i1==piezas.at(i).getPosicioni()+1)){//peon del jugador 2 debajo del rey
				return true;
			}
		}
	}
	return false;
}



