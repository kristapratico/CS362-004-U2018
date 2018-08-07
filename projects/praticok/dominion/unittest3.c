#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "playCard()"

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
    int handPos = 0;
    int choice1, choice2, choice3;
    choice1 = choice2 = choice3 = 0; 

    // kingdom cards in use
    int k[10] = {adventurer, minion, feast, gardens, mine,
               tribute, smithy, village, baron, treasure_map};

    int seed = 99;

    // state to use for init game 
    struct gameState state;

    // create a game state
    initializeGame(numPlayers, k, seed, &state);

    printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNCTION);
    
    // TEST 1: Test when it is not the play phase of the game
    numTests++;
    printf("\nTEST 1: Not play phase, should return -1\n");
    printf("Not play phase: ");
    state.phase = 1;
    assertTF(playCard(handPos, choice1, choice2, choice3, &state), -1);

    // clean-up
    state.phase = 0;

    // TEST 2: Not enough actions left to play cards
    numTests++;
    printf("\nTEST 2: No actions left to play cards, should return -1\n");
    printf("No actions left to play: ");
    state.numActions = 0;
    assertTF(playCard(handPos, choice1, choice2, choice3, &state), -1);

    // clean-up
    state.numActions = 4;

    // TEST 3: Test that the card chosen to play is an action card
    numTests++;
    printf("\nTEST 3: Card chosen to play is an action card\n");
    state.hand[player0][0] = adventurer;
    state.hand[player0][1] = treasure_map;
    state.hand[player0][2] = province;
    state.hand[player0][3] = curse;
    state.hand[player0][4] = treasure_map;
    printf("Play adventurer: ");
    assertTF(playCard(0, choice1, choice2, choice3, &state), 0);
    printf("Play treasure_map: ");
    assertTF(playCard(1, choice1, choice2, choice3, &state), 0);
    printf("Play province (returns -1): ");
    assertTF(playCard(2, choice1, choice2, choice3, &state), -1);
    printf("Play curse (returns -1): ");
    assertTF(playCard(3, choice1, choice2, choice3, &state), -1);

    // clean-up
    state.numActions = 1;
    
    // TEST 4: Play Gardens to have call to cardEffect return -1
    numTests++;
    printf("\nTEST 4: Play Gardens to test cardEffect branch, should return -1\n");
    state.hand[player0][4] = gardens;
    printf("Play gardens (returns -1): ");
    assertTF(playCard(4, choice1, choice2, choice3, &state), -1);

    // clean-up
    state.numActions = 4;

    // TEST 5: Test that number of actions is decreased by one after card played
    numTests++;
    printf("\nTEST 5: Number of actions decremented after card played\n");
    printf("Number of actions decremented: ");
    playCard(handPos, choice1, choice2, choice3, &state);
    assertTF(state.numActions, 3);

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
