#ifndef PIEZA_H
#define PIEZA_H

class Pieza{
	char tipo;
	int posicion_i;
	int posicion_j;
	int jugador;

public:
	Pieza(char, int, int, int);
	void setTipo(char tipo);
	void setPosicioni(int posicion_i);
	void setPosicionj(int posicion_j);
	void setJugador(int jugador);
	char getTipo();
	int getPosicioni();
	int getPosicionj();
	int getJugador();
};

#endif