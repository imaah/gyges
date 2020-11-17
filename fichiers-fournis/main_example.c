#include <stdio.h>
#include "board.h"

/**
 * @file main_example.c
 * @brief a simple illustration of how to include and use board.h and board.o.
 * @author Dorbec
 */
int main(int args, char **argv){
	board game = new_game();
	printf("Un plateau est créé.\n");
	int res = place_piece(game, THREE, SOUTH_P, 2);
	if(res == OK){
		printf("La piece a été placée avec succès.\n");
	}
	else {
		printf("Un problème a eu lieu lors du plac&azaement, numéro %d\n", res);
	}
	destroy_game(game);
	printf("suppression du plateau et sortie\n");	
	return 0;
}

