#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>

int main() {

    /* Initialize basic game parameters */
    int seed = 1989;
    int numPlayers = 2;
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

    struct gameState game;

    /* These variables not used in this test */
    /*
    int maxBonus = 10;
    int maxHandCount = 5;
    int i, p, r, handCount, bonus;
    */

    /* Initialize test game */
    initializeGame(numPlayers, kingdomCards, seed, &game);

    /* "At least two [tested] functions should be more than 5 lines of code... */

    /* Test int whoseTurn(struct gameState *state) - should return player 0 after initialization */
    if (whoseTurn(&game) == 0)
        printf("whoseTurn: PASS - first to play is player 0 after initialization\n");
    else
        printf("whoseTurn: FAIL - player 0 after initialization\n");

    printf("\n"); /* Append new line to test results */

    return 0;
}


