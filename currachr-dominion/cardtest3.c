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

    /* Test Great Hall card */
    int origHandCount = state->handCount[whoseTurn(state)];
    int origActions = state->numActions;
    cardEffect(great_hall, 0, 0, 0, state, 0, &maxBonus); /* handPos = 0 will break state */

    /* Was a card drawn and added to the player's hand? */
    /* should draw one and discard one card for a net gain of zero cards */
    if (origHandCount == state->handCount[whoseTurn(state)])
        printf("Great Hall: PASS - Expected number of extra cards\n");
    else
        printf("Great Hall: FAIL - Unexpected number of extra cards\n");

    /* Did the player get two more actions? */
    if (origActions + 1 == state->numActions)
        printf("Great Hall: PASS - Expected number of actions\n");
    else
        printf("Great Hall: FAIL - Unexpected number of actions\n");

    return 0;

    /* Append new line to output */
    printf("\n");

}

