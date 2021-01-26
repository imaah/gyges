#include <stdbool.h>
#include <stdio.h>

#include "board.h"
#include "game.h"

void ini_select_spot(Env *env, int line, int column)
{
    if (!in_board(line, column))
    {
        return;
    }
    if (get_piece_size(env->game, line, column) == NONE)
    {
        if ((env->current_player == NORTH_P && line != 5) || (env->current_player == SOUTH_P && line != 0))
        {
            env->err_msg = "Emplacement non-valide !";
            env->err_showtime = ERR_SHOWTIME;
        }
        else
        {
            env->current_state = INI_SELECT_SIZE;
            env->selected_column = column;
            env->err_showtime = 0;
        }
    }
    else
    {
        env->err_msg = "Emplacement non-vide !";
        env->err_showtime = ERR_SHOWTIME;
    }
}

void ini_select_size(Env *env, size chosen_size)
{
    return_code code = place_piece(env->game, chosen_size, env->current_player, env->selected_column);

    if (code == EMPTY)
    {
        env->err_msg = "Une pièce est déjà sur cette case";
        env->err_showtime = ERR_SHOWTIME;
    }
    else if (code == FORBIDDEN)
    {
        env->err_msg = "Vous n'avez plus de pièces de cette taille";
        env->err_showtime = ERR_SHOWTIME;
    }
    // Theoritically, this will never be true because PARAMs errors are already handled in input_output.c
    else if (code == PARAM)
    {
        env->err_msg = "Cliquez sur une des cases du plateau";
        env->err_showtime = ERR_SHOWTIME;
    }
    else
    {
        env->placed_piece++;
        if (env->placed_piece < 12)
        {
            env->current_state = INI_SELECT_SPOT;
        }
        else
        {
            env->current_state = MID_SELECT_PIECE;
        }

        env->current_player = next_player(env->current_player);
    }
}

void mid_select_piece(Env *env, int line, int column)
{
    if (get_piece_size(env->game, line, column) != NONE)
    {
        if ((env->current_player == NORTH_P && line == northmost_occupied_line(env->game)) || (env->current_player == SOUTH_P && line == southmost_occupied_line(env->game)))
        {
            pick_piece(env->game, env->current_player, line, column);
            env->current_state = MID_MOVE_PIECE;
            env->moves_made = 0;
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

void mid_move_piece(Env *env, int line, int column)
{
    direction dir;
    int picked_line = picked_piece_line(env->game);
    int picked_column = picked_piece_column(env->game);

    // Looping through all possible directions (GOAL:0, NORTH:1, ...)

    for (int possible_direction = 0; possible_direction < 5; possible_direction++)
    {
        int *mv = move(possible_direction);

        if (possible_direction == GOAL)
        {
            if ((column == 2 || column == 3) && ((env->current_player == NORTH_P && line == -1) || (env->current_player == SOUTH_P && line == 6)))
            {
                if (is_move_possible(env->game, GOAL))
                {
                    move_piece(env->game, GOAL);
                    env->current_state = VICTORY;
                    return;
                }
            }
        }
        else if (line - picked_line == mv[0] && column - picked_column == mv[1])
        {
            dir = possible_direction;
            if (is_move_possible(env->game, dir))
            {
                move_piece(env->game, dir);

                picked_line = picked_piece_line(env->game);
                picked_column = picked_piece_column(env->game);
                env->moves_made++;

                if (movement_left(env->game) == -1)
                {
                    env->current_state = MID_SELECT_PIECE;
                    env->current_player = next_player(env->current_player);
                }
                else
                {
                    size s = get_piece_size(env->game, picked_line, picked_column);

                    if (s != NONE)
                    {
                        env->current_state = MID_SELECT_ACTION;
                    }
                }
            }
            return;
        }
    }
}

void mid_select_action(Env *env, action action)
{
    if (action == SWAP)
    {
        env->current_state = MID_SWAP_PIECE;
    }
    else if (action == CONTINUE)
    {
        env->current_state = MID_MOVE_PIECE;
    }
}

void mid_swap_piece(Env *env, int line, int column)
{
    if (!in_board(line, column))
    {
        return;
    }
    return_code code = swap_piece(env->game, line, column);

    if (code == EMPTY)
    {
        env->err_msg = "Vous ne pouvez pas échanger les pièces pour le moment !";
        env->err_showtime = ERR_SHOWTIME;
    }
    else if (code == FORBIDDEN)
    {
        env->err_msg = "La case n'est pas vide !";
        env->err_showtime = ERR_SHOWTIME;
    }
    // Theoritically, this will never be true
    else if (code == PARAM)
    {
        env->err_msg = "La case n'est pas valide !";
        env->err_showtime = ERR_SHOWTIME;
    }
    {
        env->current_state = MID_SELECT_PIECE;
        env->current_player = next_player(env->current_player);
    }
}

void handle_click(Env *env, int line, int column)
{

    switch (env->current_state)
    {
    case INI_SELECT_SPOT:
        ini_select_spot(env, line, column);
        break;
    case MID_SELECT_PIECE:
        mid_select_piece(env, line, column);
        break;
    case MID_MOVE_PIECE:
        mid_move_piece(env, line, column);
        break;
    case MID_SWAP_PIECE:
        mid_swap_piece(env, line, column);
        break;
    default:
        break;
    }
}