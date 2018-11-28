#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "math.h"
#include <stdio.h>
#include <string.h>

#define NUM_TESTS 1000

int checkSmithy(struct gameState* game, int n) {

    //int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
    //
    /* No choices, no bonus for smithy */
    /* handPos = 0 will break gameState, but that's OK */
    /* gameState is only checked once before regenerating in main() */

    /* Ignoring playCard responsibilities here: */
    /* Not testing numAction decrementing */
    /* Not testing phase check - ignore and play action anyway */
    /* cardEffect IS RESPONSIBLE FOR DISCARDING played card */

    /* gameState variables to save and check */
    int whoseTurn = game->whoseTurn;
    /* int oNumBuys = game->numBuys; */
    int oHandCount = game->handCount[whoseTurn]; /* Should increase by 3 */
    int oDeckCount = game->deckCount[whoseTurn]; /* Unless this is less than 3 */
    /* int oDiscardCount = game->discardCount[whoseTurn]; */

    int failuresDetected = 0;

    cardEffect(smithy, 0, 0, 0, game, 0, 0);

    /* The Oracle */
    printf("Test #%d: ", n);
    /* oDeckCount >= 3, smithy should draw 3 cards */
    if (oDeckCount >= 3) {
        if (oHandCount - 1 + 3 == game->handCount[whoseTurn])
            printf("handCount - 1 + 3 - PASS, ");
        else {
            printf("handCount - 1 + 3 - FAIL (orig %d after %d), ",
                    oHandCount, game->handCount[whoseTurn]);
            failuresDetected = 1;
        }
    } else {
        if (oHandCount - 1 + oDeckCount == game->handCount[whoseTurn])
            printf("handCount - 1 + deckCount (%d) - PASS, ", oDeckCount);
        else {
            printf("handCount - 1 + deckCount (%d) - FAIL (orig %d after %d), ", oDeckCount,
                    oHandCount, game->handCount[whoseTurn]);
            failuresDetected = 1;
        }
    }
    printf("\n"); /* New line after test results */
    return failuresDetected;
}

int main() {
    /* Initialize basic game parameters */
    int i, n, p;
    /*
    int k[10] = {   adventurer,
                    council_room,
                    feast,
                    gardens,
                    mine,
                    remodel,
                    smithy,
                    village,
                    baron,
                    great_hall};
                    */

    int failuresDetected = 0;

    struct gameState G;
    
    for (n = 0; n < NUM_TESTS; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        p = floor(Random() * 4);
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);
        /* Avoiding seg faults with the code below! */
        G.whoseTurn = p;
        G.playedCardCount = p = floor(Random() * 256);
        failuresDetected += checkSmithy(&G, n);
    }

    if (failuresDetected) printf("FAILURE - %d TESTS FAILED\n", failuresDetected);
    else printf("OK - ALL TESTS PASSED\n");

    return 0;
}
