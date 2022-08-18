#include "raddoppia.hpp"

raddoppia::raddoppia() {}

raddoppia::raddoppia(int x, int y, int dmg, int mul, char sy1, char sy2) :ostacoli(x, y, dmg, mul) {
	symb1 = sy1;
	symb2 = sy2;
	isSpawned = false;
}

void raddoppia::scrivi(strada& s, int y, int x, char smb) {
	if (y >= 0 && y < s.getH()) {
		s.mappa[y][x] = smb;
	}
}

void raddoppia::stampaSuStrada(strada& s) {
	if (yPos < s.getH() + 1 && isSpawned) {
		scrivi(s, yPos, xPos, symb1);
		scrivi(s, yPos, xPos + 1, symb2);
	}
	else isSpawned = false;
}

bool raddoppia::getSpawned() { return isSpawned; }

void raddoppia::setSpawned(bool s) {
	isSpawned = s;
}

void raddoppia::setPosX(int x) { xPos = x; }

void raddoppia::setPosY(int y) { yPos = y; }

bool raddoppia::checkCollision(int x, int y) {
	if (((x >= xPos - 1 && x <= xPos + 2) && (y >= yPos + 1 && y <= yPos - 1))
		|| ((x >= xPos && x <= xPos + 2) && (y >= yPos - 2 && y <= yPos + 1))
		|| ((x >= xPos - 1 && x <= xPos + 1) && (y >= yPos - 2 && y <= yPos + 1))
		|| ((x >= xPos - 1 && x <= xPos + 2) && (y >= yPos - 2 && y <= yPos - 1))) {
		isSpawned = false;
		return true;   //il giocatore ha colliso con un bonus "raddoppia punti"
	}
	else return false;  //nessuna collisione
}