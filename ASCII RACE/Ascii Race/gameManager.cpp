#include "gameManager.hpp"
using namespace std;

gameManager::gameManager() {}

/*
	costruttore classe, scudo e double non sono gestiti attraverso liste perchè essendo bonus non compaiono duplicati sulla mappa.
	si parte da 100 punti e dal livello 1. flashes viene usata quando la macchina colpisce un ostacolo, per mostrare la collisione
	il numero massimo di ostacoli dipende dalla difficoltà
*/
gameManager::gameManager(int d) {
	diff = d;
	flashes = 0;
	maxOstacoli = 5 * (d + 1);
	numOstacoli = 0;
	punteggio = maxPunti = 100;
	scudStart = doubleStart = 0;
	livello = 1;
	street = strada();
	user = car(street.getW() / 2, street.getH() - 3, '@');
	quit = pause = isShield = isDouble = false;
	gameTick = 0;
	headTronco = NULL;
	headChiodo = NULL;
	headBuco = NULL;
	headEnemy = NULL;
	headPunti = NULL;
	scud = scudo(0, -1, 0, 0, '/', '\\');
	doub = raddoppia(0, -1, 0, 0, 'X', '2');
}

/*
	la funzione principale della classe. Gestisce il gioco alternando fasi di controllo input/controllo collisioni/stampa della strada
*/
void gameManager::start() {
	srand(time(NULL));
	char m = 32;
	system("CLS");
	preGame();
	user.scriviSuStrada(street);
	street.stampa(isShield);

	while (punteggio>0 && !quit) {
		
		//controlli su presenza di bonus quali scudo e double
		if (isShield && scudStart == gameTick - durataScudo) {
			scud.setSpawned(false);
			isShield = false;
		}
		if (isShield && durataScudo - (gameTick - scudStart) == MAX_FLASHES)
			flashes = MAX_FLASHES;

		if (isDouble && doubleStart == gameTick - durataDoppia) {
			doub.setSpawned(false);
			isDouble = false;
		}

		gameTick++;
		
		//ogni 150 refresh, viene aggiunta una quantità di punteggio pari a "addTick"
		if (gameTick % 150 == 0) punteggio += addTick;
		if (punteggio > maxPunti) maxPunti = punteggio;
		
		//refresh del punteggio e del livello
		if(punteggio>100)	livello = punteggio / 100;
		
		//ogni 5 livelli, viene aggiunto un ostacolo in più al maxOstacoli
		if(livello % 5 == 0) maxOstacoli = (5 * (diff+ 1) + (livello / 5));
		
		//ogni 4 refresh, viene fatto spawnare un nuovo ostacolo se possibile
		if(gameTick % 4 == 0)
			setSpawn();

		//flash auto se collisione rilevata o scudo in fine
		if (flashes > 0) flashes--;
		if (flashes % 2 != 0) user.setSymb(' ');
		else user.setSymb('@');

		//apertura menù pausa
		if (pause) pausa();
			
		//Aggiornamento posizione degli ostacoli e dell'utente
		muoviUser();
		if (scud.getSpawned())
			scud.muovi();
		if (doub.getSpawned())
			doub.muovi();
		muoviTronco(headTronco);
		muoviBuco(headBuco);
		muoviChiodo(headChiodo);
		muoviEnemy(headEnemy);
		muoviPunti(headPunti);

		//funzioni per rilevare la collisione con i vari ostacoli (tutti ad eccezione di scud e doub sono gestiti attraverso delle liste)
		if (scud.getSpawned())
			isShield = scud.checkCollision(user.getPosX(), user.getPosY());
		if (doub.getSpawned())
			isDouble = doub.checkCollision(user.getPosX(), user.getPosY());
		checkCollisionTronco(headTronco, user.getPosX(), user.getPosY(), &punteggio, livello, &flashes, isShield);
		checkCollisionBuco(headBuco, user.getPosX(), user.getPosY(), &punteggio, livello, &flashes, isShield);
		checkCollisionChiodo(headChiodo, user.getPosX(), user.getPosY(), &punteggio, livello, &flashes, isShield);
		checkCollisionEnemy(headEnemy, user.getPosX(), user.getPosY(), &punteggio, livello, &flashes, isShield);
		checkCollisionPunti(headPunti, user.getPosX(), user.getPosY(), &punteggio, livello, &flashes, isDouble);

		//Funzioni per elimnare dalla lista eventuali oggetti che hanno colliso
		headTronco = manageTronco(headTronco, numOstacoli);
		headBuco = manageBuco(headBuco, numOstacoli);
		headChiodo = manageChiodo(headChiodo, numOstacoli);
		headEnemy = manageEnemy(headEnemy, numOstacoli);
		headPunti = managePunti(headPunti, numOstacoli);

		//refresh stampa (cancella tutto ciò che è sulla matrice e ricopia tutto con le posizioni aggiornate, dopo stampa a video)
		street.clean();
		user.scriviSuStrada(street);
		printTronco(street, headTronco);
		printBuco(street, headBuco);
		printChiodo(street, headChiodo);
		printEnemy(street, headEnemy);
		printPunti(street, headPunti);
		if (scud.getSpawned())
			scud.stampaSuStrada(street);
		if (doub.getSpawned())
			doub.stampaSuStrada(street);
		street.stampa(isShield);

		//paramtri aggiuntivi visualizzati quali difficoltà, punteggio, livello ed eventuale presenza di scudo o double
		gotoxy(street.getW() + 1, 3);
		cout << "Difficolta': ";  (diff == 0) ? cout << "Facile" : diff == 1 ? cout << "Medio" : cout << "Difficile";
		gotoxy(street.getW() + 1, 4);
		cout << "Punteggio: " << punteggio << "   ";
		gotoxy(street.getW() + 1, 5);
		cout << "Livello: " << livello << "   ";
		gotoxy(street.getW() + 1, 6);
		if (isShield)	cout << "Shield: " << durataScudo - (gameTick - scudStart) << "      " ;
		else cout << "                                          ";
		gotoxy(street.getW() + 1, 7);
		if (isDouble)	cout << "Double: "<< durataDoppia - (gameTick - doubleStart) << "         ";
		else cout << "                                          ";
	}
	//fine del gioco
	system("cls");                         
	gotoxy(10, 10);
	cout << "GAME OVER";
	gotoxy(10, 11);
	cout<<"Highscore: " << maxPunti;
	Sleep(1000);
	gotoxy(10, 20);
}

