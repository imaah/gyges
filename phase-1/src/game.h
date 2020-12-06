#ifndef _GAME_H_
#define _GAME_H_

#include "board.h"

/**
 * \file game.h
 *
 * \brief Gyges game function.
 *
 * In this file, all the functions for the game loop
 *  
 * \author Morisse & Guibout
 *
 */


/**
 * @brief Places pieces on the board.
 * 
 * This function is called at the beggining of the game to place the 6 starting pieces of each player on each side
 * of the board. 
 * 
 * @param game the current game to use
 * @param player_p a pointer to a player
 */
void initialize_game(board game, player *p);

/**
 * @brief Chooses the piece to pick.
 * 
 * This function takes position of a piece on the board and picks it.
 * 
 * @param game the current game to use
 * @param current_player the current player that have to place a piece
 * 
 * @returns the size of the picked piece
 */
int get_piece(board game, player current);

/** 
 * @brief Asks if the player wants to swap the piece or continue moving.
 * 
 * If the player's last move of a piece happens to be on the same cell of another cell, he can etheir swap his
 * piece with the other one, or continue moving his current one. This function asks him which action he wants to do.
 * 
 * @param game the current game to use
 * @param rmoves a pointer to the remaining moves
 * @param hovered_size the size of the hovered piece
 */
void ask_action(board game, int *remaining_moves, size hovered_size);

/**
 * @brief Moves pieces around the board.
 * 
 * This function is used once all parameters are correct, and the picked piece can be moved.
 * 
 * @param game the current game to use
 * @param rmoves a pointer to the remaining moves
 * 
 * @returns whether the move is cancelled
 */
bool play(board game, int *rmoves);

/**
 * @brief This function starts a new game turn.
 * 
 * Each time a move ends because a player has no option left, this function is called to show the board, tell
 * the next player that it's his name to play and switch the player enum to the next element.
 * If the game has a winner, the function returns false to tell the main function that we have a winner.
 * 
 * @param game the current game to use
 * @param current_player a pointer to the current player that will play
 * 
 * @returns whether the game is won by a player or not
 */
bool game_turn(board game, player *current);

#endif