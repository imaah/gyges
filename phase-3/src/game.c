#include <stdbool.h>
#include <stdio.h>

#include "board.h"
#include "game.h"
#include "input_output.h"


void ini_select_spot(Env *env, int line, int column) {
    if(get_piece_size(env->game, line, column) == NONE) {

        if((env->current_player == NORTH_P && line != 5) || (env->current_player == SOUTH_P && line != 0)) {
            env->err_msg = "Emplacement non-valide !";
            env->err_showtime = ERR_SHOWTIME;
        } else {
            env->current_state = INI_SELECT_SIZE;
            env->selected_column = column;
            env->err_showtime = 0;
        }

    } else {
        env->err_msg = "Emplacement non-vide !";
        env->err_showtime = ERR_SHOWTIME;
    }
}

void ini_select_size(Env *env, size chosen_size) {

}

void mid_select_spot(Env * env, int line, int column)
{
    if (get_piece_size(env->game, line, column) != NONE)
    {
        if ((env->current_player == NORTH_P && line == northmost_occupied_line(env->game)) || (env->current_player == SOUTH_P && line == southmost_occupied_line(env->game)))
        {
            env->picked_piece_line = line;
            env->picked_piece_column = column;
            env->picked_piece_size = get_piece_size(env->game, env->picked_piece_line, env->picked_piece_column);
            env->remaining_moves = env->picked_piece_size;
        }
        else
        {
            env->err_msg = "Choississez une de vos pièces";
            env->err_showtime = ERR_SHOWTIME;
        }
    }
    else
    {
        env->err_msg = "Choississez plutôt une pièce";
        env->err_showtime = ERR_SHOWTIME;
    }
}

void handle_click(Env *env, int line, int column) {

    if(env->current_state == INI_SELECT_SPOT) {
        ini_select_spot(env, line, column);
    }

    /*// If the game is its initialization phase
    if (game_state == INI_PLACE)
    {
        if (current_player == NORTH_P)
        {

        }
        else if (currect_player == SOUTH_P)
        {

        }
        else
        {
            print_error("Ce n'est à aucun joueur de jouer!");
        }

        // Changer le gamestate
    }*/
}


void initialize_game(board game, player *player_p)
{
    player current = SOUTH_P;

    // The following loop is used to place the players' pieces.
    for (int i = 0; i < 12; i++)
    {
        int column;
        size size_p;
        bool success = false;

        show_board(game);
        printf("\033[0;31m%d\033[0m/12\n", i);
        announce_turn(current);

        printf("[");

        for (int i = 0; i < NB_SIZE; i++)
        {
            int available = nb_pieces_available(game, i + 1, current);

            printf("\033[0;36m%d\033[0m : \033[1;32m%d\033[0m restante", i + 1, available);

            if (available > 1)
            {
                printf("s");
            }

            if (i < NB_SIZE - 1)
            {
                printf(" ; ");
            }
        }

        printf("]\n\n");

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
            // Theoritically, this will never be true because params errors are already handled in input_output.h
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
    *player_p = current;
}

size choose_piece(board game, player current_player)
{
    bool success = false;
    int picked_line;
    int picked_column;
    size picked_size;

    // Getting the position of the piece, and looping through error code until there is none
    do
    {
        return_code code;
        if (current_player == SOUTH_P)
        {
            picked_line = southmost_occupied_line(game);
        }
        else
        {
            picked_line = northmost_occupied_line(game);
        }
        printf("Vous jouez sur la ligne \033[1;33m%d\033[0m\n", picked_line + 1);

        // Reseting the total piece in a row to 0
        int placed_piece = 0;
        // Looping through all the cells of the row to check if there is more than 1 piece
        for (int i = 0; i < DIMENSION; i++)
        {
            // If there is a piece, increment the counter
            if (get_piece_size(game, picked_line, i) != NONE)
            {
                placed_piece++;
                picked_column = i;
            }
        }

        // If there is only one piece in the row, auto-pick
        if (placed_piece > 1)
        {
            picked_column = get_column();
        }
        else
        {
            printf("Puisqu'il n'y avait qu'une seule pièce dans la ligne la plus proche de votre camp, elle à été selectionnée\n");
        }

        code = pick_piece(game, current_player, picked_line, picked_column);

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

void ask_action(board game, int *remaining_moves, size hovered_size)
{
    bool confirmed = false;

    do
    {
        action ac = get_action();

        if (ac == SWAP)
        {
            bool swapped = false;

            if (confirm_swap())
            {
                confirmed = true;
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
        }
        // If he does not want to swap, he must want to move again
        else
        {
            if (confirm_continue())
            {
                *remaining_moves += hovered_size;
                confirmed = true;
            }
        }
    } while (!confirmed);

    // If the player wants to swap, ask him with which piece
}

bool play(board game, int *remaining_moves_p)
{
    // Looping until there is no move left
    int move_done = 0;
    while (*remaining_moves_p != 0)
    {
        int dir;
        bool can_move = false;

        show_board(game);

        // Showing how many moves are left
        if (*remaining_moves_p > 1)
        {
            printf("[\033[1;31m%d\033[0m déplacements restants]\n", *remaining_moves_p);
        }
        else
        {
            printf("[\033[1;31m%d\033[0m déplacement restant]\n", *remaining_moves_p);
        }

        do
        {
            // Asking the player in which direction he wants to play
            dir = get_direction();

            // Handling if the chosen direction is not existing
            if (dir == -1)
            {
                cancel_type type = get_cancel_type();

                if (type == STEP)
                {
                    if (move_done == 0)
                    {
                        cancel_movement(game);
                        return true;
                    }
                    else
                    {
                        cancel_step(game);
                        (*remaining_moves_p)++;
                        move_done--;
                    }
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
        (*remaining_moves_p)--;
        move_done++;

        if (*remaining_moves_p == 0 && picked_line != -1 && picked_column != -1)
        {
            size hovered_size = get_piece_size(game, picked_line, picked_column);

            if (hovered_size != NONE)
            {
                ask_action(game, remaining_moves_p, hovered_size);
            }
        }
    }

    return false;
}

bool game_turn(board game, player *current_player)
{
    show_board(game);
    announce_turn(*current_player);

    int remaining_moves = choose_piece(game, *current_player);
    bool cancelled = play(game, &remaining_moves);

    // If everything went fine, check if we have a winner
    if (cancelled == false)
    {
        if (get_winner(game) != NO_PLAYER)
        {
            return false;
        }

        *current_player = next_player(*current_player);
    }

    return true;
}