void gameManager::muoviUser() {
	//funzione per gestire l'input da tastiera
	//prevede il movimento tramite "WASD", "wasd", "frecce", e un tasto "P" o "p" per aprire il menù di pausa
	char m;
	if (_kbhit()) {
		m = _getch();
		if (m == 's' || m == 'S' || m == 80) user.getPosY() < street.getH() - 3 ? user.muovi(DOWN) : user.muovi(STOP);
		else if (m == 'w' || m == 'W' || m == 72) user.getPosY() > 3 ? user.muovi(UP) : user.muovi(STOP);
		else if (m == 'a' || m == 'A' || m == 75) user.getPosX() > 3 ? user.muovi(LEFT) : !isShield ? fuoriStrada(&flashes, &punteggio, user, true) : user.muovi(RIGHT);
		else if (m == 'd' || m == 'D' || m == 77) user.getPosX() < street.getW() - 3 ? user.muovi(RIGHT) : !isShield ? fuoriStrada(&flashes, &punteggio, user, false) : user.muovi(LEFT);
		else if (m == 'p' || m == 'P' || m==27) pause = true;
		else user.muovi(STOP);
	}
}

//conto alla rovescia prima di cominciare il gioco o prima di rientrare dalla pausa
void gameManager::preGame() {
	ShowConsoleCursor(false);
	HANDLE hconsole;
	hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hconsole, 2);
	gotoxy(street.getW() / 2, street.getH() / 2);
	cout << "3";
	Sleep(1000);
	gotoxy(street.getW() / 2, street.getH() / 2);
	SetConsoleTextAttribute(hconsole, 15);
	cout << "2";
	Sleep(1000);
	gotoxy(street.getW() / 2, street.getH() / 2);
	SetConsoleTextAttribute(hconsole, 2);
	cout << "1";
	Sleep(1000);
	gotoxy(street.getW() / 2, street.getH() / 2);
	SetConsoleTextAttribute(hconsole, 15);
	cout << "START";
	Sleep(1000);
}

