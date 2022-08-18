                _____  _____ _____ _____      _____            _____ ______ 
	     /\    / ____|/ ____|_   _|_   _|    |  __ \     /\   / ____|  ____| 
	    /  \  | (___ | |      | |   | |      | |__) |   /  \ | |    | |__   
	   / /\ \  \___ \| |      | |   | |      |  _  /   / /\ \| |    |  __|  
	  / ____ \ ____) | |____ _| |_ _| |_     | | \ \  / ____ \ |____| |____  
	 /_/    \_\_____/ \_____|_____|_____|    |_|  \_\/_/    \_\_____|______| 

## COMANDI GIOCO:

	W, freccia in su : muovi su;
	S, freccia in giù : muovi giù;
	A, freccia a sinistra : muovi sx;
	D, freccia a destra : muovi dx;
	P, ESC : menù di pausa;
        INVIO: seleziona.

-------------------

### COMANDI MENU di selezione della DIFFICOLTA' / MENU di PAUSA:	
	
	W: sposta su
	S: sposta giù
	INVIO: conferma scelta.

--------------------

### Visualizzazioni a destra della mappa:

  - Difficoltà; 
  - Punteggio; 
  - Livello;
  - Timer del RADDOPPIA; 
  - Timer dello SCUDO.

---------------------

## Descrizione generale delle varie classi contenute nel progetto

#### Strada:

E’ la classe che rappresenta la mappa di gioco. Consiste in una matrice di caratteri avente dimensioni costanti 45*29. Contiene il costruttore, i getter, un metodo per la stampa e un metodo per pulirla.
Viene inizializzata con punti interrogativi; solo i caratteri degli oggetti effettivamente da stampare sono sostituiti al posto dei punti interrogativi, il resto è rimpiazzato con spazi vuoti. La clean riempirà nuovamente la strada di punti interrogativi.

#### Car:

E’ la classe che gestisce la macchina dell’utente; abbiamo usato un’enum per definirne i movimenti (stop, up, down, right, left).
Tiene traccia della posizione x e y della macchina, e del simbolo che la rappresenta. Implementa il costruttore, i getter, un metodo per muovere la macchina in base all’input da tastiera (si muove di 4 celle per volta per rendere i movimenti più fluidi e veloci. Questa costante è modificabile), un metodo per stampare la macchina a video e uno per modificarne il simbolo (usato per implementare il powerup “scudo”).

#### Ostacoli:

Abbiamo deciso di adottare una super-classe comune a tutti gli ostacoli, dal momento che questi presentano caratteristiche molto simili tra loro. Ogni ostacolo è individuato da una posizione x e da una posizione y, da un danno che conferisce in caso di collisione con la macchina utente (che si andrà a sottrarre al punteggio complessivo), da un valore multi (moltiplicatore del danno che varia in base al livello e alla difficoltà selezionata), e da un bool despawn, che servirà per eliminare l’ostacolo dalla lista di appartenenza. Le funzioni per la gestione della stampa e delle collisioni sono implementate nelle sottoclassi (tronco, enemy, chiodo, buco) perché ogni ostacolo ha simboli caratteristici e dimensioni diverse.

La presenza degli ostacoli nella mappa di gioco viene gestita tramite l’utilizzo di liste con puntatori, le cui funzioni sono implementate nel file chiamato gestioneListe.
In questo file sono definite le struct per rappresentare le liste di ogni ostacolo, più alcune funzioni:
-	add: aggiunge alla lista un nuovo elemento di tipo ostacolo;
-	check: controlla che l’ostacolo abbia spazio a sufficienza per spawnare nella mappa da gioco senza sovrapporsi ad altri oggetti;
-	print: stampa l’oggetto sulla mappa di gioco;
-	muovi: fa avanzare l’oggetto sulla mappa di gioco;
-	checkCollision: dopo ogni gameTick controlla l’eventuale verificarsi di collisioni avvenute tra la macchina del giocatore e un oggetto di tipo ostacolo;
-	manage: rimuove dalla lista tutti gli ostacoli che devono essere eliminati dalla lista di appartenenza (o perché sono stati “distrutti” dalla collisione o perché sono usciti dalla mappa).
GestioneListe non costruisce liste per gestire i tre powerUp scudo, raddoppia e bloccoPunti, nonostante questi siano comunque sottoclassi di ostacoli. Questa scelta deriva dal fatto che nella schermata di gioco non sarà mai presente più di un oggetto dello stesso powerUp alla volta. Scudo conferisce un breve periodo di immunità dalle collisioni (durante il quale la macchina cambia colore), raddoppia permette di raddoppiare i punti presi nell’intervallo di tempo in cui questo power up è attivo, e bloccoPunti conferisce un punteggio extra. 

