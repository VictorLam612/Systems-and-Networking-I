#include <stdio.h>
#include <string.h>
#include "player.h"


/*
 * Function: add_card
 * -------------------
 *  Add a new card to the player's hand. 
 *
 *  target: the target player
 *  new_card: pointer to the new card to add
 *
 *  returns: return 0 if no error, non-zero otherwise
 */
int add_card(struct player* target, struct card* new_card) {
	struct hand* foo = malloc(sizeof(struct hand));
	(*foo).top = *new_card;
	(*foo).next = NULL;
	if ((*target).card_list == NULL) {(*target).card_list = foo;}
	else {
		struct hand* temp = (*target).card_list;
		while((*temp).next != NULL) {
			temp = (*temp).next;
		}
		(*temp).next = foo;
	}
	(*target).hand_size++;
	return 0;
}

/*
 * Function: remove_card
 * ---------------------
 *  Remove a card from the player's hand. 
 *
 *  target: the target player
 *  old_card: pointer to the old card to remove
 *
 *  returns: return 0 if no error, non-zero otherwise
 */
int remove_card(struct player* target, struct card* old_card) {
	if ((*target).card_list == NULL) {return -1; }
	struct hand* temp = (*target).card_list;
	struct hand* prev = temp;
	if (strcmp((*old_card).rank, (*temp).top.rank) == 0 && (*old_card).suit == (*temp).top.suit) {
		(*target).card_list = (*target).card_list->next;
		free(temp);
		(*target).hand_size--;
		return 0;
	}
	while (prev != NULL) {
		if (strcmp((*old_card).rank, (*temp).top.rank) == 0 && (*old_card).suit == (*temp).top.suit) {
			(*prev).next = (*temp).next;
			free(temp);
			(*target).hand_size--;
			return 0;
		}
		prev = temp;
		temp = (*temp).next;
	}
	return -1;
}
			

/*
 * Function: check_add_book
 * ------------------------
 *  Check if a player has all 4 cards of the same rank.
 *  If so, remove those cards from the hand, and add the rank to the book.
 *  Returns after finding one matching set of 4, so should be called after adding each a new card.
 * 
 *  target: pointer to the player to check
 *  
 *  Return: a char that indicates the book that was added; return 0 if no book added.
 */
char check_add_book (struct player* target) {
	if ((*target).hand_size < 4) {return '0';}
	int flag = -1;
	int arr[13];
	struct hand* foo = (*target).card_list;
	while (foo != NULL) {
		char temp = (*foo).top.rank[0];
		switch (temp) {
		case 'A':
			arr[0]++;
			if (arr[0] == 4) {flag = 0;}
			break;
		case '2':
			arr[1]++;
			if (arr[1] == 4) {flag = 1;}
			break;
		case '3':
			arr[2]++;
			if (arr[2] == 4) {flag = 2;}
			break;
		case '4':
			arr[3]++;
			if (arr[3] == 4) {flag = 3;}
			break;
		case '5':
			arr[4]++;
			if (arr[4] == 4) {flag = 4;}
			break;
		case '6':
			arr[5]++;
			if (arr[5] == 4) {flag = 5;}
			break;
		case '7':
			arr[6]++;
			if (arr[6] == 4) {flag = 6;}
			break;
		case '8':
			arr[7]++;
			if (arr[7] == 4) {flag = 7;}
			break;
		case '9':
			arr[8]++;
			if (arr[8] == 4) {flag = 8;}
			break;
		case '1':
			arr[9]++;
			if (arr[9] == 4) {flag = 9;}
			break;
		case 'J':
			arr[10]++;
			if (arr[10] == 4) {flag = 10;}
			break;
		case 'Q':
			arr[11]++;
			if (arr[11] == 4) {flag = 11;}
			break;
		default:
			arr[12]++;
			if (arr[12] == 4) {flag = 12;}
			break;
		}
		if(flag != -1) {break;}
	}
	if (flag != -1) {
		int i = 0;
		while (i < 7) {
			if ((*target).book[i] != '0') {break;}
			i++;
		}
		switch(flag) {
		case 0:
			(*target).book[i] = 'A';
			break;
		case 1:
			(*target).book[i] = '2';
			break;
		case 2:
			(*target).book[i] = '3';
			break;
		case 3:
			(*target).book[i] = '4';
			break;
		case 4:
			(*target).book[i] = '5';
			break;
		case 5:
			(*target).book[i] = '6';
			break;
		case 6:
			(*target).book[i] = '7';
			break;
		case 7:
			(*target).book[i] = '8';
			break;
		case 8:
			(*target).book[i] = '9';
			break;
		case 9:
			(*target).book[i] = '1';
			break;
		case 10:
			(*target).book[i] = 'J';
			break;
		case 11:
			(*target).book[i] = 'Q';
			break;
		case 12:
			(*target).book[i] = 'K';
			break;
		}
		while((*target).card_list->top.rank[0] == (*target).book[i]) {
			foo = (*target).card_list->next;
			free((*target).card_list);
			(*target).card_list = foo;
			(*target).hand_size--;
		}
		while ((*foo).next != NULL) {
			if( (*foo).next->top.rank[0] == (*target).book[i]) {remove_card(target, &(*foo).next->top);}
			else {foo = (*foo).next; }
		}
	}
	return 0;
}
			

