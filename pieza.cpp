#include "pieza.h"

Pieza::Pieza(char tipo, int posicion_i, int posicion_j, int jugador){
	this-> tipo=tipo;
	this-> posicion_i=posicion_i;
	this-> posicion_j=posicion_j;
	this-> jugador=jugador;
}

void Pieza::setTipo(char tipo){
	this-> tipo=tipo;
}
void Pieza::setPosicioni(int posicion_i){
	this-> posicion_i=posicion_i;
}
void Pieza::setPosicionj(int posicion_j){
	this-> posicion_j=posicion_j;
}
void Pieza::setJugador(int jugador){
	this-> jugador=jugador;
}

//------------------------------------------

char Pieza::getTipo(){
	return tipo;
}
int Pieza::getPosicioni(){
	return posicion_i;
}
int Pieza::getPosicionj(){
	return posicion_j;
}
int Pieza::getJugador(){
	return jugador;
}