#### Main:

Stampa il titolo nella schermata di partenza, poi entra in un do while che permette di selezionare la difficoltà e di avviare il gioco. La partita resterà in esecuzione fino al momento in cui verrà attivata la funzione restart. 

Titolo:

Si occupa della stampa a video del titolo e della schermata di scelta della difficoltà. Quest’ultima viene selezionata muovendo il cursore con la tastiera e premendo invio. La difficoltà viene poi passata come parametro a gameManager, la classe principale che gestisce tutto lo svolgimento del gioco.

#### Game Manager:

E’ la classe che gestisce la partita.
Tiene traccia di tutti i parametri (difficoltà, gametick, punteggio, maxPunti, flash, livello, massimo numero di ostacoli…) e di una serie di booleani utili nella risoluzione delle varie casistiche del gioco (attivazione di bonus speciali, apertura del menu di pausa, uscita dal gioco ecc…).
Definisce un puntatore a tutte le liste ostacoli, e un oggetto per ogni classe (strada, car, scudo e raddoppia).
Contiene:
-	un costruttore (imposta i parametri iniziali in base alla difficoltà);
-	start (funzione principale)  definisce un while basato su punteggio (che deve essere sempre positivo, in caso contrario l’utente avrà perso la partita) e un booleano che identifica la scelta dell’utente di abbandonare il gioco. Gestisce le seguenti fasi:

-	controlla la presenza di bonus sulla mappa quali scudo e raddoppia;
-	aumenta il contatore dei gameTick;
-	aggiorna il punteggio e il numero massimo di ostacoli (se necessario);
-	ogni 4 cicli è chiamata la funzione setspawn;
-	controlla se l’auto ha subito collisione, e nel caso avvia il timer della variabile flashes (la macchina lampeggia);
-	controlla l’eventuale decisione dell’utente di mettere in pausa il gioco;
-	aggiorna le posizioni di ostacoli e utente in base all’input da tastiera;
-	chiama le funzioni per rilevare le collisioni su tutti gli ostacoli;
-	chiama le funzioni per rimuovere gli ostacoli che hanno colliso o che sono usciti fuori dalla mappa;
-	pulisce la strada e stampa a video tutti i parametri aggiuntivi del gioco;
-	fine del gioco (game over o abbandono) visulizza il punteggio massimo e avvia funzione restart.

-	preGame effettua il conto alla rovescia prima di iniziare una partita o prima di rientrare dal menu di pausa;
-	restart permette di abbandonare il gioco o di cominciare una nuova partita, dando la possibilità di effettuare la selezione in una schermata video;
-	set spawn gestisce lo spawn degli ostacoli e definisce una variabile casuale compresa tra 0 e 15: in base al valore decide, se possibile, quale degli ostacoli far spawnare (tenendo conto della loro frequenza di spawn);
-	fuoriStrada: l’utente finisce fuori strada, perde punteggio e la macchina viene fatta rimbalzare verso il centro della strada.
-	Pausa: p, esc permettono di bloccare il gioco (mantenendo lo stato corrente).

#### Funzioni:

Contiene due funzioni ausiliarie per muovere e nascondere il cursore durante la partita.


## Autori:
- Giorgio Di Gregorio;
- Andrea Zecca;
- Luigi Manieri;
- Giovanni Grotto;

