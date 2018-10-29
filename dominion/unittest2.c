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
    struct gameState* state = &game;

    /* Test int buyCard(int supplyPos, struct gameState *state) */
    printf("INFO: Game state after initialization\n");
    printf("\tstate->whoseTurn == %d\n", state->whoseTurn);
    printf("\tstate->phase == %d\n", state->phase);
    printf("\tstate->numBuys == %d\n", state->numBuys);
    printf("\tstate->coins == %d\n", state->coins); /* SHOULD BE 5 */

    /* buyCard should not allow more than two buys in a row */
    if (buyCard(copper, state) == 0)
        printf("buyCard: PASS - 1st buy worked\n");
    else
        printf("buyCard: FAIL - 1st buy should have been allowed\n");
    if (buyCard(copper, state))
        printf("buyCard: PASS - no additional buy\n");
    else
        printf("buyCard: FAIL - additional buy shouldn't have been allowed\n");

    /* Reset numBuys, phase, then test that buys can't be made when supply is out */
    state->numBuys = 999;
    state->phase = 0;
    state->supplyCount[copper] = 0;
    if (buyCard(copper, state))
        printf("buyCard: PASS - shouldn't be able to buy from empty supply pile\n");
    else
        printf("buyCard: FAIL - bought from empty supply pile\n");

    /* Test to see if buys can made despite insufficient coins */
    if (buyCard(province, state))
        printf("buyCard: PASS - shouldn't be able to buy card of greater value than coins\n");
    else
        printf("buyCard: FAIL - bought card of greater value than coins\n");

    /* Test to see if buys affect player coins */
    buyCard(smithy, state);
    if (state->coins == 1) /* SHOULD BE 1, after spending 4 on smithy */
        printf("buyCard: PASS - correct coins spent\n");
    else
        printf("buyCard: FAIL - incorrect coins spent\n");

    /* Test to see if buys affect player coins */
    /* interacts with game state through */
    /* int gainCard(int supplyPos, struct gameState 8state, int toFlag, int player) */
    if (state->discard[state->whoseTurn][ state->discardCount[state->whoseTurn] - 1 ] == smithy)
        printf("buyCard: PASS - bought card in player discard pile\n");
    else
    if (state->discard[state->whoseTurn][ state->discardCount[state->whoseTurn] - 1 ] == smithy)
        printf("buyCard: FAIL - bought card NOT in player discard pile\n");

    printf("\n"); /* Append new line to test results */

    return 0;
}


