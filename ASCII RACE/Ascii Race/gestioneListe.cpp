#include "gestioneListe.hpp"

//SEZIONE TRONCO
//date le coordinate e la strada, controlla se è possibile far spawnare un oggetto in quelle coordinate
bool checkTronco(strada s, int x){
	if (s.mappa[0][x] == '?' && s.mappa[0][x + 1] == '?' && s.mappa[0][x + 2] == '?' && s.mappa[0][x + 3] == '?') return true;
	else return false;
}

//funzione per aggiungere un elemento alla lista passando la coordinata x e la difficoltà del gioco
listaTronco* addTronco(listaTronco* head, int x, int diff) {
	if (head == NULL) {
		head = new listaTronco;
		head->t = tronco(x, -1, (diff + 1) * 20, (diff+1)*10, '=');
		head->next = NULL;
		return head;
	}
	else {
		head->next = addTronco(head->next, x,diff);
		return head;
	}
}

//Scorre la lista e chiama per ogni elemento il metodo muovi per incrementare la posizione in Y
void muoviTronco(listaTronco* head) {
	listaTronco* tmp = head;
	while (tmp != NULL) {
		tmp->t.muovi();
		tmp = tmp->next;
	}
}

//Scorre la lista e stampa nella matrice della strada l'elemento
void printTronco(strada& s, listaTronco* head) {
	listaTronco* tmp = head;
	while (tmp != NULL) {
		tmp->t.stampaSuStrada(s);
		tmp = tmp->next;
	}
}

//Scorre tutta la lista e controlla quali elementi sono da eliminare perchè hanno colliso o sono usciti fuori dalla mappa (Ricorsivamente)
listaTronco* manageTronco(listaTronco* head, int& numO) {
	if (head == NULL)	return NULL;
	else {
		if (head->t.getDespawn()) {
			numO = numO - 1;
			return manageTronco(head->next, numO);
		}
		else {
			head->next = manageTronco(head->next, numO);
			return head;
		}
	}
}

//Scorre la lista intera e controlla eventuali collisioni (In input Coordinate della macchina utente, puntatore al punteggio, livello, puntatore a flashes e la presenza o meno dello scudo
void checkCollisionTronco(listaTronco* head, int x, int y, int *punteggio, int lvl, int *flashes, bool shield) {
	listaTronco* tmp = head;
	while (tmp != NULL) {
		if (tmp->t.checkCollision(x, y)) {
			tmp->t.setDespawn(true);
			if (shield == false) {
				*punteggio -= tmp->t.getDmg(lvl);
				*flashes = MAX_FLASHES;
			}
		}
		tmp = tmp->next;
	}
}


	//SEZIONE BUCO
//date le coordinate e la strada, controlla se è possibile far spawnare un oggetto in quelle coordinate
bool checkBuco(strada s, int x) {
	if (s.mappa[0][x] == '?' && s.mappa[0][x + 1] == '?' && s.mappa[0][x + 2] == '?' /*&& s.mappa[0][x + 3] == '?'*/) return true;
	else return false;
}

//funzione per aggiungere un elemento alla lista passando la coordinata x e la difficoltà del gioco
listaBuco* addBuco(listaBuco* head, int x, int diff) {
	if (head == NULL) {
		head = new listaBuco;
		head->b = buco(x, -1, (diff + 1) * 30, (diff + 1) * 15, 'O');
		head->next = NULL;
		return head;
	}
	else {
		head->next = addBuco(head->next, x, diff);
		return head;
	}
}

//Scorre la lista e chiama per ogni elemento il metodo muovi per incrementare la posizione in Y
void muoviBuco(listaBuco* head) {
	listaBuco* tmp = head;
	while (tmp != NULL) {
		tmp->b.muovi();
		tmp = tmp->next;
	}
}

//Scorre la lista e stampa nella matrice della strada l'elemento
void printBuco(strada& s, listaBuco* head) {
	listaBuco* tmp = head;
	while (tmp != NULL) {
		tmp->b.stampaSuStrada(s);
		tmp = tmp->next;
	}
}

//Scorre tutta la lista e controlla quali elementi sono da eliminare perchè hanno colliso o sono usciti fuori dalla mappa (Ricorsivamente)
listaBuco* manageBuco(listaBuco* head, int& numO) {
	if (head == NULL)	return NULL;
	else {
		if (head->b.getDespawn()) {
			numO = numO - 1;
			return manageBuco(head->next, numO);
		}
		else {
			head->next = manageBuco(head->next, numO);
			return head;
		}
	}
}

