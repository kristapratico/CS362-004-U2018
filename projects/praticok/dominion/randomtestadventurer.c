#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"
#define DEBUG_PRINT 0
#define NUM_TESTS 10000

// num unqiue cards in this implementation of Dominion
int UNIQUE_CARDS = 27;

// holds the error counts for each test case
int error1 = 0;
int error2 = 0;
int error3 = 0;
int error4 = 0;
int error5 = 0; 
int error6 = 0;

// func prototype for debugging
void printGameState(struct gameState *state);

// custom assert 
int assertTF(int value1, int value2) {
    if (value1 == value2)
        return 0;
    else 
        return 1;
}

// function plays adventurer and then compares the pre and post game 
// state to check for desired game behavior
void checkAdventurerCard(int p, int k[], struct gameState *pre) {
    // state after adventurer card played
    struct gameState post;
    
    // copy the randomized state to post
    memcpy(&post, pre, sizeof(struct gameState));

    // place adventurer in hand and randomize other cardEffect arguments
    int handPos = 0;
    post.hand[p][handPos] = adventurer;
    int choice1, choice2, choice3;
    choice1 = rand() % 5;
    choice2 = rand() % 5;
    choice3 = rand() % 5;
    int bonus = rand() % 5;

    // vars for checking for treasure cards added to hand
    int isTreasure = 0;
    int numOriginalTreasures = 0;
    int currentNumTreasures = 0;

    // variables that hold game behavior: 0 = correct behavior and 1 = incorrect behavior
    int checkHandCount, isCardPlayed, isTreasureCards, stateChangePlyr, stateChangeKing, stateChangeVictory;
    checkHandCount = isCardPlayed = isTreasureCards = stateChangePlyr = stateChangeKing = stateChangeVictory = 0;
    
    // call cardEffect with adventurer
    cardEffect(adventurer, choice1, choice2, choice3, &post, handPos, &bonus);
    
    // check if player's handcount increases by 1 (+2 cards - discard)
    checkHandCount = assertTF(pre->handCount[p] + 2 - 1, post.handCount[p]);
    
    // check if played card count is incremented
    isCardPlayed = assertTF(pre->playedCardCount + 1, post.playedCardCount);
    
    // check if cards gained by player are treasure cards
    for (int x = 0; x < pre->handCount[p]; x++) {
        isTreasure = pre->hand[p][x];
        if(isTreasure == copper || isTreasure == silver || isTreasure == gold) {
            numOriginalTreasures++;
        }
    }
    numOriginalTreasures = numOriginalTreasures + 2; 

    for (int x = 0; x < post.handCount[p]; x++) {
        isTreasure = post.hand[p][x];
        if(isTreasure == copper || isTreasure == silver || isTreasure == gold) {
            currentNumTreasures++;
        }
    }
    if(currentNumTreasures != numOriginalTreasures) 
        isTreasureCards = 1;

    // no state change to other players
    for(int y = 0; y < post.numPlayers; y++) {
        if (y == post.whoseTurn) {
            continue;
        }
        if (pre->handCount[y] != post.handCount[y])
            stateChangePlyr = 1;                        
        if (pre->deckCount[y] != post.deckCount[y]) 
            stateChangePlyr = 1;
        if (pre->discardCount[y] != post.discardCount[y])
            stateChangePlyr = 1;                       
    }
    // no state change occurs to victory card piles
    if (pre->supplyCount[estate] != post.supplyCount[estate]) 
        stateChangeVictory = 1;                 
    if (pre->supplyCount[duchy] != post.supplyCount[duchy])
        stateChangeVictory = 1;        
    if (pre->supplyCount[province] != post.supplyCount[province])
        stateChangeVictory = 1;

    // no state change occurs to kingdom card piles
    for (int x = 0; x < 10; x++) {
        if(pre->supplyCount[k[x]] != post.supplyCount[k[x]])
            stateChangeKing = 1;
    }
    
    // check for errors and increment counters
    if(DEBUG_PRINT)
        error1++;
    if(isCardPlayed)
        error2++;
    if(isTreasureCards)
        error3++;
    if(stateChangePlyr)
        error4++;
    if(stateChangeKing)
        error5++;
    if(stateChangeVictory)
        error6++;

    // if DEBUG_PRINT true, print the game state for troubleshooting
    if (stateChangePlyr) {
        if (checkHandCount || isCardPlayed || isTreasureCards || stateChangePlyr
            || stateChangeKing || stateChangeVictory) {
            printGameState(&post);
        }
    }
}

