#include <iostream>
#include "titolo.hpp"
 #include "gameManager.hpp"
using namespace std;

int main() {
    //stampa del titolo
    titolo title = titolo();
    title.stampaTitolo();
    int diff;
    gameManager game;
    do {
        //scelta difficoltà
        diff = title.difficulty();
        game = gameManager(diff);
        //avvio del gioco
        game.start();
    } while (game.restart());
    return 0;

}




