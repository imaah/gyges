#include <stdlib.h>

#include "board.h"

/**
 * \file board.c
 *
 * \brief Source code associated with \ref board.h
 *
 * \author Guibout & Morisse
 */

/**
 * @brief The board of the game, define it as you wish.
 */

struct board_s {
    size grid[DIMENSION][DIMENSION];
	
	player picked_owner;
	int picked_line;
	int picked_column;

	int south_piece_left[NB_SIZE];
	int north_piece_left[NB_SIZE];
};

void clear_game(board game) {
	for(int i = 0; i < DIMENSION -1; i++) {
		for(int j = 0; j < DIMENSION - 1; j++) {
			(*game).grid[i][j] = NONE;
		}
	}
	(*game).picked_owner = NO_PLAYER;
	(*game).picked_column = -1;
	(*game).picked_line = -1;

	for(int i = 0; i < NB_SIZE; i++) { 
		(*game).north_piece_left[i] = NB_INITIAL_PIECES;
		(*game).south_piece_left[i] = NB_INITIAL_PIECES;
	}
}

board new_game(){ 
	// memory allocation for the board (leave it as is)
	board new_board = malloc(sizeof(struct board_s));
	// TODO: Insérer les traitements que vous voudriez faire.
	clear_game(new_board);
	return new_board;
}

void destroy_game(board game){
	// freeing memory, necessary for memory allocated with malloc (leave as is)
	free(game);
}