/*
	funzione per gestire lo spawn
	viene effettuato attraverso la generazioe di un numero casuale € [0,15]
	in base all'ostacolo, ci sono varie frequenze di spawn
*/
void gameManager::setSpawn() {
	int i = rand() % 16;
	int x;
	switch (i)
	{
		//3/16 spawna un Tronco
		case 0:
		case 7:
		case 14:
			x = rand() % (street.getW() - 5) + 1;
			//controllo per verificare che le coordinate scelte non siano già occupate da altri ostacoli
			if (checkTronco(street, x) && numOstacoli < maxOstacoli) {
				numOstacoli++;
				headTronco = addTronco(headTronco, x,diff);
			}
			break;
		//2/16 spawna una macchina nemica
		case 1:
		case 8:
			x = rand() % (street.getW() - 4) + 1;
			//controllo per verificare che le coordinate scelte non siano già occupate da altri ostacoli
			if (checkEnemy(street, x) && numOstacoli < maxOstacoli) {
				numOstacoli++;
				headEnemy = addEnemy(headEnemy, x, diff);
			}
			break;
		//3/16 spawna un buco
		case 2:
		case 9:
		case 12:
			x = rand() % (street.getW() - 4) + 1;
			//controllo per verificare che le coordinate scelte non siano già occupate da altri ostacoli
			if (checkBuco(street, x) && numOstacoli < maxOstacoli) {
				numOstacoli++;
				headBuco = addBuco(headBuco, x, diff);
			}
			break;
		//2/16 spawna un blocco Punti
		case 3:
		case 10:
			x = rand() % (street.getW() - 4) + 1;
			//controllo per verificare che le coordinate scelte non siano già occupate da altri ostacoli
			if (checkPunti(street, x) && numOstacoli < maxOstacoli) {
				numOstacoli++;
				headPunti = addPunti(headPunti, x, diff);
			}
			break;
		//3/16 spawna un chiodo	
		case 4:
		case 11:
		case 15:
			x = rand() % (street.getW() - 3) + 1;
			//controllo per verificare che le coordinate scelte non siano già occupate da altri ostacoli
			if (checkChiodo(street, x) && numOstacoli < maxOstacoli) {
				numOstacoli++;
				headChiodo = addChiodo(headChiodo, x, diff);
			}
			break;
		//1/16 spawna il raddoppia
		case 5:
			//RADDOPPIA
			x = rand() % (street.getW() - 3) + 1;
			//controllo per verificare che le coordinate scelte non siano già occupate da altri ostacoli
			if (checkDouble(street, x) && doub.getSpawned() == false && !isDouble) {
				doub.setSpawned(true);
				doub.setPosX(x);
				doub.setPosY(-1);
				doubleStart = gameTick;
			}
			break;
		//1/16 spawna lo scudo
		case 6:
			//SCUDO
			x = rand() % (street.getW() - 3) + 1;
			//controllo per verificare che le coordinate scelte non siano già occupate da altri ostacoli
			if (checkScudo(street, x) && scud.getSpawned() == false && !isShield) {
				scud.setSpawned(true);
				scud.setPosX(x);
				scud.setPosY(-1);
				scudStart = gameTick;
			}
			break;
		}
}

//funzione per gestire il movimento a ridosso della strada, vengono sottratti i punti e viene fatta lampeggiare la macchina, spostandola verso il centro della strda
void gameManager::fuoriStrada(int* f, int* p, car& user, bool dx) {
	*f = MAX_FLASHES;
	*p = *p - 50 * diff;
	if (dx) user.muovi(RIGHT);
	else user.muovi(LEFT);
}

