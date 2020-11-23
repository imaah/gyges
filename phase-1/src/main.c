#include <stdio.h>
#include <stdbool.h>

#include "board.h"
#include "input_output.h"

/*
 * Places pieces on the board.
 * 
 * This function is called at the beggining of the game to place the 6 starting pieces of each player on each side
 * of the board. 
 */
void initialize_game(board game, player *p)
{
    player current = *p;

    // The following loop is used to place the players' pieces.
    for (int i = 0; i < 12; i++)
    {
        int column;
        size size_p;
        bool success = false;

        show_board(game);
        printf("\e[0;31m%d\e[0m/12\n", i);
        announce_turn(current);

        // Repeats until the player inputs a correct value
        do
        {
            return_code code;

            column = get_column();
            size_p = get_size();
            code = place_piece(game, size_p, current, column);

            if (code == EMPTY)
            {
                print_error("Une pièce est déjà placée à cet emplacement!");
            }
            else if (code == FORBIDDEN)
            {
                print_error("Vous avez déjà placez toutes vos pièces de cette taille!");
            }
            // Theoritically, this will never be true because params errors are already handled in input_output.c
            else if (code == PARAM)
            {
                print_error("Mauvais paramètre !");
            }
            else
            {
                // The user input is correct so the loop will stop
                success = true;
            }
        } while (!success);

        // It is the next player turn
        current = next_player(current);
    }
    *p = current;
}

/*
 * Picks a piece to move.
 * 
 * This function takes position of a piece on the board and moves it around on the board according to player's choice.
 */
int get_piece(board game, player current)
{
    bool success = false;
    int picked_line;
    int picked_column;
    size picked_size;
    
    // Getting the position of the piece, and looping through error code until there is none
    do
    {
        return_code code;
        picked_line = get_line();
        picked_column = get_column();

        code = pick_piece(game, current, picked_line, picked_column);

        if (code == EMPTY)
        {
            print_error("La case ciblée est vide !");
        }
        else if (code == FORBIDDEN)
        {
            print_error("Vous ne pouvez pas déplacer cette pièce !");
        }
        // Theoritically, this will never be true
        else if (code == PARAM)
        {
            print_error("Mauvais paramètre!");
        }
        // If no error, it's a success
        else
        {
            picked_size = picked_piece_size(game);
            success = true;
        }

    } while (!success);

    // Returns the correctly picked piece size
    return picked_size;
}

/* 
 * Asks if the player wants to swap the piece or continue moving.
 * 
 * If the player's last move of a piece happens to be on the same cell of another cell, he can etheir swap his
 * piece with the other one, or continue moving his current one. This function asks him which action he wants to do.
 */
void ask_action(board game, int *rmoves, size hovered_size)
{
    action ac = get_action();

    // If the player wants to swap, ask him with which piece
    if (ac == SWAP)
    {
        bool swapped = false;

        // Regular error handling, to avoid trying to swap with non-existing pieces
        do
        {
            int swap_line = get_line();
            int swap_column = get_column();

            return_code code = swap_piece(game, swap_line, swap_column);

            if (code == EMPTY)
            {
                print_error("Vous ne pouvez pas échanger les pièces pour le moment !");
            }
            else if (code == FORBIDDEN)
            {
                print_error("L'emplacement ciblé n'est pas libre !");
            }
            // Theoritically, this will never be true
            else if (code == PARAM)
            {
                print_error("Mauvais paramètre !");
            }
            else
            {
                // The user input is correct so the loop will stop
                swapped = true;
            }
        } while (!swapped);
    }
    // If he does not want to swap, he must want to move again
    else
    {
        *rmoves += hovered_size;
    }
}

/**
 * Moves pieces around the board.
 * 
 * This function is used once all parameters are correct, and the picked piece can be moved.
 */
bool play(board game, int *rmoves)
{
    // Looping until there is no move left
    while (*rmoves != 0)
    {
        direction dir;
        bool can_move = false;
        
        // Showing how many moves are left
        do
        {
            show_board(game);

            if (*rmoves > 1)
            {
                printf("[\e[1;31m%d\e[0m déplacements restants]\n", *rmoves);
            }
            else
            {
                printf("[\e[1;31m%d\e[0m déplacement restant]\n", *rmoves);
            }

            // Asking the player in which direction he wants to play
            dir = get_direction();
            
            // Handling if the chosen direction is not existing
            if (dir == -1)
            {
                cancel_type type = get_cancel_type();

                if (type == STEP)
                {
                    cancel_step(game);
                    (*rmoves)++;
                }
                else
                {
                    cancel_movement(game);
                    return true;
                }
            }
            // If the chosen direction is possible, check if it's doable
            else
            {
                can_move = is_move_possible(game, dir);

                if (!can_move)
                {
                    print_error("Vous ne pouvez pas déplacer la pièce dans cette direction !");
                }
            }
        } while (!can_move);

        // If everyting is good, move the piece
        move_piece(game, dir);

        int picked_line = picked_piece_line(game);
        int picked_column = picked_piece_column(game);

        // After moving, substracting one move to the total
        (*rmoves)--;

        if (*rmoves == 0 && picked_line != -1 && picked_column != -1)
        {
            size hovered_size = get_piece_size(game, picked_line, picked_column);

            if (hovered_size != NONE)
            {
                ask_action(game, rmoves, hovered_size);
            }
        }
    }

    return false;
}

/**
 * This function starts a new game turn.
 * 
 * Each time a move ends because a player has no option left, this function is called to show the board, tell
 * the next player that it's his name to play and switch the player enum to the next element.
 * If the game has a winner, the function returns false to tell the main function that we have a winner.
 */
bool game_turn(board game, player *current)
{   
    show_board(game);
    announce_turn(*current);

    int remaining_moves = get_piece(game, *current);
    bool cancelled = play(game, &remaining_moves);

    // If everything went fine, check if we have a winner
    if (cancelled == false)
    {
        if (get_winner(game) != NO_PLAYER)
        {
            return false;
        }

        *current = next_player(*current);
    }

    return true;
}

/**
 * Main loop of the game.
 * 
 * This function acts as the main loop of the game. It calls one after another each important function to the
 * effective conduct of the game.
 */
int main(void)
{
    // Running the game until we have a winner
    bool running = true;
    board game = new_game();
    player current = SOUTH_P;

    // Initializing the game by placing 6 pieces for each player
    initialize_game(game, &current);

    printf("Début du jeu\n");

    // While we have no winner, we go on a new game turn
    while (running)
    {
        running = game_turn(game, &current);
    }

    // If we have a winner, we announce it and we stop the game
    announce_winner(game);

    destroy_game(game);

    return 0;
}
