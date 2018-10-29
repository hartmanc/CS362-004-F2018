#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>

int main() {

    /* Initialize basic game parameters */
    int seed = 1989;
    int numPlayers = 2;
    int maxBonus = 10;
    int maxHandCount = 5;
    int kingdomCards[10] = {adventurer,
                            council_room,
                            feast,
                            gardens,
                            mine,
                            remodel,
                            smithy,
                            village,
                            baron,
                            great_hall};

    /* Declare other variables */
    int i, p, r, handCount, bonus;
    struct gameState game;

    /* Initialize test game */
    initializeGame(numPlayers, kingdomCards, seed, &game);
    shuffle(0, &game);

    return 0;
}

