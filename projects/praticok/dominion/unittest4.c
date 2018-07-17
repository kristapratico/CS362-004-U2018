#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "gainCard()"

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

// checks if the card is in the player's hand, deck, or discard
int checkForCard(int player, int card, int location, struct gameState *state) {
    // if card is present = 1; otherwise = 0
    int present = 0;

    // location: 0 = discard; 1 = deck; 2 = hand 
    if (location == 0) {
        for (int x = 0; x < state->discardCount[player]; x++) {
            if (state->discard[player][x] == card) {
                present = 1;
            }
        }
        return present;    
    }    
    
    if (location == 1) {
        for (int x = 0; x < state->deckCount[player]; x++) {
            if (state->deck[player][x] == card) {
                present = 1;
            }
        }
        return present;    
    }
    
    if (location == 2) {
        for (int x = 0; x < state->handCount[player]; x++) {
            if (state->hand[player][x] == card) {
                present = 1;
            }
        }
        return present;    
    }
    return -1;
}


int main () {
    int numPlayers = 2;
    int player0 = 0;
    int player1 = 1;
    int toDiscard = 0;
    int toDeck = 1;
    int toHand = 2;

    // kingdom cards in use
    int k[10] = {adventurer, minion, feast, gardens, mine,
               tribute, smithy, village, baron, treasure_map};

    int seed = 99;

    // state to use for init game and beginningState to check if state changed
    struct gameState state, beginningState;

    // create a game state
    initializeGame(numPlayers, k, seed, &state);
    memcpy(&beginningState, &state, sizeof(struct gameState));

    printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);
    
    // TEST 1: Supply pile is empty or card does not exist in game
    numTests++;
    printf("\nTEST 1: Supply pile is empty or card does not exist in game\n");
    state.supplyCount[adventurer] = 0;
    printf("Supply pile empty, return -1: ");
    assertTF(gainCard(adventurer, &state, toHand, player0), -1);
    printf("Player0 did not gain adventurer card in hand: ");
    assertTF(checkForCard(player0, adventurer, toHand, &state), 0);
    printf("Player1 did not gain adventurer card in hand: ");
    assertTF(checkForCard(player1, adventurer, toHand, &state), 0);
    
    printf("Card not in game, return -1: ");
    assertTF(gainCard(outpost, &state, toHand, player0), -1);
    printf("Player0 did not gain outpost card in hand: ");
    assertTF(checkForCard(player0, outpost, toHand, &state), 0);
    printf("Player1 did not gain outpost card in hand: ");
    assertTF(checkForCard(player1, outpost, toHand, &state), 0);

    memcpy(&state, &beginningState, sizeof(struct gameState));
    // TEST 2: Add village to player0's hand
    numTests++;
    printf("\nTEST 2: Add village to player0's hand\n");
    gainCard(village, &state, toHand, player0);
    printf("Village is in player0's hand: ");
    assertTF(checkForCard(player0, village, toHand, &state), 1);
    printf("player0's hand count increased: ");
    assertTF(state.handCount[player0], beginningState.handCount[player0] + 1);
    printf("Village was not added to player0's deck: ");
    assertTF(checkForCard(player0, village, toDeck, &state), 0);
    printf("Village was not added to player0's discard: ");
    assertTF(checkForCard(player0, village, toDiscard, &state), 0);
    printf("Village was not added to player1's hand: ");
    assertTF(checkForCard(player1, village, toHand, &state), 0);
    printf("Village was not added to player1's deck: ");
    assertTF(checkForCard(player1, village, toDeck, &state), 0);
    printf("Village was not added to player1's discard: ");
    assertTF(checkForCard(player1, village, toDiscard, &state), 0);
    printf("Supply pile for village is decremented: ");
    assertTF(state.supplyCount[village], 9);

    memcpy(&state, &beginningState, sizeof(struct gameState));
    // TEST 3: Add village to player0's deck
    numTests++;
    printf("\nTEST 3: Add village to player0's deck\n");
    gainCard(village, &state, toDeck, player0);
    printf("Village is in player0's deck: ");
    assertTF(checkForCard(player0, village, toDeck, &state), 1);
    printf("player0's deck count increased: ");
    assertTF(state.deckCount[player0], beginningState.deckCount[player0] + 1);
    printf("Village was not added to player0's hand: ");
    assertTF(checkForCard(player0, village, toHand, &state), 0);
    printf("Village was not added to player0's discard: ");
    assertTF(checkForCard(player0, village, toDiscard, &state), 0);
    printf("Village was not added to player1's hand: ");
    assertTF(checkForCard(player1, village, toHand, &state), 0);
    printf("Village was not added to player1's deck: ");
    assertTF(checkForCard(player1, village, toDeck, &state), 0);
    printf("Village was not added to player1's discard: ");
    assertTF(checkForCard(player1, village, toDiscard, &state), 0);
    printf("Supply pile for village is decremented: ");
    assertTF(state.supplyCount[village], 9);


    memcpy(&state, &beginningState, sizeof(struct gameState));
    // TEST 4: Add village to player0's discard
    numTests++;
    printf("\nTEST 4: Add village to player0's discard\n");
    gainCard(village, &state, toDiscard, player0);
    printf("Village is in player0's discard: ");
    assertTF(checkForCard(player0, village, toDiscard, &state), 1);
    printf("player0's discard count increased: ");
    assertTF(state.discardCount[player0], beginningState.discardCount[player0] + 1);
    printf("Village was not added to player0's hand: ");
    assertTF(checkForCard(player0, village, toHand, &state), 0);
    printf("Village was not added to player0's deck: ");
    assertTF(checkForCard(player0, village, toDeck, &state), 0);
    printf("Village was not added to player1's hand: ");
    assertTF(checkForCard(player1, village, toHand, &state), 0);
    printf("Village was not added to player1's deck: ");
    assertTF(checkForCard(player1, village, toDeck, &state), 0);
    printf("Village was not added to player1's discard: ");
    assertTF(checkForCard(player1, village, toDiscard, &state), 0);
    printf("Supply pile for village is decremented: ");
    assertTF(state.supplyCount[village], 9);

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