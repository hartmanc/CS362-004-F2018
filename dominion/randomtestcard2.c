#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "math.h"
#include <stdio.h>
#include <string.h>

#define NUM_TESTS 1000

int checkVillage(struct gameState* game, int n) {

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
    int oActions = game->numActions;

    int failuresDetected = 0;

    cardEffect(village, 0, 0, 0, game, 0, 0);

    /* The Oracle */
    printf("Test #%d: ", n);
    /* If there is at least one card, Village draws one after discarding */
    if (oDeckCount >= 1) {
        if (oHandCount - 1 + 1 == game->handCount[whoseTurn]) /* should be the same */
            printf("handCount - 1 + 1 - PASS, ");
        else {
            printf("handCount - 1 + 1 - FAIL (orig %d after %d), ",
                    oHandCount, game->handCount[whoseTurn]);
            failuresDetected = 1;
        }
    } else { /* No cards to draw after discarding */
        if (oHandCount - 1 + oDeckCount == game->handCount[whoseTurn])
            printf("handCount - 1 + deckCount (%d) - PASS, ", oDeckCount);
        else {
            printf("handCount - 1 + deckCount (%d) - FAIL (orig %d after %d), ", oDeckCount,
                    oHandCount, game->handCount[whoseTurn]);
            failuresDetected = 1;
        }
    }
    /* Village should add two actions to gameState */
    if (oActions + 2 == game->numActions)
        printf("numActions + 2 - PASS");
    else
        printf("numActions + 2 - FAIL (orig %d after %d)", oActions, game->numActions);

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
        failuresDetected += checkVillage(&G, n);
    }

    if (failuresDetected) printf("FAILURE - %d TESTS FAILED\n", failuresDetected);
    else printf("OK - ALL TESTS PASSED\n");

    return 0;
}

