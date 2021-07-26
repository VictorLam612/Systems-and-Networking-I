#include <stdio.h>
#include <string.h>
#include "player.h"
#include "deck.h"
#include "card.h"
#include "gofish.h"


int main(int args, char* argv[]) {
	printf("Computer hand is printed for grading purposes\n");
Start:	printf("shuffling deck...\n\n");
  	shuffle();
	deal_player_cards(&user);
	deal_player_cards(&computer);
	while (1) {	
		printf("User turn: \n");
		print_hand(&user);
		print_book(&user);
		char rank = user_play(&user);
		if (search(&computer, rank) == 1) {
			if (rank == '1') {printf("Computer has %d %c0's \n\n",transfer_cards(&computer, &user, rank), rank);} 
			else {printf("Computer has %d %c's \n\n",transfer_cards(&computer, &user, rank), rank);}
		} else { 
			if (rank == '1') { printf("Computer has no %c0's! Go Fish! \n\n", rank); }
			else {printf("Computer has no %c's! Go Fish! \n\n", rank); }
			deal_cards(&user);
		}
		
		printf("Computer Turn: \n");
		print_hand(&computer);
		print_book(&computer);
		rank = computer_play(&computer);
		if (search(&user, rank) == 1) {
			if (rank == '1') {printf("User has %d %c0's \n \n",transfer_cards(&user, &computer, rank), rank);}
			else {printf("User has %d %c's \n \n",transfer_cards(&user, &computer, rank), rank);}
		} else { 
			printf("User has no %c's! Go Fish! \n \n", rank); 
			deal_cards(&computer);
		}
		
		int prompt = -1;
		if (game_over(&user)) {
			fprintf(stderr, "Congratulations! You beat the computer player. \n");
			prompt = prompt_next();
		} else if (game_over(&computer)) {
			fprintf(stderr, "Sorry! You lose to the computer player \n");
			prompt = prompt_next();
		}
		if (prompt == 0) {goto Finish;}
		else if (prompt == 1) {
			reset_player(&user);
			reset_player(&computer);
			goto Start;
		}
		
	}
Finish:	return 0;
}
