#include <stdio.h>
#include <stdbool.h>

#include "board.h"
#include "input_output.h"

#ifdef TEST

int main(void)
{
    // printf("\e[1;33m%c\n\e[0m", read_char("A, B, C ou D :", 4, 'A', 'B', 'C', 'D'));

    // read_char("Hello World!", -10);

    int a = 10;
    int b = 20;

    if ((a && b) != -1)
    {
        printf("OK\n");
    }
    else
    {
        print_error("Pas OK\n");
    }

    a = -1;
    b = -1;

    if ((a && b) != -1)
    {
        printf("OK\n");
    }
    else
    {
        print_error("Pas OK\n");
    }

    // direction dir = get_direction();

    // switch (dir)
    // {
    // case NORTH:
    //     printf("NORTH\n");
    //     break;
    // case SOUTH:
    //     printf("SOUTH\n");
    //     break;
    // case EAST:
    //     printf("EAST\n");
    //     break;
    // case WEST:
    //     printf("WEST\n");
    //     break;
    // case GOAL:
    //     printf("GOAL\n");
    //     break;
    // default:
    //     break;
    // }

    // printf("quit : %d", confirm_quit());

    // board game = new_game();

    // for (int i = 0; i < 6; i++)
    // {
    //     place_piece(game, (int)(i / 2) + 1, NORTH_P, i);
    //     place_piece(game, (int)(i / 2) + 1, SOUTH_P, i);
    // }

    // show_board(game);

    // pick_piece(game, NORTH_P, 5, 3);

    // show_board(game);

    // move_piece(game, SOUTH);

    // show_board(game);
}

#else
int main(void)
{
    bool running = true;
    board game = new_game();
    player current = SOUTH_P;

    // The following loop is used to place the players' pieces.
    for (int i = 0; i < 12; i++)
    {
        int column;
        size size_p;
        bool success = false;

        printf("\n\n\e[0;31m%d\e[0m/12\n", i);
        announce_turn(current);
        show_board(game);

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
        change_player(&current);
    }

    printf("Début du jeu\n");

    while (running)
    {
        announce_turn(current);
        show_board(game);

        bool success = false;
        int picked_line;
        int picked_column;
        size picked_size;
        int remaining_moves;

        do
        {
            return_code code;
            picked_line = get_line();
            picked_column = get_column();

            code = pick_piece(game, current, picked_line, picked_column);

            if (code == EMPTY)
            {
                print_error("La case ciblée est vide!");
            }
            else if (code == FORBIDDEN)
            {
                print_error("Vous ne pouvez pas déplacer cette pièce!");
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

        while (movement_left(game) != 0)
        {
            direction dir;
            bool can_move = false;
            do
            {
                show_board(game);
                dir = get_direction();

                can_move = is_move_possible(game, dir);

                if (!can_move)
                {
                    print_error("Vous ne pouvez pas déplacer la pièce dans cette direction !");
                }
            } while (!can_move);

            move_piece(game, dir);

            picked_line = picked_piece_line(game);
            picked_column = picked_piece_column(game);

            remaining_moves--;

            if (remaining_moves == 0 && picked_line != -1 && picked_column != -1)
            {
                size hovered_size = get_piece_size(game, picked_line, picked_column);

                if (hovered_size != NONE)
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
                }
            }
        }

        if(get_winner(game) != NO_PLAYER) {
            running = false;
        }

        change_player(&current);
    }


    player winner = get_winner(game);

    printf("Bravo ");

    if(winner == SOUTH_P) {
        printf("\e[1;33mSUD");
    } else {
		printf("\e[1;34mNORD");
    }
    
    printf(" ! Tu as remporté cette partie !!!🎉");

    return 0;
}
#endif