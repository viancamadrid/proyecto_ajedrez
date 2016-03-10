#include <ncurses.h>
#include "pieza.h"
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iostream> 

using std::ifstream;
using std::ofstream;
using std::vector;
using std::string;
using std::abs;
using namespace std;

void crearPartida(vector<Pieza>&);
void cargarPartida(vector<Pieza>&);
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
bool moveTorre(int,int,int,int,char**);
bool moveCaballo(int,int,int,int);
bool moveBishop(int,int,int,int);
bool moveQueen();
bool moveKing(int, int, int, int);
void eliminarMover(char*);
bool jaque(vector<Pieza>,int,int,char**);
bool jaquePeon(int,int,int,int);
bool jaqueTorre(int,int,int,int,char**);
bool nadaEnmedioTorre(int,int,int,int,char**);
bool jaqueCaballo(int,int,int,int);
bool jaqueBishop(int,int,int,int,char**);

int main(int argc, char const *argv[]){
	initscr();
	start_color();
	vector<Pieza> piezas;
	crearPiezas(piezas);
	char**tablero=crearTablero();
	llenarTablero(tablero, piezas);
	int turno=1;
	int op=menu();

	/*while(op!=52){

	}*/


	if(op==51){
		op=instrucciones();
	}
	if(op==49){
		clear();
		imprimirTablero(tablero);
		int op2=menu2();
		while(op2!=50 && op2!=51){
			//if(!(jaque(tablero,piezas,turno))){
				clear();
				imprimirTablero(tablero);
				move(10,10);
				char* mover=crearMover();
				makeMove(piezas,tablero,turno,mover);
				llenarTablero(tablero,piezas);
				clear();
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
			//}
		}
		if(op2==50){
			crearPartida(piezas);
		}
	}else if(op==50){
		cargarPartida(piezas);
		clear();
		imprimirTablero(tablero);
		int op2=menu2();
		while(op2!=50 && op2!=51){
			//if(!(jaque(tablero,piezas,turno))){
				clear();
				imprimirTablero(tablero);
				move(10,10);
				char* mover=crearMover();
				makeMove(piezas,tablero,turno,mover);
				llenarTablero(tablero,piezas);
				clear();
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
			//}
		}
		if(op2==50){
			crearPartida(piezas);
		}else if(op2==51){
			clear();
			move(20,10);
			printw("GRACIAS POR JUGAR!");
			getch();
		}
	}else if(op==52){
		clear();
		move(20,10);
		printw("GRACIAS POR JUGAR!");
		getch();
	}
	clear();
	refresh();
	getch();
	endwin();
	return 0;
}

void crearPartida(vector<Pieza>& piezas){
	ofstream out_file("partida.bin",ios::out|ios::binary);
	for (int i = 0; i < 32; ++i){
		out_file.write((char*)&piezas[i],sizeof(Pieza));
	}
	out_file.flush();
	out_file.close();
}

void cargarPartida(vector<Pieza>& piezas){
	ifstream in_file("partida.bin",ios::in|ios::binary);
	while(in_file.eof()){
		Pieza temp;
		in_file.read(reinterpret_cast<char*>(&temp),sizeof(Pieza));
		piezas.push_back(temp);
	}
	in_file.close();
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
	string espacio="\t";
	char numero=' ';
	init_pair(1,COLOR_YELLOW,COLOR_WHITE);
	init_pair(2,COLOR_YELLOW,COLOR_BLACK);
	init_pair(3,COLOR_WHITE,COLOR_BLACK);
	attrset(COLOR_PAIR(3));
	//printw("A\t\tB\t\tC\t\tD\t\tE\t\tF\t\tG\t\tH\n");
	printw("\tA\t\tB\t\tC\t\tD\t\tE\t\tF\t\tG\t\tH\n");
	int num=8;
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
		attrset(COLOR_PAIR(3));
		printw("%c%d%c",'\t',num,'\n');
		num--;
	}
	attrset(COLOR_PAIR(2));
	return;
}

