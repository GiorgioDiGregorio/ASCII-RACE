#include "funzioni.hpp"
#include <Windows.h>

//Funzione per muovere il cursore sul terminale
void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Funzione per rendere il cursore "invisibile" sul terminale
void ShowConsoleCursor(bool Show)
{
	int Size = 25;
	//The Size = the cursor height, by default 25. Size range: 1 - 100
	_CONSOLE_CURSOR_INFO CurInfo; //Define the cursor size

	if (Size <= 0)
		Size = 1;
	if (Size > 100)
		Size = 100;

	CurInfo.dwSize = Size; //Define the visibility of the cursor
	CurInfo.bVisible = Show;

	//Set parameters
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}