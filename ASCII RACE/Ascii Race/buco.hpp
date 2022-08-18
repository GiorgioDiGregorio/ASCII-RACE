#ifndef BUCO_H
#define BUCO_H
#include "ostacoli.hpp"
class buco : public ostacoli {
private:
	char symb;
public:
	buco();
	buco(int x, int y, int dmg, int mul, char sy);
	void stampaSuStrada(strada& s);
	bool getDespawn();
	bool checkCollision(int x, int y);
	void scrivi(strada& s, int y, int x);
};
#endif