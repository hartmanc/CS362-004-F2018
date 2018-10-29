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

    /* Test int isGameOver(struct gameState *state) */

    /* Game should not be over, just initialized */
    if (isGameOver(&game))
        printf("isGameOver: FAIL - game can't be over, just initialized!\n");
    else
        printf("isGameOver: PASS - game isn't over, just initialized\n");

    /* Make game state's province card's empty, test again */
    printf("Set game state to 0 province cards - game is over\n");
    (&game)->supplyCount[province] = 0;
    if (isGameOver(&game))
        printf("isGameOver: PASS - game is over, there are no province cards left\n");
    else
        printf("isGameOver: FAIL - game is over, there are no province cards left\n");

    printf("Set game state to 1 province card - game is not over\n");
    (&game)->supplyCount[province] = 1;

    if (isGameOver(&game))
        printf("isGameOver: FAIL - game is not over, there is one province card left\n");
    else
        printf("isGameOver: PASS - game is not over, there is one province card left\n");

    /* Make game state's province card's empty, test again */
    printf("Set supply count of adventurer to 0 - one supply pile at 0, game ongoing\n");
    (&game)->supplyCount[adventurer] = 0;
    if (isGameOver(&game))
        printf("isGameOver: FAIL - game is not over, only one supply pile at 0\n");
    else
        printf("isGameOver: PASS - game is not over, only one supply pile at 0\n");

    printf("Set supply count of smithy to 0 - one supply pile at 0, game ongoing\n");
    (&game)->supplyCount[smithy] = 0;
    if (isGameOver(&game))
        printf("isGameOver: FAIL - game is not over, only two supply piles at 0\n");
    else
        printf("isGameOver: PASS - game is not over, only two supply piles at 0\n");

    printf("Set supply count of baron to 0 - one supply pile at 0, game ongoing\n");
    (&game)->supplyCount[baron] = 0;
    if (isGameOver(&game))
        printf("isGameOver: PASS - game is over, three supply piles at 0\n");
    else
        printf("isGameOver: FAIL - game is over, three supply piles at 0\n");

    printf("\n"); /* Append new line to test results */

    return 0;
}