void makeMove(vector<Pieza>&  piezas, char** tablero, int jugador, char* mover){
	int i1, j1, i2, j2;
	bool bandera=false;
	printw("Ingresar la Coordenada en Mayusculas");
	move(11,10);
	printw("Ejemplo: B7B6");
	move(12,10);
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
		bool movimiento=moveTorre(i1,i2,j1,j2,tablero);
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

bool moveTorre(int i1, int i2, int j1, int j2, char ** tablero){
	//bool mover=false;
	if(nadaEnmedioTorre(i1,i2,j1,j2,tablero)){
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


//jaque , el rey es amenazado
//jaquemate, el rey no tiene escapatoria
//validar los movimientos validos para cada pieza y si una toca al rey enemigo entonces es jaque

bool jaque(vector<Pieza> piezas, int jugador, int enemigo, char** tablero){
	vector<Pieza> piezas2;
	int pos_i_enemigo, pos_j_enemigo, pos_i_jugador, pos_j_jugador;

	//mira las piezas del jugador

	for (int i = 0; i < 32; ++i){
		if(piezas.at(i).getJugador()==jugador){//agrega las piezas que tiene ese juagdor a un vector
			piezas2.push_back(piezas.at(i));
		}
		if(piezas.at(i).getJugador()==enemigo && piezas.at(i).getTipo()=='K'){
			pos_i_enemigo=piezas.at(i).getPosicioni();
			pos_j_enemigo=piezas.at(i).getPosicionj();
		}
	}

	for (int i = 0; i < piezas2.size(); ++i){
		if(piezas2.at(i).getTipo()=='P'){//busca los peones
			pos_i_jugador=piezas2.at(i).getPosicioni();
			pos_j_jugador=piezas2.at(i).getPosicionj();
			if(jaquePeon(pos_i_jugador,pos_j_jugador,pos_i_enemigo,pos_j_enemigo)){
				return true;
			}
		}else if(piezas2.at(i).getTipo()=='T'){//busca las torres
			if(jaqueTorre(pos_i_jugador,pos_j_jugador,pos_i_enemigo,pos_j_enemigo,tablero)){
				return true;
			}
		}else if(piezas2.at(i).getTipo()=='C'){
			if(jaqueCaballo(pos_i_jugador,pos_j_jugador,pos_i_enemigo,pos_j_enemigo)){
				return true;
			}
			return false;
		}else if(piezas2.at(i).getTipo()=='B'){
			
		}else if(piezas2.at(i).getTipo()=='Q'){
			
		}else if(piezas2.at(i).getTipo()=='K'){
			
		}
	}
	return false;
}


bool jaquePeon(int i_jugador, int j_jugador, int i_enemigo, int j_enemigo){//si el peon esta justo detras del rey
	if((i_jugador==i_enemigo+1) && (j_jugador==j_enemigo)){
		return true;
	}
	return false;
}

bool jaqueTorre(int i_jugador, int j_jugador, int i_enemigo, int j_enemigo, char** tablero){
	if(nadaEnmedioTorre(i_jugador,j_jugador,i_enemigo, j_enemigo,tablero)){
		return true;
	}
	return false;
}

bool nadaEnmedioTorre(int i1, int j1, int i2, int j2, char** tablero){
	if(i1==i2){
		if(j2>j1){//la posicion j del rey es mayor a la de la torre
			for (int i = j1; i <j2; ++i){
				if(tablero[i1][i]!=' '){//si no hay un espacio entonces hay una pieza en el camino
					return false;
				}
			}
			return true;
		}else{//la posicion j de la torre es mayor a la del rey
			for (int i = j2; i <j1; ++i){
				if(tablero[i1][i]!=' '){
					return false;
				}
			}
			return true;
		}
	}else if(j1==j2){
		if(i2>i1){//la posicion i del rey es mayor a la de la torre
			for (int i = i1; i <i2; ++i){
				if(tablero[i][j1]!=' '){//si no hay un espacio entonces hay una pieza en el camino
					return false;
				}
			}
			return true;
		}else{//la posicion i de la torre es mayor a la del rey
			for (int i = i2; i <i1; ++i){
				if(tablero[i][j1]!=' '){
					return false;
				}
			}
			return true;
		}
	}
	return false;// si las posiciones no estan en la misma linea
}

bool jaqueCaballo(int i1, int j1, int i2, int j2){
	if(moveCaballo(i1,j1,i2,j2)){
		return true;
	}
	return false;
}

bool jaqueBishop(int i1, int j1, int i2, int j2, char** tablero){

}

/*
if((i1+j1)==(i2+j2)){
		return true;
}else if(abs(i1-j1)==abs(i2-j2)){
		return true;
}
return false;

*/