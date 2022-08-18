#ifndef STRADA_H
#define STRADA_H
#include <iostream>
#include "funzioni.hpp"
class strada {
private:
	static const int width = 45;
	static const int heigth = 29;

public:
	char mappa[heigth][width];  //y,x
	strada();
	void stampa(bool isShield);
	int getW();
	int getH();
	void clean();
};
#endif