#include <stdio.h>
#include <stdbool.h>

#include "board.h"
#include "input_output.h"

#ifdef TEST

int main(void)
{
    board game = new_game();

    for(int i = 0; i < 6; i++) {
        place_piece(game, (int) (i / 2) + 1, NORTH_P, i);
        place_piece(game, (int) (i / 2) + 1, SOUTH_P, i);
    }

    show_board(game);

    pick_piece(game, NORTH_P, 5, 3);

    show_board(game);

    move_piece(game, SOUTH);

    show_board(game);
}

#else
int main(void)
{
    bool running = true;
    board game = new_game();
    player current = SOUTH_P;
    
    for(int i = 0; i < 12; i++) {
        int column;
        size size_p;
        bool success = false;

        printf("\n\n\e[0;31m%d\e[0m/12\n", i);
        announce_turn(current);
        show_board(game);
        
        do {
            return_code code;

            column = get_column();
            size_p = get_size();
            code = place_piece(game, size_p, current, column);

            if(code == EMPTY) {
                print_error("Une pièce est déjà placée à cet emplacement!");
            } else if(code == FORBIDDEN) {
                print_error("Vous avez déjà placez toutes vos pièces de cette taille!");
            } else if(code == PARAM) {
                print_error("Mauvais paramètre !");
            } else {
                success = true;
            }
        } while(!success);
        
        change_player(&current);
    }

    printf("Début du jeu\n");

    while(running) {
        announce_turn(current);
        show_board(game);
        direction dir;
        
        bool success = false;
        int picked_line;
        int picked_column;

        do {
            return_code code;
            picked_line = get_line();
            picked_column = get_column();

            code = pick_piece(game, current, picked_line, picked_column);

            if(code == EMPTY) {
                print_error("La case ciblée est vide!");
            } else if(code == FORBIDDEN) {
                print_error("Vous ne pouvez pas déplacer cette pièce!");
            } else if(code == PARAM) {
                print_error("Mauvais paramètre!");
            } else {
                success = true;
            }
        } while(!success);



        do {
            dir = get_direction();
        } while (!is_move_possible(game, dir));

    }

    return 0;
}
#endif