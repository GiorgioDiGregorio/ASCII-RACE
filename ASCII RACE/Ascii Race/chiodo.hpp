#ifndef CHIODO_H
#define CHIODO_H
#include "ostacoli.hpp"
class chiodo : public ostacoli {
private:
	char symb;
public:
	chiodo();
	chiodo(int x, int y, int dmg, int mul, char sy);
	void stampaSuStrada(strada& s);
	void scrivi(strada& s, int y, int x);
	bool getDespawn();
	bool checkCollision(int x, int y);
};
#endif
