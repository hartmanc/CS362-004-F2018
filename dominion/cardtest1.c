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
    int maxBonus = 10; /* No idea what this does */

    /* These variables not used in this test */
    /*
    int maxHandCount = 5;
    int i, p, r, handCount, bonus;
    */

    /* Initialize test game */
    initializeGame(numPlayers, kingdomCards, seed, &game);
    struct gameState* state = &game;

    /* Test smithy card */
    int origHandCount = state->handCount[whoseTurn(state)];
    cardEffect(smithy, 0, 0, 0, state, 0, &maxBonus); /* handPos = 0 will break state */

    /* buyCard should not allow more than two buys in a row */
    if (origHandCount + 3 == state->handCount[whoseTurn(state)])
        printf("Smithy: PASS - Expected number of extra cards\n");
    else
        printf("Smithy: FAIL - Unexpected number of extra cards\n");
    return 0;

    /* Append new line to output */
    printf("\n");

}

