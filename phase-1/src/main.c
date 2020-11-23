#include <stdio.h>
#include <stdbool.h>

#include "board.h"
#include "input_output.h"

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
            // Theoritically, this will never be true
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

int get_piece(board game, player current)
{
    bool success = false;
    int picked_line;
    int picked_column;
    size picked_size;

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
        else
        {
            picked_size = picked_piece_size(game);
            success = true;
        }

    } while (!success);

    return picked_size;
}

void ask_action(board game, int *rmoves, size hovered_size)
{
    action ac = get_action();

    if (ac == SWAP)
    {
        bool swapped = false;

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
    else
    {
        *rmoves += hovered_size;
    }
}

bool play(board game, int *rmoves)
{
    while (*rmoves != 0)
    {
        direction dir;
        bool can_move = false;
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

            dir = get_direction();
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
            else
            {
                can_move = is_move_possible(game, dir);

                if (!can_move)
                {
                    print_error("Vous ne pouvez pas déplacer la pièce dans cette direction !");
                }
            }
        } while (!can_move);

        move_piece(game, dir);

        int picked_line = picked_piece_line(game);
        int picked_column = picked_piece_column(game);

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

bool game_turn(board game, player *current)
{   
    show_board(game);
    announce_turn(*current);

    int remaining_moves = get_piece(game, *current);
    bool cancelled = play(game, &remaining_moves);

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

int main(void)
{
    bool running = true;
    board game = new_game();
    player current = SOUTH_P;

    initialize_game(game, &current);

    printf("Début du jeu\n");

    while (running)
    {
        running = game_turn(game, &current);
    }

    announce_winner(game);

    destroy_game(game);

    return 0;
}
