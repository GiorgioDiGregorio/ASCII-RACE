#include "enemy.hpp"

enemy::enemy() {}

enemy::enemy(int x, int y, int dmg, int mul, char sy) :ostacoli(x, y, dmg, mul) {
    symb = sy;
}

void enemy::stampaSuStrada(strada& s) {
    if (yPos < s.getH() + 4 && !despawn) {
        scrivi(s, yPos, xPos + 1);
        scrivi(s, yPos - 1, xPos + 1);
        scrivi(s, yPos - 1, xPos);
        scrivi(s, yPos - 1, xPos + 2);
        scrivi(s, yPos - 2, xPos + 1);
        scrivi(s, yPos - 3, xPos + 1);
        scrivi(s, yPos - 3, xPos);
        scrivi(s, yPos - 3, xPos + 2);
    }
    else despawn = true;
}

void enemy::scrivi(strada& s, int y, int x) {
    if (y >= 0 && y < s.getH())
        s.mappa[y][x] = symb;
}

bool enemy::getDespawn() { return despawn; }

bool enemy::checkCollision(int x, int y) {
    if (((x >= xPos - 1 && x <= xPos + 3) && (y >= yPos && y <= yPos + 1)) //dal basso
        || ((x <= xPos + 3 && x >= xPos) && (y >= yPos - 5 && y <= yPos + 1)) //da destra
        || ((x <= xPos + 2 && x >= xPos - 1) && (y >= yPos - 5 && y <= yPos + 1)) //da sinistra
        || ((x >= xPos - 1 && x <= xPos + 3) && (y >= yPos - 5 && y <= yPos - 4)) //dall'alto
        )
        return true;    //Il giocatore ha colliso con un ostacolo "macchina nemica"
    else return false;  //Nessuna collisione
}