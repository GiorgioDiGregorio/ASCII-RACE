#include "tronco.hpp"

tronco::tronco() {}

tronco::tronco(int x, int y, int dmg, int mul, char sy) :ostacoli(x, y, dmg, mul) {
	symb = sy;
}

void tronco::stampaSuStrada(strada& s) {
	if (yPos < s.getH() + 2 && !despawn) {
		scrivi(s, yPos, xPos);
		scrivi(s, yPos, xPos + 1);
		scrivi(s, yPos, xPos + 2);
		scrivi(s, yPos, xPos + 3);
		scrivi(s, yPos - 1, xPos);
		scrivi(s, yPos - 1, xPos + 1);
		scrivi(s, yPos - 1, xPos + 2);
		scrivi(s, yPos - 1, xPos + 3);
	}
	else despawn = true;
}

void tronco::scrivi(strada& s, int y, int x) {
	if (y >= 0 && y <= s.getH() - 1)
		s.mappa[y][x] = symb;
}

bool tronco::getDespawn() { return despawn; }

bool tronco::checkCollision(int x, int y) {
	if (((x >= xPos - 1 && x <= xPos + 4) && (y >= yPos && y <= yPos + 1)) //dal basso
		|| ((x <= xPos + 4 && x >= xPos) && (y >= yPos - 3 && y <= yPos + 1)) //da destra
		|| ((x <= xPos + 3 && x >= xPos - 1) && (y >= yPos - 3 && y <= yPos + 1)) //da sinistra
		|| ((x >= xPos - 1 && x <= xPos + 4) && (y >= yPos - 3 && y <= yPos - 2)) //dall'alto
		)
		return true;     //Il giocatore ha colliso con un ostacolo "tronco"
	else return false;   //Nessuna collisione
}