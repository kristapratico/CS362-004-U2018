#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "isGameOver()"

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
    int gameOver = 1;
    int gameInProgress = 0;

    // kingdom cards in use
    int k[10] = {adventurer, minion, feast, gardens, mine,
               tribute, smithy, village, baron, treasure_map};

    int seed = 99;

    // state to use for init game 
    struct gameState state;

    // create a game state
    initializeGame(numPlayers, k, seed, &state);

    printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNCTION);
    
    // TEST 1: Game just begun, no plays happened yet
    numTests++;
    printf("\nTEST 1: Game just initialized, check if game is over\n");
    printf("Game is not over: ");
    assertTF(isGameOver(&state), gameInProgress);

    // TEST 2: Province pile is empty
    numTests++;
    printf("\nTEST 2: Province pile is empty, game is over\n");
    printf("Game is over: ");
    state.supplyCount[province] = 0;
    assertTF(isGameOver(&state), gameOver);

    // clean-up
    state.supplyCount[province] = 1;

    // TEST 3: Three supply piles empty
    numTests++;
    printf("\nTEST 3: Three supply piles empty (edge of loop case), game is over\n");
    printf("Game is over: ");
    state.supplyCount[minion] = 0;
    state.supplyCount[tribute] = 0;
    state.supplyCount[treasure_map] = 0;
    assertTF(isGameOver(&state), gameOver);

    // clean-up
    state.supplyCount[minion] = 1;
    state.supplyCount[tribute] = 1;
    state.supplyCount[treasure_map] = 1;

    // TEST 4: Two supply piles empty
    numTests++;
    printf("\nTEST 4: Two supply piles empty, game is in progress\n");
    printf("Game is not over: ");
    state.supplyCount[adventurer] = 0;
    state.supplyCount[smithy] = 0;
    assertTF(isGameOver(&state), gameInProgress);

    // clean-up
    state.supplyCount[adventurer] = 1;
    state.supplyCount[smithy] = 1;

    // TEST 5: Non-kingdom card supplies are empty (victory card, treasure, curse)
    numTests++;
    printf("\nTEST 5: Three non-kingdom supplies empty (victory card, treasure, curse) empty, game is over\n");
    printf("Game is over: ");
    state.supplyCount[estate] = 0;
    state.supplyCount[curse] = 0;
    state.supplyCount[silver] = 0;
    assertTF(isGameOver(&state), gameOver);

    // clean-up
    state.supplyCount[estate] = 1;
    state.supplyCount[curse] = 1;
    state.supplyCount[silver] = 1;


    printf("\n----End Tests for %s----\n", TESTFUNCTION);
    printf("\nNumber of Tests Ran: %d\n", numTests);
    
    if (numFailedTests == 0) {
        printf("All tests for %s PASSED\n", TESTFUNCTION);
    }
    else {
        printf("Number of Tests Failed: %d\n", numFailedTests);
    }

    return 0;
}
