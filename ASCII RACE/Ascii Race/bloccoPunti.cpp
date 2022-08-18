#include "bloccoPunti.hpp"

bloccoPunti::bloccoPunti() {}

bloccoPunti::bloccoPunti(int x, int y, int dmg, int mul, char sy1, char sy2) : ostacoli(x, y, dmg, mul) {
	symb1 = sy1;
	symb2 = sy2;
}

void bloccoPunti::scrivi(strada& s, int y, int x, char smb) {
	if (y >= 0 && y < s.getH()) {
		s.mappa[y][x] = smb;
	}
}

void bloccoPunti::stampaSuStrada(strada& s) {
	if (yPos < s.getH() + 1 && !despawn) {
		scrivi(s, yPos, xPos, symb1);
		scrivi(s, yPos, xPos + 1, symb2);
		scrivi(s, yPos, xPos + 2, symb2);
	}
	else despawn = true;
}

bool bloccoPunti::getDespawn() { return despawn; }

bool bloccoPunti::checkCollision(int x, int y) {
	if (((x >= xPos - 1 && x <= xPos + 3) && (y >= yPos && y <= yPos + 1)) //dal basso
		|| ((x <= xPos + 3 && x >= xPos) && (y >= yPos - 2 && y <= yPos + 1)) //da destra
		|| ((x <= xPos + 2 && x >= xPos - 1) && (y >= yPos - 2 && y <= yPos + 1)) //da sinistra
		|| ((x >= xPos - 1 && x <= xPos + 3) && (y >= yPos - 2 && y <= yPos - 1)) //dall'alto
		)
		return true;    //il giocatore ha colliso con un bonus "blocco Punti"
	else return false;  //nessuna collisione
}