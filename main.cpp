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