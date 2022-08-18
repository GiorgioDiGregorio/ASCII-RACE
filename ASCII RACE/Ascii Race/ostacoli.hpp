#ifndef OSTACOLI_H
#define OSTACOLI_H
#include "strada.hpp"
class ostacoli {
protected:
	int xPos;
	int yPos;
	int damage;
	int multi;    //moltiplicatore usato in getDamage per assegnare il danno dell'ostacolo, in base al livello corrente
	bool despawn; //usata quando oggetto deve essere eliminato dalla lista (uscito fuori dalla mappa, o collisione avvenuta)
public:
	ostacoli();
	ostacoli(int x, int y, int dmg, int mul);
	int getDmg(int currLvl);    //funzione che calcola il danno dell'ostacolo, in base al livello corrente e al moltiplicatore
	int getX();
	int getY();
	void muovi();
	void setDespawn(bool d);
};
#endif