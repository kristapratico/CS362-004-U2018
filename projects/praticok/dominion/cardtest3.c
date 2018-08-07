#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "minion"

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
    int discard = 1;
    int handPos = 0;
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
    
    // TESTING CHOICE 1
    printf("\n~~Testing Choice 1 - Gain 2 coins~~\n");
    memcpy(&beginningState, &state, sizeof(struct gameState));
    choice1 = 1;
    cardEffect(minion, choice1, choice2, choice3, &state, handPos, &bonus);
    
    // TEST 1: Current player receives +1 action
    numTests++;
    printf("TEST 1: Player0 plays minion and gains +1 action\n");
    printf("Player0 gains +1 action: ");
    assertTF(state.numActions, beginningState.numActions + 1);

    // TEST 2: Check if minion card is recorded as played
    numTests++;
    printf("\nTEST 2: Check if minion card was recorded as played\n");
    printf("minion card was recorded as played: ");
    assertTF(state.playedCardCount, beginningState.playedCardCount + 1);

    // TEST 3: Player0 gains +2 coins
    numTests++;
    printf("\nTEST 3: Player0 chooses to gain +2 coins\n");
    printf("Player0 gains +2 coins: ");
    assertTF(state.coins, beginningState.coins + 2);

    // TEST 4: Player0 does not gain any cards
    numTests++;
    printf("\nTEST 4: Player0 does not gain any cards\n");
    printf("Player0 gains no cards: ");
    assertTF(state.handCount[player0], beginningState.handCount[player0] - discard);

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

    // TESTING CHOICE 2
    printf("\n~~Testing Choice 2 - player0 discards hand, +4 cards, other player with at least 5 cards discards all and draws 4 cards~~\n");
    struct gameState state2;
    initializeGame(numPlayers, k, seed, &state2);
    memcpy(&beginningState, &state2, sizeof(struct gameState));
    handPos = 0;
    choice1 = 0;
    choice2 = 1;
    // give player1 a full hand before turn so attack can be observed
    state2.handCount[player1] = 5;

    cardEffect(minion, choice1, choice2, choice3, &state2, handPos, &bonus);

    // TEST 8: Current player receives +1 action
    numTests++;
    printf("\nTEST 8: Player0 plays minion and gains +1 action\n");
    printf("Player0 gains +1 action: ");
    assertTF(state2.numActions, beginningState.numActions + 1);

    // TEST 9: Player0 now has 4 cards in hand
    numTests++;
    printf("\nTEST 9: Check if player0 now has 4 cards in hand\n");
    printf("player0 has 4 cards in hand: ");
    assertTF(state2.handCount[player0], beginningState.handCount[player0] - 1);

    // TEST 10: Player0 received 4 cards from his own pile
    numTests++;
    printf("\nTEST 3: Player0 gains 4 cards from his own pile\n");
    printf("Player0 drew 4 cards from his own pile: ");
    assertTF(state2.deckCount[player0], beginningState.deckCount[player0] - 4);

    // TEST 11: Player1 now has 4 cards in hand from the attack
    numTests++;
    printf("\nTEST 11: Check if player1 now has 4 cards in hand from the attack\n");
    printf("player1 has 4 cards in hand: ");
    assertTF(state2.handCount[player1], 4);

    // TEST 12: No state change occurs to the victory card piles
    numTests++;
    printf("\nTEST 12: No state change occurs to victory card piles\n");
    printf("Estate pile unchanged: ");
    assertTF(state2.supplyCount[estate], beginningState.supplyCount[estate]);
    printf("Duchy pile unchanged: ");
    assertTF(state2.supplyCount[duchy], beginningState.supplyCount[duchy]);
    printf("Province pile unchanged: ");
    assertTF(state2.supplyCount[province], beginningState.supplyCount[province]);

    // TEST 13: No state change occurs to the kingdom card piles
    numTests++;
    printf("\nTEST 13: No state change occurs to kingdom card piles\n");
    for (int x = 0; x < 10; x++) {
        printf("Card %d: ", x);
        assertTF(state2.supplyCount[k[x]], beginningState.supplyCount[k[x]]);
    }


    printf("\n----End Tests for %s----\n", TESTCARD);
    printf("\nNumber of Tests Ran: %d\n", numTests);
    
    if (numFailedTests == 0) {
        printf("All tests for %s PASSED\n", TESTCARD);
    }
    else {
        printf("Number of Tests Failed: %d\n", numFailedTests);
    }

    return 0;
}