//Scorre la lista intera e controlla eventuali collisioni (In input Coordinate della macchina utente, puntatore al punteggio, livello, puntatore a flashes e la presenza o meno dello scudo
void checkCollisionBuco(listaBuco* head, int x, int y, int* punteggio, int lvl, int* flashes, bool shield) {
	listaBuco* tmp = head;
	while (tmp != NULL) {
		if (tmp->b.checkCollision(x, y)) {
			tmp->b.setDespawn(true);
			if (shield == false) {
				*punteggio -= tmp->b.getDmg(lvl);
				*flashes = MAX_FLASHES;
			}
		}
		tmp = tmp->next;
	}
}

	//SEZIONE CHIODO
//date le coordinate e la strada, controlla se è possibile far spawnare un oggetto in quelle coordinate
bool checkChiodo(strada s, int x) {
	if (s.mappa[0][x] == '?' && s.mappa[0][x + 1] == '?' /* && s.mappa[0][x + 2] == '?' && s.mappa[0][x + 3] == '?'*/) return true;
	else return false;
}

//funzione per aggiungere un elemento alla lista passando la coordinata x e la difficoltà del gioco
listaChiodo* addChiodo(listaChiodo* head, int x, int diff) {
	if (head == NULL) {
		head = new listaChiodo;
		head->c = chiodo(x, -1, (diff + 1) * 15, (diff + 1) * 10, 'x');
		head->next = NULL;
		return head;
	}
	else {
		head->next = addChiodo(head->next, x, diff);
		return head;
	}
}

//Scorre la lista e chiama per ogni elemento il metodo muovi per incrementare la posizione in Y
void muoviChiodo(listaChiodo* head) {
	listaChiodo* tmp = head;
	while (tmp != NULL) {
		tmp->c.muovi();
		tmp = tmp->next;
	}
}

//Scorre la lista e stampa nella matrice della strada l'elemento
void printChiodo(strada& s, listaChiodo* head) {
	listaChiodo* tmp = head;
	while (tmp != NULL) {
		tmp->c.stampaSuStrada(s);
		tmp = tmp->next;
	}
}

//Scorre tutta la lista e controlla quali elementi sono da eliminare perchè hanno colliso o sono usciti fuori dalla mappa (Ricorsivamente)
listaChiodo* manageChiodo(listaChiodo* head, int& numO) {
	if (head == NULL)	return NULL;
	else {
		if (head->c.getDespawn()) {
			numO = numO - 1;
			return manageChiodo(head->next, numO);
		}
		else {
			head->next = manageChiodo(head->next, numO);
			return head;
		}
	}
}

//Scorre la lista intera e controlla eventuali collisioni (In input Coordinate della macchina utente, puntatore al punteggio, livello, puntatore a flashes e la presenza o meno dello scudo
void checkCollisionChiodo(listaChiodo* head, int x, int y, int* punteggio, int lvl, int* flashes, bool shield) {
	listaChiodo* tmp = head;
	while (tmp != NULL) {
		if (tmp->c.checkCollision(x, y)) {
			tmp->c.setDespawn(true);
			if (shield == false) {
				*punteggio -= tmp->c.getDmg(lvl);
				*flashes = MAX_FLASHES;
			}
		}
		tmp = tmp->next;
	}
}


	//SEZIONE ENEMY
//date le coordinate e la strada, controlla se è possibile far spawnare un oggetto in quelle coordinate
bool checkEnemy(strada s, int x) {
	if (s.mappa[0][x] == '?' && s.mappa[0][x + 1] == '?' && s.mappa[0][x + 2] == '?') return true;
	else return false;
}

//funzione per aggiungere un elemento alla lista passando la coordinata x e la difficoltà del gioco
listaEnemy* addEnemy(listaEnemy* head, int x, int diff) {
	if (head == NULL) {
		head = new listaEnemy;
		head->e = enemy(x, -1, (diff + 1) * 50, (diff + 1) * 20, '#');
		head->next = NULL;
		return head;
	}
	else {
		head->next = addEnemy(head->next, x, diff);
		return head;
	}
}

//Scorre la lista e chiama per ogni elemento il metodo muovi per incrementare la posizione in Y
void muoviEnemy(listaEnemy* head) {
	listaEnemy* tmp = head;
	while (tmp != NULL) {
		tmp->e.muovi();
		tmp = tmp->next;
	}
}

