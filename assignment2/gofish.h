#ifndef GOFISH_H
#define GOFISH_H
#include <stdio.h>

/*
   Define any prototype functions
   for gofish.h here.
*/

int prompt_next() {
char foo;
printf("Do you want to play again [Y/N]: ");
scanf("%c", &foo);
if(foo == 'Y') {return 1;}
else {return 0;}
}

void print_hand(struct player* target) {
	printf("Player's Hand: ");
	struct hand* temp = (*target).card_list;
	while (temp != NULL) {
		if((*temp).top.rank[0] == '1') {
			printf("10%c ", (*temp).top.suit);
		} else {
			printf("%s%c ", (*temp).top.rank, (*temp).top.suit);
		}
		temp = (*temp).next;
	}
	printf("\n");
}

void print_book(struct player* target) {
	printf("Book: ");
	for (int i = 0; i < 7; i++) {
		if ((*target).book[i] != '0') {
			printf("%c ", (*target).book[i]);
		}
	}
	printf("\n");
}

#endif
