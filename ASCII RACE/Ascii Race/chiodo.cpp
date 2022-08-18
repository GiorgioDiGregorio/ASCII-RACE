#include "chiodo.hpp"

chiodo::chiodo() {}

chiodo::chiodo(int x, int y, int dmg, int mul, char sy) :ostacoli(x, y, dmg, mul) {
	symb = sy;
}

void chiodo::stampaSuStrada(strada& s) {
	if (yPos < s.getH() + 3 && !despawn) {
		scrivi(s, yPos, xPos);
		scrivi(s, yPos, xPos + 1);
		scrivi(s, yPos - 1, xPos);
		scrivi(s, yPos - 1, xPos + 1);
		scrivi(s, yPos - 2, xPos);
		scrivi(s, yPos - 2, xPos + 1);
	}
	else despawn = true;
}

void chiodo::scrivi(strada& s, int y, int x) {
	if (y >= 0 && y < s.getH())
		s.mappa[y][x] = symb;
}

bool chiodo::getDespawn() { return despawn; }

bool chiodo::checkCollision(int x, int y) {
	if (((x >= xPos - 1 && x <= xPos + 2) && (y >= yPos && y <= yPos + 1)) //dal basso
		|| ((x <= xPos + 2 && x >= xPos) && (y >= yPos - 4 && y <= yPos + 1)) //da destra
		|| ((x <= xPos + 1 && x >= xPos - 1) && (y >= yPos - 4 && y <= yPos + 1)) //da sinistra
		|| ((x >= xPos - 1 && x <= xPos + 2) && (y >= yPos - 4 && y <= yPos - 3)) //dall'alto
		)
		return true;     //il giocatore ha colliso con un ostacolo "chiodo"
	else return false;   //nessuna collisione
}