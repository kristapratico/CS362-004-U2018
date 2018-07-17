#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "fullDeckCount()"

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

    // kingdom cards in use
    int k[10] = {adventurer, minion, feast, gardens, mine,
               tribute, smithy, village, baron, treasure_map};

    int seed = 99;

    // state to use for init game 
    struct gameState state;

    // create a game state
    initializeGame(numPlayers, k, seed, &state);

    printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);
    
    // TEST 1: Enumerating Gardens, none present in hand, discard, or deck
    numTests++;
    printf("\nTEST 1: Count Gardens, zero present in hand, deck, or discard\n");
    printf("Zero gardens counted: ");
    assertTF(fullDeckCount(player0, gardens, &state), 0);

    // TEST 2: Enumerating Gardens, five gardens in deck
    numTests++;
    printf("\nTEST 2: Count Gardens, deck: 5; hand: 0; discard: 0\n");
    for (int i = 0; i < 5; i++)
        state.deck[player0][i] = gardens;
    printf("Five gardens counted: ");
    assertTF(fullDeckCount(player0, gardens, &state), 5);

    // TEST 3: Enumerating Gardens, five gardens in deck and 4 in hand
    numTests++;
    printf("\nTEST 3: Count Gardens, deck: 5; hand: 4; discard: 0\n");
    for (int i = 0; i < 4; i++)
        state.hand[player0][i] = gardens;
    printf("Nine gardens counted: ");
    assertTF(fullDeckCount(player0, gardens, &state), 9);

    // TEST 4: Enumerating Gardens, five gardens in deck, 4 in hand, 1 in discard
    numTests++;
    printf("\nTEST 4: Count Gardens, deck: 5; hand: 4; discard: 1\n");
    state.discard[player0][0] = gardens;
    state.discardCount[player0] = 1;
    printf("Ten gardens counted: ");
    assertTF(fullDeckCount(player0, gardens, &state), 10);


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