//Scorre la lista e stampa nella matrice della strada l'elemento
void printEnemy(strada& s, listaEnemy* head) {
	listaEnemy* tmp = head;
	while (tmp != NULL) {
		tmp->e.stampaSuStrada(s);
		tmp = tmp->next;
	}
}

//Scorre tutta la lista e controlla quali elementi sono da eliminare perchè hanno colliso o sono usciti fuori dalla mappa (Ricorsivamente)
listaEnemy* manageEnemy(listaEnemy* head, int& numO) {
	if (head == NULL)	return NULL;
	else {
		if (head->e.getDespawn()) {
			numO = numO - 1;
			return manageEnemy(head->next, numO);
		}
		else {
			head->next = manageEnemy(head->next, numO);
			return head;
		}
	}
}

//Scorre la lista intera e controlla eventuali collisioni (In input Coordinate della macchina utente, puntatore al punteggio, livello, puntatore a flashes e la presenza o meno dello scudo
void checkCollisionEnemy(listaEnemy* head, int x, int y, int* punteggio, int lvl, int* flashes, bool shield) {
	listaEnemy* tmp = head;
	while (tmp != NULL) {
		if (tmp->e.checkCollision(x, y)) {
			tmp->e.setDespawn(true);
			if (shield == false) {
				*punteggio -= tmp->e.getDmg(lvl);
				*flashes = MAX_FLASHES;
			}
		}
		tmp = tmp->next;
	}
}

	//SEZIONE BLOCCO PUNTI
//date le coordinate e la strada, controlla se è possibile far spawnare un oggetto in quelle coordinate
bool checkPunti(strada s, int x) {
	if (s.mappa[0][x] == '?' && s.mappa[0][x + 1] == '?' && s.mappa[0][x + 2] == '?' /*&& s.mappa[0][x + 3] == '?'*/) return true;
	else return false;
}

//funzione per aggiungere un elemento alla lista passando la coordinata x e la difficoltà del gioco
listaPunti* addPunti(listaPunti* head, int x, int diff) {
	if (head == NULL) {
		head = new listaPunti;
		head->p = bloccoPunti(x, -1, (diff + 1) *20, 5, 'P', '+');
		head->next = NULL;
		return head;
	}
	else {
		head->next = addPunti(head->next, x, diff);
		return head;
	}
}

//Scorre la lista e chiama per ogni elemento il metodo muovi per incrementare la posizione in Y
void muoviPunti(listaPunti* head) {
	listaPunti* tmp = head;
	while (tmp != NULL) {
		tmp->p.muovi();
		tmp = tmp->next;
	}
}

//Scorre la lista e stampa nella matrice della strada l'elemento
void printPunti(strada& s, listaPunti* head) {
	listaPunti* tmp = head;
	while (tmp != NULL) {
		tmp->p.stampaSuStrada(s);
		tmp = tmp->next;
	}
}

//Scorre tutta la lista e controlla quali elementi sono da eliminare perchè hanno colliso o sono usciti fuori dalla mappa (Ricorsivamente)
listaPunti* managePunti(listaPunti* head, int& numO) {
	if (head == NULL)	return NULL;
	else {
		if (head->p.getDespawn()) {
			numO = numO - 1;
			return managePunti(head->next, numO);
		}
		else {
			head->next = managePunti(head->next, numO);
			return head;
		}
	}
}

//Scorre la lista intera e controlla eventuali collisioni (In input Coordinate della macchina utente, puntatore al punteggio, livello, puntatore a flashes e la presenza o meno dello scudo
void checkCollisionPunti(listaPunti* head, int x, int y, int* punteggio, int lvl, int* flashes, bool isDouble) {
	listaPunti* tmp = head;
	while (tmp != NULL) {
		if (tmp->p.checkCollision(x, y)) {
			tmp->p.setDespawn(true);
			if (isDouble)
				*punteggio += 2* tmp->p.getDmg(lvl);
			else 
				*punteggio += tmp->p.getDmg(lvl);
		}
		tmp = tmp->next;
	}
}

//SEZIONE RADDOPPIA
//date le coordinate e la strada, controlla se è possibile far spawnare un oggetto in quelle coordinate
bool checkDouble(strada s, int x) {
	if (s.mappa[0][x] == '?' && s.mappa[0][x + 1] == '?')
		return true;
	else return false;
}

//SEZIONE SCUDO
//date le coordinate e la strada, controlla se è possibile far spawnare un oggetto in quelle coordinate
bool checkScudo(strada s, int x) {
	if (s.mappa[0][x] == '?' && s.mappa[0][x + 1] == '?')
		return true;
	else return false;
}
