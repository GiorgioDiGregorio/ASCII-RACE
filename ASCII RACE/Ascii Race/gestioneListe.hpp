#ifndef GESTIONELISTE_H
#define GESTIONELISTE_H
#include <stdbool.h>
#include "tronco.hpp"
#include "chiodo.hpp"
#include "buco.hpp"
#include "enemy.hpp"
#include "strada.hpp"
#include "car.hpp"
#include "bloccoPunti.hpp"
#include "scudo.hpp"
#include "raddoppia.hpp"

#define MAX_FLASHES 6

struct listaTronco {
	tronco t;
	listaTronco* next;
};

struct listaChiodo {
	chiodo c;
	listaChiodo* next;
};

struct listaBuco {
	buco b;
	listaBuco* next;
};

struct listaEnemy {
	enemy e;
	listaEnemy* next;
};

struct listaPunti {
	bloccoPunti p;
	listaPunti* next;
};

listaTronco* addTronco(listaTronco* head, int x, int diff);
listaChiodo* addChiodo(listaChiodo* head, int x, int diff);
listaBuco* addBuco(listaBuco* head, int x, int diff);
listaEnemy* addEnemy(listaEnemy* head, int x, int diff);
listaPunti* addPunti(listaPunti* head, int x, int diff);

bool checkTronco(strada s, int x);
void printTronco(strada& s, listaTronco* head);
void muoviTronco(listaTronco* head);
void checkCollisionTronco(listaTronco* head, int x, int y, int *punteggio, int lvl, int* flashes, bool shield);
listaTronco* manageTronco(listaTronco* head, int& numO);

bool checkBuco(strada s, int x);
void printBuco(strada& s, listaBuco* head);
void muoviBuco(listaBuco* head);
void checkCollisionBuco(listaBuco* head, int x, int y, int* punteggio, int lvl, int* flashes, bool shield);
listaBuco* manageBuco(listaBuco* head, int& numO);

bool checkChiodo(strada s, int x);
void printChiodo(strada& s, listaChiodo* head);
void muoviChiodo(listaChiodo* head);
void checkCollisionChiodo(listaChiodo* head, int x, int y, int* punteggio, int lvl, int* flashes, bool shield);
listaChiodo* manageChiodo(listaChiodo* head, int& numO);

bool checkEnemy(strada s, int x);
void printEnemy(strada& s, listaEnemy* head);
void muoviEnemy(listaEnemy* head);
void checkCollisionEnemy(listaEnemy* head, int x, int y, int* punteggio, int lvl, int* flashes, bool shield);
listaEnemy* manageEnemy(listaEnemy* head, int& numO);

bool checkPunti(strada s, int x);
void printPunti(strada& s, listaPunti* head);
void muoviPunti(listaPunti* head);
void checkCollisionPunti(listaPunti* head, int x, int y, int* punteggio, int lvl, int* flashes, bool isDouble);
listaPunti* managePunti(listaPunti* head, int& numO);

bool checkDouble(strada s, int x);

bool checkScudo(strada s, int x);
#endif