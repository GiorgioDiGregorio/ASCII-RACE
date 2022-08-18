#include "scudo.hpp"

scudo::scudo() {}

scudo::scudo(int x, int y, int dmg, int mul, char sy1, char sy2) :ostacoli(x, y, dmg, mul) {
	symb1 = sy1;
	symb2 = sy2;
	isSpawned = false;
}

void scudo::scrivi(strada& s, int y, int x, char smb) {
	if (y >= 0 && y < s.getH()) {
		s.mappa[y][x] = smb;
	}
}

void scudo::stampaSuStrada(strada& s) {
	if (yPos < s.getH() + 2 && isSpawned) {
		scrivi(s, yPos, xPos, symb2);
		scrivi(s, yPos, xPos + 1, symb1);
		scrivi(s, yPos - 1, xPos, symb1);
		scrivi(s, yPos - 1, xPos + 1, symb2);
	}
	else isSpawned = false;
}

bool scudo::getSpawned() { return isSpawned; }

void scudo::setPosX(int x) { xPos = x; }

void scudo::setPosY(int y) { yPos = y; }

void scudo::setSpawned(bool s) {
	isSpawned = s;
}

bool scudo::checkCollision(int x, int y) {
	if (((x >= xPos - 1 && x <= xPos + 3) && (y >= yPos + 1 && y <= yPos - 1))
		|| ((x >= xPos && x <= xPos + 3) && (y >= yPos - 3 && y <= yPos + 1))
		|| ((x >= xPos - 1 && x <= xPos + 1) && (y >= yPos - 3 && y <= yPos + 1))
		|| ((x >= xPos - 1 && x <= xPos + 1) && (y >= yPos - 3 && y <= yPos - 2))) {
		isSpawned = false;
		return true;     //il giocatore ha colliso con un bonus "scudo"
	}
	else return false;   //nessuna collisione
}