//funzione per gestire il restart con possibilità di abbandonare il gioco o di ricominciare la partita
bool gameManager::restart() {
	system("cls");
	bool ready = false;
	char m;
	int scelta = 0;
	ShowConsoleCursor(false);
	HANDLE hconsole;
	hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "__   __            _                     " << endl;
	cout << "\\ \\ / /           | |                    " << endl;
	cout << " \\ V /___  _   _  | |     ___  ___  ___  " << endl;
	cout << "  \\ // _ \\| | | | | |    / _ \\/ __|/ _ \\ " << endl;
	cout << "  | | (_) | |_| | | |___| (_) \\__ \\  __/ " << endl;
	cout << "  \\_/\\___/ \\__,_| \\_____/\\___/|___/\\___| " << endl;
	cout << "                                         " << endl;
	gotoxy(5, 8);
	SetConsoleTextAttribute(hconsole, 2);
	cout << "  Esci  ";
	SetConsoleTextAttribute(hconsole, 15);
	gotoxy(5, 10);
	cout << "  Ricomincia  ";
	while (!ready) {
		if (_kbhit()) {
			m = _getch();
			if (m == 's' || m == 'S' || m == 80) {
				scelta++;
				scelta %= 2;
			}
			else if (m == 'w' || m == 'W' || m == 72) {
				if (scelta != 0) scelta--;
				else scelta = 1;
			}
			else if (m == 13 || m == 32) {
				ready = true;
			}
			switch (scelta)
			{
			case 0:
				gotoxy(5, 8);
				SetConsoleTextAttribute(hconsole, 2);
				cout << "  Esci  ";
				SetConsoleTextAttribute(hconsole, 15);
				gotoxy(5, 10);
				cout << "  Ricomincia  ";
				break;
			case 1:
				gotoxy(5, 10);
				SetConsoleTextAttribute(hconsole, 2);
				cout << "  Ricomincia  ";
				gotoxy(5, 8);
				SetConsoleTextAttribute(hconsole, 15);
				cout << "  Esci  ";
				break;
			}
		}
	}
	if (scelta == 0) return false;  //esci
	else return true;
}

//funzione per gestire la pausa, con possibilità di uscire dal gioco o riprendere la partita
void gameManager::pausa() {
	bool ready = false;
	char m;
	int scelta = 0;
	ShowConsoleCursor(false);
	HANDLE hconsole;
	hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(street.getW() / 2 - 4, street.getH() / 2);
	SetConsoleTextAttribute(hconsole, 2);
	cout << "  Esci  ";
	SetConsoleTextAttribute(hconsole, 15);
	gotoxy(street.getW() / 2 - 4, street.getH() / 2 + 2);
	cout << "  Riprendi  ";
	while (!ready) {
		if (_kbhit()) {
			m = _getch();
			if (m == 's' || m == 'S' || m == 80) {
				scelta++;
				scelta %= 2;
			}
			else if (m == 'w' || m == 'W' || m == 72) {
				if (scelta != 0) scelta--;
				else scelta = 1;
			}
			else if (m == 13 || m == 32 || m == 'p' || m == 'P' || m==27) {
				if (m == 'p' || m == 'P' || m==27)
					scelta = 1;
				ready = true;
			}
			switch (scelta)
			{
			case 0:
				gotoxy(street.getW() / 2 - 4, street.getH() / 2);
				SetConsoleTextAttribute(hconsole, 2);
				cout << "  Esci  ";
				SetConsoleTextAttribute(hconsole, 15);
				gotoxy(street.getW() / 2 - 4, street.getH() / 2 + 2);
				cout << "  Riprendi  ";
				break;
			case 1:
				gotoxy(street.getW() / 2 - 4, street.getH() / 2 + 2);
				SetConsoleTextAttribute(hconsole, 2);
				cout << "  Riprendi  ";
				gotoxy(street.getW() / 2 - 4, street.getH() / 2);
				SetConsoleTextAttribute(hconsole, 15);
				cout << "  Esci  ";
				break;
			}
		}
	}
	if (scelta == 0) quit = true;
	else {
		gotoxy(street.getW() / 2 - 4, street.getH() / 2 );
		cout << "          ";
		gotoxy(street.getW() / 2 - 4, street.getH() / 2 + 2);
		cout << "          ";
		pause = false;
		preGame();
	}
}