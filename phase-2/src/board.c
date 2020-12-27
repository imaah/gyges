#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "board.h"

/**
 *\file board.c
 *
 *\brief Source code associated with \ref board.h
 *
 *\author Guibout &Morisse
 */

/**
 *@brief The board of the game, define it as you wish.
 */

struct board_s
{
	size grid[DIMENSION][DIMENSION];

	player picked_owner;
	int picked_line;
	int picked_column;
	size picked_size;

	bool south_goal_occupied;
	bool north_goal_occupied;

	int origin_line;
	int origin_column;

	int movement_left;

	direction moves[3];

	int pieces_left[NB_PLAYERS][NB_SIZE];
};

void clear_game(board game)
{
	for (int i = 0; i < DIMENSION - 1; i++)
	{
		for (int j = 0; j < DIMENSION - 1; j++)
		{
			game->grid[i][j] = NONE;
		}
	}

	// Reseting all variables to default values
	game->picked_owner = NO_PLAYER;
	game->picked_column = -1;
	game->picked_line = -1;
	game->picked_size = NONE;

	game->south_goal_occupied = false;
	game->north_goal_occupied = false;

	game->movement_left = 0;

	for (int i = 0; i < 3; i++)
	{
		game->moves[i] = -1;
	}

	game->origin_line = -1;
	game->origin_column = -1;

	for (int i = 0; i < NB_SIZE; i++)
	{
		game->pieces_left[SOUTH_P - 1][i] = NB_INITIAL_PIECES;
		game->pieces_left[NORTH_P - 1][i] = NB_INITIAL_PIECES;
	}
}

board new_game()
{
	// memory allocation for the board (leave it as is)
	board new_board = malloc(sizeof(struct board_s));
	clear_game(new_board);
	return new_board;
}

board copy_game(board game)
{
	board copy = new_game(game);

	for (int i = 0; i < DIMENSION - 1; i++)
	{
		for (int j = 0; j < DIMENSION - 1; j++)
		{
			copy->grid[i][j] = game->grid[i][j];
		}
	}

	// Copying all variables from the original board to the copy
	copy->picked_owner = game->picked_owner;
	copy->picked_column = game->picked_column;
	copy->picked_line = game->picked_line;
	copy->picked_size = game->picked_size;

	copy->south_goal_occupied = game->south_goal_occupied;
	copy->north_goal_occupied = game->north_goal_occupied;

	copy->movement_left = game->movement_left;

	for (int i = 0; i < 3; i++)
	{
		copy->moves[i] = game->moves[i];
	}

	copy->origin_line = game->origin_line;
	copy->origin_column = game->origin_column;

	for (int i = 0; i < NB_SIZE; i++)
	{
		copy->pieces_left[SOUTH_P - 1][i] = game->pieces_left[SOUTH_P - 1][i];
		copy->pieces_left[NORTH_P - 1][i] = game->pieces_left[NORTH_P - 1][i];
	}

	return copy;
}

void destroy_game(board game)
{
	// freeing memory, necessary for memory allocated with malloc (leave as is)
	free(game);
}

bool in_board(int line, int column)
{
	if (0 <= line && line <= DIMENSION - 1)
	{
		if (0 <= column && column <= DIMENSION - 1)
		{
			// If in board, return true
			return true;
		}
	}

	return false;
}

size get_piece_size(board game, int line, int column)
{
	if (!in_board(line, column))
	{
		return NONE;
	}

	// Return the piece's size if it's in board
	return game->grid[line][column];
}

player get_winner(board game)
{
	if (game->north_goal_occupied)
	{
		return SOUTH_P;
	}
	else if (game->south_goal_occupied)
	{
		return NORTH_P;
	}

	// Returning no player if there is no winner this turn
	return NO_PLAYER;
}

int southmost_occupied_line(board game)
{
	for (int line = 0; line < DIMENSION; line++)
	{
		for (int column = 0; column < DIMENSION; column++)
		{
			if (get_piece_size(game, line, column) != NONE)
			{
				return line;
			}
		}
	}
	return -1;
}

