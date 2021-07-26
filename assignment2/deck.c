#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "deck.h"


/*
 * Function: shuffle
 * --------------------
 *  Initializes deck_instance and shuffles it.
 *  Resets the deck if a prior game has been played.
 * 
 *  returns: 0 if no error, and non-zero on error
 */ 
int shuffle() {
	deck_instance.top_card = 52;							
        char suits[4] = {'D', 'C', 'H', 'S'};							
        char num[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', '1', 'J', 'Q', 'K'};	
	for (int i = 0; i < 52; i++) {	
		deck_instance.list[i].rank[0] = num[i % 13];
	}		
	for (int i = 0; i < 4; i++) {								
		int count = 13 * i;
		while (count < 13 * (i + 1)) {
			deck_instance.list[count].suit = suits[i];
			count++;
		}
	}
        struct card temp;									
	int swap;		
	srand(time(0));								
        for(int i = 0; i < 52; i++){								
                swap = rand() % 52;
		temp = deck_instance.list[swap];
                deck_instance.list[swap] = deck_instance.list[i];
		deck_instance.list[i] = temp;
        }
        return 0;
}

/*
 * Function: deal_player_cards
 * ---------------------------
 *  Deal 7 random cards to the player specified in the function.
 *  Remove the dealt cards from the deck. 
 *
 *  target: pointer to the player to be dealt cards
 *
 *  returns: 0 if no error, and non-zero on error
 */
int deal_player_cards(struct player* target) {
	(*target).card_list = malloc(sizeof(struct hand));
	memset((*target).book, '0', sizeof((*target).book));
	for (int i = 0; i < 7; i++) {
		if (deal_cards(target) != 0) {return -1;}
	}
	return 0;
}

/*
 * Function: deal_cards
 * ---------------------------
 *  Deals a card to the player specified in the function
 *  Remove the dealt card from the deck. 
 *
 *  target: pointer to the player to be dealt cards
 *
 *  returns: 0 if no error, and non-zero on error
 */
int deal_cards(struct player* target) {
	if (deck_instance.top_card == 0) {return -1;}
	struct card add = deck_instance.list[--deck_instance.top_card];
	if ((*target).hand_size == 0) {
		(*target).card_list->next = NULL;
		(*target).card_list->top.rank[0] = add.rank[0];
		(*target).card_list->top.suit = add.suit;
	} else {
		struct hand* foo = malloc(sizeof(struct hand));
		(*foo).next = NULL;
		(*foo).top = *next_card();
		struct hand* temp = (*target).card_list;
		while ((*temp).next != NULL) {
			temp = (*temp).next;
		}
		(*temp).next = foo;
	}
	(*target).hand_size++;
	return 0;
}

/*
 * Function: next_card
 * -------------------
 *  Return a pointer to the top card on the deck.
 *  Removes that card from the deck. 
 *
 *  returns: pointer to the top card on the deck.
 */
struct card* next_card() {
	return &deck_instance.list[--deck_instance.top_card];
}

/*
 * Function: size
 * --------------
 *  Return the number of cards left in the current deck.
 *
 *  returns: number of cards left in the deck.
 */
size_t deck_size() {
	return deck_instance.top_card;
}
