#include "car.hpp"
#include <iostream>
using namespace std;

car::car() {}

car::car(int posx, int posy, char sy) {
	posX = posx;
	posY = posy;
	symb = sy;
}

int car::getPosX() {
	return posX;
}
int car::getPosY() {
	return posY;
}

//Gestione del movimento in base all'input da tastiera (utilizzo di enumeration) (la macchina utente si muove di 4 in 4 per velocizzare il movimento)
void car::muovi(eDir direction) {
	switch (direction) {
	case STOP:
		break;
	case UP:
		posY = posY - mov;
		break;
	case RIGHT:
		posX = posX + mov;
		break;
	case DOWN:
		posY = posY + mov;
		break;
	case LEFT:
		posX = posX - mov;
		break;
	}
}

void car::scriviSuStrada(strada &s) {
	s.mappa[posY][posX] = symb;
	s.mappa[posY+1][posX] = symb;
	s.mappa[posY+2][posX] = symb;
	s.mappa[posY-1][posX] = symb;
	s.mappa[posY][posX-1] = symb;
	s.mappa[posY][posX+1] = symb;
	s.mappa[posY+2][posX-1] = symb;
	s.mappa[posY+2][posX+1] = symb;
}

void car::setSymb(char s) { symb = s; }