int northmost_occupied_line(board game)
{
	for (int line = DIMENSION - 1; line >= 0; line--)
	{
		for (int column = 0; column < DIMENSION; column++)
		{
			if (get_piece_size(game, line, column) != NONE)
			{
				return line;
			}
		}
	}

	return -1;
}

player picked_piece_owner(board game)
{
	return game->picked_owner;
}

size picked_piece_size(board game)
{
	return game->picked_size;
}

int picked_piece_line(board game)
{
	return game->picked_line;
}

int picked_piece_column(board game)
{
	return game->picked_column;
}

int movement_left(board game)
{
	return game->movement_left;
}

int nb_pieces_available(board game, size piece, player player)
{
	if (player == NO_PLAYER)
	{
		return -1;
	}

	return game->pieces_left[player - 1][piece - 1];
}

return_code place_piece(board game, size piece, player current_player, int column)
{
	int line;

	if (current_player == NORTH_P)
	{
		line = 5;
	}
	else if (current_player == SOUTH_P)
	{
		line = 0;
	}
	else
	{
		return PARAM;
	}

	// If the piece size is not a valid size or the coordinates are not correct return PARAM code
	if (!(0 < piece && piece <= NB_SIZE) || !in_board(line, column))
	{
		return PARAM;
	}
	// if the position is not empty return EMPTY code
	else if (get_piece_size(game, line, column) != NONE)
	{
		return EMPTY;
	}
	// if the playe has not enough pieces left
	else if (nb_pieces_available(game, piece, current_player) == 0)
	{
		return FORBIDDEN;
	}

	game->grid[line][column] = piece;
	game->pieces_left[current_player - 1][piece - 1]--;

	return OK;
}

return_code pick_piece(board game, player current_player, int line, int column)
{
	size piece_size = get_piece_size(game, line, column);

	// If it's not in board or no player is currently playing, then its a PARAM error
	if (!in_board(line, column) || current_player == NO_PLAYER)
	{
		return PARAM;
	}

	// If there is no piece inside the cell, return EMPTY code 
	if (piece_size == NONE)
	{
		return EMPTY;
	}

	// Checking if line is the correct one according to the current player 
	if (current_player == SOUTH_P)
	{
		if (southmost_occupied_line(game) != line)
		{
			return FORBIDDEN;
		}
	}
	else
	{
		if (northmost_occupied_line(game) != line)
		{
			return FORBIDDEN;
		}
	}

	// If there is a winner, return FORBIDDEN code
	if (get_winner(game) != NO_PLAYER)
	{
		return FORBIDDEN;
	}

	// Picking the piece
	game->picked_line = line;
	game->picked_column = column;
	game->picked_size = piece_size;
	game->picked_owner = current_player;
	game->origin_line = line;
	game->origin_column = column;
	game->movement_left = piece_size;
	game->grid[line][column] = NONE;

	return OK;
}

player next_player(player current_player)
{
	if (current_player == SOUTH_P)
	{
		return NORTH_P;
	}

	return SOUTH_P;
}

/**
 *@brief A function that returns the movement of a piece according to a direction
 * 
 *@param dir the direction
 * 
 *@returns the pointer to an array of 2 numbers : {y, x}. If the direction is GOAL or not valid the function will return {0, 0}
 **/
int *move(direction dir)
{
	static int movement[2];

	// Acts like in a dual axis plan
	switch (dir)
	{
		case NORTH:
			movement[0] = 1;
			movement[1] = 0;
			break;
		case SOUTH:
			movement[0] = -1;
			movement[1] = 0;
			break;
		case EAST:
			movement[0] = 0;
			movement[1] = 1;
			break;
		case WEST:
			movement[0] = 0;
			movement[1] = -1;
			break;
		default:
			movement[0] = 0;
			movement[1] = 0;
			break;
	}

	return movement;
}

