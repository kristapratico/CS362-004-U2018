#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

// Counters for number of tests and failed tests
int numFailedTests = 0;
int numTests = 0;

// custom assert 
void assertTF(int value1, int value2) {
    if (value1 == value2) {
        printf("PASSED\n");
    }
    else {
        printf("FAILED\n");
        numFailedTests++;
    }
}

int main () {
    int numPlayers = 2;
    int player0 = 0;
    int player1 = 1;
    int handPos = 0;
    int discard = 1;
    int choice1, choice2, choice3;
    choice1 = choice2 = choice3 = 0;
    int bonus = 0;

    // kingdom cards in use
    int k[10] = {adventurer, minion, feast, gardens, mine,
               tribute, smithy, village, baron, council_room};

    int seed = 99;

    // state to use for init game and beginningState to check if state changed
    struct gameState state, beginningState;

    // create a game state
    initializeGame(numPlayers, k, seed, &state);

    printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);

    memcpy(&beginningState, &state, sizeof(struct gameState));
    cardEffect(village, choice1, choice2, choice3, &state, handPos, &bonus);

    // TEST 1: Current player receives exactly 1 card
    numTests++;
    printf("TEST 1: Player0 plays village and receives exactly 1 card\n");
    printf("Player0 gains 1 card: ");
    assertTF(state.handCount[player0], beginningState.handCount[player0] + 1 - discard);

    // TEST 2: Check if village card is recorded as played
    numTests++;
    printf("\nTEST 2: Check if village card was recorded as played\n");
    printf("village card was recorded as played: ");
    assertTF(state.playedCardCount, beginningState.playedCardCount + 1);

    // TEST 3: Current player gained 1 card from his own pile
    numTests++;
    printf("\nTEST 3: Player0 gained 1 card from his own pile\n");
    printf("Player0 drew 1 card from his own pile: ");
    assertTF(state.deckCount[player0], beginningState.deckCount[player0] - 1);

    // TEST 4: Current player receives +2 actions
    numTests++;
    printf("\nTEST 4: Player0 gains +2 actions\n");
    printf("Player0 gains +2 actions: ");
    assertTF(state.numActions, beginningState.numActions + 2);

    // TEST 5: No state change occurs for other player
    numTests++;
    printf("\nTEST 5: No state change occurs for player1\n");
    printf("Player1 hand count was not changed: ");
    assertTF(state.handCount[player1], beginningState.handCount[player1]);
    printf("Player1 deck count was not changed: ");
    assertTF(state.deckCount[player1], beginningState.deckCount[player1]);

    // TEST 6: No state change occurs to the victory card piles
    numTests++;
    printf("\nTEST 6: No state change occurs to victory card piles\n");
    printf("Estate pile unchanged: ");
    assertTF(state.supplyCount[estate], beginningState.supplyCount[estate]);
    printf("Duchy pile unchanged: ");
    assertTF(state.supplyCount[duchy], beginningState.supplyCount[duchy]);
    printf("Province pile unchanged: ");
    assertTF(state.supplyCount[province], beginningState.supplyCount[province]);

    // TEST 7: No state change occurs to the kingdom card piles
    numTests++;
    printf("\nTEST 7: No state change occurs to kingdom card piles\n");
    for (int x = 0; x < 10; x++) {
        printf("Card %d: ", x);
        assertTF(state.supplyCount[k[x]], beginningState.supplyCount[k[x]]);
    }

    printf("\n----End Tests for %s----\n", TESTCARD);
    printf("\nNumber of Tests Ran: %d\n", numTests);
    
    if (numFailedTests == 0) {
        printf("All tests for %s PASSED\n", TESTCARD);
    }
    else {
        printf("Number of Tests Failed: %d\n", numFailedTests);
    }
    printf("\n--------------------End Unit Tests------------------------\n");	
    return 0;
}
