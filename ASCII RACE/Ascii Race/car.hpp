#ifndef CAR_H
#define CAR_H
#include "strada.hpp"
#define mov 4
using namespace std;

enum eDir { STOP = 0, UP = 1, RIGHT = 2, DOWN = 3, LEFT = 4 };

class car {
protected:
    int posX;
    int posY;
    char symb;
public:
    car();
    car(int posx, int posy, char sy);
    int getPosX();
    int getPosY();
    void muovi(eDir direction);
    void scriviSuStrada(strada &s);
    void setSymb(char s);
};
#endif