bool is_move_possible(board game, direction direction)
{
	int line = picked_piece_line(game);
	int column = picked_piece_column(game);

	int *dir = move(direction);

	if (direction == GOAL)
	{
		// If the north player is not trying to go in his own goal and he can move...
		if (picked_piece_owner(game) == NORTH_P && line == 0 && movement_left(game) == 1)
		{
			return true;
		}
		// Also checking for the south player
		else if (picked_piece_owner(game) == SOUTH_P && line == 5 && movement_left(game) == 1)
		{
			return true;
		}
	}

	// If the player is not trying to do a winning move, it's a regular one
	else if (in_board(line + dir[0], column + dir[1]))
	{
		if (picked_piece_size(game) == ONE || movement_left(game) == 1)
		{
			return true;
		}
		else if (get_piece_size(game, line + dir[0], column + dir[1]) == NONE)
		{
			return true;
		}
	}

	return false;
}

void reset_game_move(board game)
{
	// Reseting piece's related variables to what they were before the move
	game->grid[picked_piece_line(game)][picked_piece_column(game)] = picked_piece_size(game);
	game->picked_line = -1;
	game->picked_column = -1;
	game->picked_owner = NO_PLAYER;
	game->picked_size = NONE;
	game->origin_line = -1;
	game->origin_column = -1;

	for (int i = 0; i < 3; i++)
	{
		game->moves[i] = -1;
	}
}

return_code move_piece(board game, direction direction)
{
	int *dir = move(direction);

	// Checking all possible errors to throw before moving the piece
	if (picked_piece_owner(game) == NO_PLAYER)
	{
		return EMPTY;
	}

	if (!in_board(picked_piece_line(game) + dir[0], picked_piece_column(game) + dir[1]))
	{
		return PARAM;
	}

	if (!is_move_possible(game, direction))
	{
		return FORBIDDEN;
	}

	if (direction == GOAL)
	{
		if (picked_piece_owner(game) == NORTH_P)
		{
			game->south_goal_occupied = true;
		}
		else
		{
			game->north_goal_occupied = true;
		}
	}

	game->picked_line += dir[0];
	game->picked_column += dir[1];

	game->movement_left--;

	for (int i = 0; i < 3; i++)
	{
		if (game->moves[i] == -1)
		{
			game->moves[i] = direction;
			break;
		}
	}

	if (game->movement_left == 0)
	{
		size hovered_size = get_piece_size(game, picked_piece_line(game), picked_piece_column(game));

		if (hovered_size == NONE)
		{
			reset_game_move(game);
		}
		else
		{
			game->movement_left += hovered_size;
		}
	}

	return OK;
}

return_code cancel_movement(board game)
{
	// If there is no player that is moving a piece the function will return EMPTY code
	if (picked_piece_owner(game) == NO_PLAYER)
	{
		return EMPTY;
	}

	// Putting the piece back to its position
	game->picked_line = game->origin_line;
	game->picked_column = game->origin_column;

	reset_game_move(game);

	return OK;
}

return_code cancel_step(board game)
{
	if (picked_piece_owner(game) == NO_PLAYER)
	{
		return EMPTY;
	}

	int last = -4;

	for (int i = 0; i < 3; i++)
	{
		if (game->moves[i] == -1)
		{
			last = i - 1;
			break;
		}
	}

	if (last != -4)
	{
		// Going one step back
		direction last_move_direction = game->moves[last];
		int *dir = move(last_move_direction);

		game->moves[last] = -1;
		game->picked_line += -dir[0];
		game->picked_column += -dir[1];
	}

	return OK;
}

return_code swap_piece(board game, int target_line, int target_column)
{
	if (picked_piece_owner(game) == NO_PLAYER)
	{
		return FORBIDDEN;
	}

	size hovered_size = get_piece_size(game, picked_piece_line(game), picked_piece_column(game));

	if (!in_board(target_line, target_column))
	{
		return PARAM;
	}

	if (hovered_size == NONE)
	{
		return EMPTY;
	}

	size target_size = get_piece_size(game, target_line, target_column);

	if (target_size != NONE)
	{
		return FORBIDDEN;
	}

	game->grid[target_line][target_column] = hovered_size;

	reset_game_move(game);

	return OK;
}
