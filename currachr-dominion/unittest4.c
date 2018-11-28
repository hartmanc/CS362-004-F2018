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

    /* Test int supplyCount(int card, struct gameState *state) - should be 10 after game start*/
    if (supplyCount(smithy, &game) == 10)
        printf("whoseTurn: PASS - correct number of cards returned\n");
    else
        printf("whoseTurn: FAIL - incorrect number of cards returned\n");

    printf("\n"); /* Append new line to test results */

    return 0;
}



