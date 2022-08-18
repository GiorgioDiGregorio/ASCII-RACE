#ifndef SCUDO_H
#define SCUDO_H
#include "ostacoli.hpp"

class scudo : public ostacoli {
private:
	char symb1;
	char symb2;
	bool isSpawned;
public:
	scudo();
	scudo(int x, int y, int dmg, int mul, char sy1, char sy2);
	void stampaSuStrada(strada& s);
	bool getSpawned();
	bool checkCollision(int x, int y);
	void scrivi(strada & s, int y, int x, char smb); 
	void setPosX(int x);
	void setPosY(int y);
	void setSpawned(bool s);
};
#endif