/*
 * Function: search
 * ----------------
 *  Search a player's hand for a requested rank.
 *  
 *  rank: the rank to search for
 *  target: the player (and their hand) to search
 *
 *  Return: If the player has a card of that rank, return 1, else return 0
 */
int search(struct player* target, char rank) {
	struct hand* temp = (*target).card_list;
	while (temp != NULL) {
		if ((*temp).top.rank[0] == rank) {return 1;}
		temp = (*temp).next;
	}
	return 0;
}

/*
 * Function: transfer_cards
 * ------------------------
 *   Transfer cards of a given rank from the source player's 
 *   hand to the destination player's hand. Remove transferred
 *   cards from the source player's hand. Add transferred cards
 *   to the destination player's hand.
 *   
 *   src: a pointer to the source player
 *   dest: a pointer to the destination player
 *   rank: the rank to transfer
 *
 *   Return: 0 if no cards found/transferred, <0 if error, otherwise 
 *   return value indicates number of cards transferred
 */   
int transfer_cards(struct player* src, struct player* dest, char rank) {
	int ret = 0;
	struct hand* foo = (*src).card_list;
	struct card* trans;
	while (foo != NULL) {
		if ((*foo).top.rank[0] == rank) {
			trans = &(*foo).top;
			remove_card(src, trans);
			add_card(dest, trans);
			foo = (*src).card_list;
			ret++;
		} else {foo = (*foo).next;}
	}
	return ret;
}

/*
 * Function: game_over
 * -------------------
 *   Boolean function to check if a player has 7 books yet
 *   and the game is over
 *
 *   target: the player to check
 *   
 *   Return: 1 if game is over, 0 if game is not over
 */
int game_over(struct player* target) {
	if ((*target).book[6] != '0') {return 1; }
	return 0;
}

/* 
 * Function: reset_player
 * ----------------------
 *
 *   Reset player by free'ing any memory of cards remaining in hand,
 *   and re-initializes the book.  Used when playing a new game.
 * 
 *   target: player to reset
 * 
 *   Return: 0 if no error, and non-zero on error.
 */
int reset_player(struct player* target) {
	struct hand* curr = (*target).card_list->next;
	struct hand* prev = (*target).card_list;
	while (prev != NULL) {
		free(prev);
		prev = curr;
		if (curr == NULL) {break; }
		curr = (*curr).next;
	}
	free(target);
	memset((*target).book, '0', sizeof((*target).book));
	return 0;
}

/* 
 * Function: computer_play
 * -----------------------
 *
 *   Select a rank randomly to play this turn. The player must have at least
 *   one card of the selected rank in their hand.
 *
 *   target: the player's hand to select from
 *
 *   Rank: return a valid selected rank
 */
char computer_play(struct player* target) {
	return (*target).card_list->top.rank[0];
}

/* 
 * Function: user_play
 * -------------------
 *
 *   Read standard input to get rank user wishes to play.  Must perform error
 *   checking to make sure at least one card in the player's hand is of the 
 *   requested rank.  If not, print out "Error - must have at least one card from rank to play"
 *   and then re-prompt the user.
 *
 *   target: the player's hand to check
 * 
 *   returns: return a valid selected rank
 */
char user_play(struct player* target) {
	char foo;
	printf("Enter a rank: ");
	scanf("%c", &foo);
	while(search(target, foo) != 1) {
		printf("\nError - must have at least one card from rank to play \n");
		printf("Enter a rank: ");
		scanf("%c", &foo);
	}
	return foo;
}
