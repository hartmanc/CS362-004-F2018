#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "math.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MIN_DECK 0 /* MAX_DECK defined in dominion.h */

#define NUM_TESTS 1000

int checkCardIsTreasure(struct gameState* game, int turn, int pos) {

    return (game->hand[turn][pos] == copper ||
           game->hand[turn][pos] == silver ||
           game->hand[turn][pos] == gold);
}

int checkAdventurer(struct gameState* game, int n) {

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
    int oHandCount = game->handCount[whoseTurn]; /* Should increase by 3 */
    int oDeckCount = game->deckCount[whoseTurn]; /* Unless this is less than 3 */
    int oDiscardCount = game->discardCount[whoseTurn];

    int failuresDetected = 0;

    /* Draw cards until getting two treasure cards or deck runs out, discard rest */
    cardEffect(adventurer, 0, 0, 0, game, 0, 0);

    /* The Oracle */
    /* Several things to check */
    printf("Test #%d: ", n);
    int aHandCount = game->handCount[whoseTurn]; /* Should increase by 3 */
    int aDeckCount = game->deckCount[whoseTurn]; /* Unless this is less than 3 */
    int aDiscardCount = game->discardCount[whoseTurn];
    /* No more than two cards added, adv. card is discarded */
    if (oHandCount + 2 - 1 >= aHandCount)
        printf("At most two cards added - PASS, ");
    else {
        printf("More than two cards added (before: %d, after %d) - FAIL, ", oHandCount, aHandCount);
        failuresDetected++;
    }
    /* Total cards in play conserved */
    if ((oHandCount + oDeckCount + oDiscardCount) ==
            (aHandCount + aDeckCount + aDiscardCount))
        printf("Total cards in play conserved - PASS, ");
    else {
        printf("Total cards in play changed ");
        printf("(oHand: %d, oDeck: %d, oDisc: %d, aHand: %d, aDeck: %d, aDisc: %d) - FAIL, ",
                oHandCount, oDeckCount, oDiscardCount,
                aHandCount, aDeckCount, aDiscardCount);
        failuresDetected++;
    }
    /* Drawn cards added to hand are, in fact, treasure cards */
    int pos = aHandCount - 1;
    /* 2 cards were drawn, both are treasure */
    /* PROGRAM IS NOT DISCARDING ADVENTURER CARD? */
    /* if (oHandCount - 1 + 2 == aHandCount) { */
    if (oHandCount + 2 == aHandCount) {
        if (checkCardIsTreasure(game, whoseTurn, pos)) { /* nth card is treasure */
            if (checkCardIsTreasure(game, whoseTurn, pos - 1)) /* n - 1 card is treasure */
                printf("2d drawn cards are treasure - PASS");
            else {
                printf("2d last card is treasure - FAIL");
                failuresDetected++;
            }
        } else {
            printf("2d card is not treasure - FAIL");
            failuresDetected++;
        }
    /* 1 card was drawn, it is treasure */
    } else if (oHandCount - 1 + 1 == aHandCount) {
        if (checkCardIsTreasure(game, whoseTurn, pos)) /* nth card is treasure */
            printf("1d and it is treasure - PASS");
        else {
            printf("1d and it is not treasure - FAIL");
            failuresDetected++;
        }
    /* No card drawn */
    } else if (oHandCount - 1 == aHandCount)
        printf("0d no cards drawn - PASS");
    else {
        printf("Something went wrong - FAIL");
        failuresDetected++;
    }
    
    printf("\n"); /* New line after test results */
    return failuresDetected;
}

int main() {
    /* Initialize basic game parameters */
    srand(1988);
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
        /* Segfaults
        G.deckCount[p] = abs(floor(Random() * MAX_DECK));
        G.discardCount[p] = abs(floor(Random() * MAX_DECK));
        G.handCount[p] = abs(floor(Random() * MAX_HAND));
        */
        /* Avoiding seg faults with the code below! */
        G.deckCount[p] = (rand() % MAX_DECK + MIN_DECK);
        G.discardCount[p] = (rand() % MAX_DECK + MIN_DECK);
        G.handCount[p] = (rand() % MAX_HAND + MIN_DECK);

        /* Real cards? */
        for (i = 0; i < G.discardCount[p]; i++)
            G.hand[p][i] = (rand() % 15); /* Need to limit range of ints */
        for (i = 0; i < G.handCount[p]; i++)
            G.discard[p][i] = (rand() % 15); /* Need to limit range of ints */
        for (i = 0; i < G.deckCount[p]; i++)
            G.deck[p][i] = (rand() % 15); /* Need to limit range of ints */

        G.whoseTurn = p;
        G.playedCardCount = floor(Random() * 256);
        failuresDetected += checkAdventurer(&G, n);
    }

    if (failuresDetected) printf("FAILURE - %d TESTS FAILED\n", failuresDetected);
    else printf("OK - ALL TESTS PASSED\n");

    return 0;
}

