#ifndef BLOCCOPUNTI_H
#define BLOCCOPUNTI_H
#include "ostacoli.hpp"

class bloccoPunti : public ostacoli {
private:
	char symb1;
	char symb2;
public:
	bloccoPunti();
	bloccoPunti(int x, int y, int dmg, int mul, char sy1, char sy2);
	void stampaSuStrada(strada& s);
	bool getDespawn();
	bool checkCollision(int x, int y);
	void scrivi(strada& s, int y, int x, char smb);
};
#endif
