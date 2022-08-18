#ifndef ENEMY_H
#define ENEMY_H
#include "ostacoli.hpp"
class enemy : public ostacoli {
private:
	char symb;
public:
	enemy();
	enemy(int x, int y, int dmg, int mul, char sy);
	void stampaSuStrada(strada& s);
	void scrivi(strada& s, int y, int x);
	bool getDespawn();
	bool checkCollision(int x, int y);
};
#endif