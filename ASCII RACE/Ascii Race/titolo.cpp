#include "titolo.hpp"
#include "strada.hpp"
#include <stdbool.h>
#include <Windows.h>
#include <conio.h>
#include <iostream>
using namespace std;

titolo::titolo() {}

void titolo::stampaTitolo() {
	HANDLE hconsole;                                    //stampa la schermata del titolo
	hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "            _____  _____ _____ _____      _____            _____ ______ \n";
	Sleep(200);
	cout << "     /\\    / ____|/ ____|_   _|_   _|    |  __ \\     /\\   / ____|  ____| \n";
	Sleep(200);
	cout << "    /  \\  | (___ | |      | |   | |      | |__) |   /  \\ | |    | |__   \n";
	Sleep(200);
	cout << "   / /\\ \\  \\___ \\| |      | |   | |      |  _  /   / /\\ \\| |    |  __|   \n";
	Sleep(200);
	cout << "  / ____ \\ ____) | |____ _| |_ _| |_     | | \\ \\  / ____ \\ |____| |____  \n";
	Sleep(200);
	cout << " /_/    \\_\\_____/ \\_____|_____|_____|    |_|  \\_\\/_/    \\_\\_____|______| \n";
	cout << "                                           \n";
	cout << "                                           \n";

	cout << "Premere un tasto per continuare\n";
	while (!_kbhit()) {}     //attende che venga premuto un tasto 
	char m = _getch();
}

int titolo::difficulty() {   //mostra il menù della difficoltà e permette di effettuare la selezione
	system("CLS");
	ShowConsoleCursor(false);   //nasconde il cursore dalla console
	HANDLE hconsole;
	hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char m;
	int scelta = 0;
	bool ready = false;   //diventa true quando il giocatore effettua la selezione       

	gotoxy(5, 1);                 //stampa il menù della difficoltà
	cout << "Scelgi la difficolta' ";
	gotoxy(5, 5);
	SetConsoleTextAttribute(hconsole, 2);
	cout << "Facile";
	SetConsoleTextAttribute(hconsole, 15);
	gotoxy(5, 7);
	cout << "Medio";
	gotoxy(5, 9);
	cout << "Difficile";
	while (!ready) {
		if (_kbhit()) {   //il giocatore preme un tasto da tastiera:
			m = _getch();
			if (m == 's' || m == 'S' || m == 80) {   //muove il cursore in basso 
				scelta++;
				scelta %= 3;
			}
			else if (m == 'w' || m == 'W' || m == 72) {  //muove il cursore in alto
				if (scelta != 0) scelta--;
				else scelta = 2;
			}
			else if (m == 13 || m == 32) {   //selezione effettuata:
				ready = true;                //esce dal while ed effettua il return della difficoltà selezionata
			}
			switch (scelta)
			{
			case 0:
				gotoxy(5, 5);   //il cursore è posizionato su "Facile", che si evidenzia in verde
				SetConsoleTextAttribute(hconsole, 2);
				cout << "Facile";
				SetConsoleTextAttribute(hconsole, 15);
				gotoxy(5, 7);
				cout << "Medio";
				gotoxy(5, 9);
				cout << "Difficile";
				break;
			case 1:
				gotoxy(5, 7);    //il cursore è posizionato su "Medio", che si evidenzia in verde
				SetConsoleTextAttribute(hconsole, 2);
				cout << "Medio";
				gotoxy(5, 5);
				SetConsoleTextAttribute(hconsole, 15);
				cout << "Facile";
				gotoxy(5, 9);
				cout << "Difficile";
				break;
			case 2:
				gotoxy(5, 9);    //il cursore è posizionato su "Difficile", che si evidenzia in verde
				SetConsoleTextAttribute(hconsole, 2);
				cout << "Difficile";
				gotoxy(5, 5);
				SetConsoleTextAttribute(hconsole, 15);
				cout << "Facile";
				gotoxy(5, 7);
				cout << "Medio";
				break;
			}
		}
	}
	return scelta;  //ritorna il livello di difficoltà selezionato dal giocatore
}