#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"
#define DEBUG_PRINT 0
#define NUM_TESTS 1

int UNIQUE_CARDS = 27;
int error1 = 0;
int error2 = 0;
int error3 = 0;
int error4 = 0;
int error5 = 0; 
int error6 = 0;

void printGameState(struct gameState *state);

// custom assert 
int assertTF(int value1, int value2) {
    if (value1 == value2)
        return 0;
    else 
        return 1;
}

void checkSmithyCard(int p, int k[], struct gameState *pre) {
    struct gameState post;
    memcpy(&post, pre, sizeof(struct gameState));
    int handPos = rand() % 5;
    post.hand[p][handPos] = smithy;
    int choice1, choice2, choice3;
    choice1 = choice2 = choice3 = 0;
    int bonus = 0;
    int checkCardCount, checkIfPlayedCard, checkCardGainFromPile, StateChangePlyr, StateChangeKing, StateChangeVictory;
    checkCardCount = checkIfPlayedCard = checkCardGainFromPile = StateChangePlyr = StateChangeKing = StateChangeVictory = 0;
    cardEffect(smithy, choice1, choice2, choice3, &post, handPos, &bonus);
    
    // player's handcount increases by 2
    checkCardCount = assertTF(pre->handCount[p] + 3 - 1, post.handCount[p]);
    checkIfPlayedCard = assertTF(pre->playedCardCount + 1, post.playedCardCount);
    checkCardGainFromPile = assertTF(pre->deckCount[p] - 3, post.deckCount[p]);
    // no state change to other players
    for(int y = 1; y < post.numPlayers; y++) {
        if (pre->handCount[y] != post.handCount[y]) 
            StateChangePlyr = 1;               
        if (pre->deckCount[y] != post.deckCount[y]) 
            StateChangePlyr = 1;         
        if (pre->discardCount[y] != post.discardCount[y]) 
            StateChangePlyr = 1;         
    }

    if (pre->supplyCount[estate] != post.supplyCount[estate]) 
        StateChangeVictory = 1;                 
    if (pre->supplyCount[duchy] != post.supplyCount[duchy])
        StateChangeVictory = 1;        
    if (pre->supplyCount[province] != post.supplyCount[province])
        StateChangeVictory = 1;

    for (int x = 0; x < 10; x++) {
        if(pre->supplyCount[k[x]] != post.supplyCount[k[x]])
            StateChangeKing = 1;
    }
    
    if(checkCardCount)
        error1++;
    if(checkIfPlayedCard)
        error2++;
    if(checkCardGainFromPile)
        error3++;
    if(StateChangePlyr)
        error4++;
    if(StateChangeKing)
        error5++;
    if(StateChangeVictory)
        error6++;

    if (DEBUG_PRINT) {
        if (checkCardCount || checkIfPlayedCard || checkCardGainFromPile || StateChangePlyr
            || StateChangeKing || StateChangeVictory) {
            printGameState(&post);
        }
    }
}

int randomize(struct gameState *state, int k[]) {
    int players = rand() % MAX_PLAYERS;
    int plyr = 0;
    state->numPlayers = players;
    state->deckCount[plyr] = rand() % MAX_DECK;
    state->discardCount[plyr] = rand() % MAX_DECK;
    state->handCount[plyr] = rand() % 5;
    state->playedCardCount = 0; 

    for (int i = 0; i < state->deckCount[plyr]; i++)
	    state->deck[plyr][i] = rand() % UNIQUE_CARDS;
    for (int i = 0; i < state->discardCount[plyr]; i++)
	    state->discard[plyr][i] = rand() % UNIQUE_CARDS;
    for (int i = 0; i < state->handCount[plyr]; i++)
	    state->hand[plyr][i] = rand() % UNIQUE_CARDS;
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
               tribute, smithy, village, baron, council_room};
    int player;

    for(int x = 0; x < NUM_TESTS; x++) {
        struct gameState state;
        player = randomize(&state, k);
        checkSmithyCard(player, k, &state);
    }
    printf("Error 1: %d\n", error1);
    printf("Error 2: %d\n", error2);
    printf("Error 3: %d\n", error3);
    printf("Error 4: %d\n", error4);
    printf("Error 5: %d\n", error5);
    printf("Error 6: %d\n", error6);
    return 0;
}