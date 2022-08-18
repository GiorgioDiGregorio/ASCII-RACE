#ifndef TRONCO_H
#define TRONCO_H
#include "ostacoli.hpp"
class tronco : public ostacoli {
	private:
		char symb;
	public:
		tronco();
		tronco(int x, int y, int dmg, int mul, char sy);
		void stampaSuStrada(strada& s);
		void scrivi(strada& s, int x, int y);
		bool getDespawn();
		bool checkCollision(int x, int y);
};
#endif