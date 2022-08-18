#include "strada.hpp"
using namespace std;

//costruttore: riempie la strada di '?' che verranno rimpiazzati dagli ostacoli e dall'utente
strada::strada() {
	for (int i = 0; i < heigth; i++) {
		for (int j = 0; j < width; j++) {
			mappa[i][j] = '?';
		}
	}
}

//Funzione per pulire la strada prima di stampare nuovamente ostacoli e auto utente
void strada::clean() {
	for (int i = 0; i < heigth; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1) mappa[i][j]='|';
			else mappa[i][j] = '?';
		}
	}
}

//Stampa a video della strada
void strada::stampa(bool isShield) {
	HANDLE hconsole;
	hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < heigth; i++) {
		for (int j = 0; j < width; j++) {
			gotoxy(j, i);
			//non sono presenti elementi in questo punto della strada
			if (mappa[i][j] == '?') {
				SetConsoleTextAttribute(hconsole, 15);
				cout << ' ';
			}
			else {
				//in base all'elemento, viene stampato a video con un colore diverso
				if (mappa[i][j] == '^') SetConsoleTextAttribute(hconsole, 12);
				else if (mappa[i][j] == '=') SetConsoleTextAttribute(hconsole, 12);
				else if (mappa[i][j] == '#') SetConsoleTextAttribute(hconsole, 12);
				else if (mappa[i][j] == 'O') SetConsoleTextAttribute(hconsole, 12);
				else if (mappa[i][j] == 'x') SetConsoleTextAttribute(hconsole, 12);
				else if (mappa[i][j] == 'X') SetConsoleTextAttribute(hconsole, 2);
				else if (mappa[i][j] == '2') SetConsoleTextAttribute(hconsole, 2);
				else if (mappa[i][j] == 'P') SetConsoleTextAttribute(hconsole, 2);
				else if (mappa[i][j] == '+') SetConsoleTextAttribute(hconsole, 2);
				else if (mappa[i][j] == '\\') SetConsoleTextAttribute(hconsole, 2);
				else if (mappa[i][j] == '/') SetConsoleTextAttribute(hconsole, 2);
				else if (mappa[i][j] == '@') {
					//se è attivo lo scudo la macchina utente viene stampata in blu, altrimenti in bianco
					if(isShield)
						SetConsoleTextAttribute(hconsole, 9);
					else
						SetConsoleTextAttribute(hconsole, 15);
				}
				else if(mappa[i][j] == '|') SetConsoleTextAttribute(hconsole, 15);
				cout << mappa[i][j];
			}
		}
	}
}

//getter vari
int strada::getH() { return heigth; }
int strada::getW() { return width; }