// randomize the game state before calling adventurerCard
// returns player to be tested 
int randomize(struct gameState *state, int k[]) {
    // random num of players and randomly select player
    int players = (rand() % 3) + 2;
    state->numPlayers = players;
    int plyr = rand() % players;
    state->whoseTurn = plyr;

    // randomize deck, discard, and hand counts
    state->deckCount[plyr] = rand() % (MAX_DECK - 4 + 1) + 3;
    state->discardCount[plyr] = 0;
    state->handCount[plyr] = rand() % (MAX_HAND - 4 + 1) + 3;
    state->playedCardCount = 0;

    // fill deck, discard, and hand with random cards
    for (int i = 0; i < state->deckCount[plyr]; i++)
        state->deck[plyr][i] = rand() % UNIQUE_CARDS;
    state->deck[plyr][state->deckCount[plyr]-2] = copper;
    state->deck[plyr][state->deckCount[plyr]-3] = copper;
    state->deck[plyr][state->deckCount[plyr]-4] = copper;

    for (int i = 0; i < state->handCount[plyr]; i++)
        state->hand[plyr][i] = rand() % UNIQUE_CARDS;

    // initialize supply counts for victory and kingdom card
    // piles. Will check that these do not change after adventurer
    // is played.
    for (int x = 0; x < 10; x++)
        state->supplyCount[k[x]] = 10;

    state->supplyCount[province] = 10;
    state->supplyCount[duchy] = 10;  
    state->supplyCount[estate] = 10;
    return plyr;
}

// For Debugging when a test case fails
void printGameState(struct gameState *state) {
    printf("Number of Players: %d\n", state->numPlayers);
    printf("Player we're testing: %d\n", state->whoseTurn);
    printf("Played Card Count: %d\n", state->playedCardCount);
    printf("Supply Count: \n");
    for(int i = 0; i < 27; i++) {
        printf("%d: %d \n", i, state->supplyCount[i]);
    }
    printf("Player(s) Hand Count: \n");
    for (int i = 0; i < state->numPlayers; i++) {
	    printf("player %d: %d\n", i, state->handCount[i]);
    }
    printf("Player(s) Deck Count: \n");
    for (int i = 0; i < state->numPlayers; i++) {
	    printf("player %d: %d \n", i, state->deckCount[i]);
    }
    printf("Player(s) Discard Count: \n");
    for (int i = 0; i < state->numPlayers; i++) {
	    printf("player %d: %d \n", i, state->discardCount[i]);
    }
}


int main () {
    srand(time(NULL));

    // kingdom cards in use
    int k[10] = {adventurer, minion, feast, gardens, mine,
               tribute, adventurer, village, baron, council_room};
    int player;

    for(int x = 0; x < NUM_TESTS; x++) {
        struct gameState state;
        player = randomize(&state, k);
        checkAdventurerCard(player, k, &state);
    }


    printf("\n-------------------- START Random Tests for %s --------------------\n", TESTCARD);

    printf("\nTEST 1: Player gains +2 cards \n\tCases Passed: %d/%d\n\n", (NUM_TESTS - error1), NUM_TESTS);
    printf("TEST 2: Card is marked as played \n\tCases Passed: %d/%d\n\n", (NUM_TESTS - error2), NUM_TESTS);
    printf("TEST 3: Cards gained by player are treasure cards \n\tCases Passed: %d/%d\n\n", (NUM_TESTS - error3), NUM_TESTS);
    printf("TEST 4: No state change to other player(s) \n\tCases Passed: %d/%d\n\n", (NUM_TESTS - error4), NUM_TESTS);
    printf("TEST 5: No state change to kingdom card piles \n\tCases Passed: %d/%d\n\n", (NUM_TESTS - error5), NUM_TESTS);
    printf("TEST 6: No state change to victory card piles \n\tCases Passed: %d/%d\n\n", (NUM_TESTS - error6), NUM_TESTS);

    if (error1 == 0 && error2 == 0 && error3 == 0 &&
        error4 == 0 && error5 == 0 && error6 == 0) {
        printf("\nAll tests successfully PASSED\n");
    }

    printf("-------------------- END Random Tests for %s --------------------\n", TESTCARD);
    
    return 0;
}