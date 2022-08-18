#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <ctime>
#include "car.hpp"
#include "strada.hpp"
#include "funzioni.hpp"
#include "tronco.hpp"
#include "buco.hpp"
#include "chiodo.hpp"
#include "enemy.hpp"
#include "bloccoPunti.hpp"
#include "scudo.hpp"
#include "raddoppia.hpp"
#include "gestioneListe.hpp"
#define durataScudo 50
#define durataDoppia 100
#define addTick 20
using namespace std;


class gameManager {
	private:
		int diff, gameTick, punteggio, maxPunti, livello, flashes, scudStart, doubleStart;
		int maxOstacoli, numOstacoli;
		strada street;
		car user;
		bool quit, pause, isShield, isDouble;
		listaTronco* headTronco;
		listaChiodo* headChiodo;
		listaBuco* headBuco;
		listaEnemy* headEnemy;
		listaPunti* headPunti;
		scudo scud;
		raddoppia doub;
	public:
		gameManager();
		gameManager(int d);
		void muoviUser();
		void start();
		void preGame();
		void setSpawn();
		void fuoriStrada(int* f, int* p, car& user, bool dx);
		bool restart();
		void pausa();
};
#endif