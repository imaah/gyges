#include <stdio.h>
#include <stdbool.h>

#include "board.h"
#include "input_output.h"

#ifdef DEBUG

int main(void)
{
    board game = new_game();

    place_piece(game, TWO, SOUTH_P, 5);
    place_piece(game, THREE, NORTH_P, 1);

    show_board(game);

    return 0;
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

        printf("%d/12\n", i);
        announce_turn(current);
        show_board(game);
        
        do {
            return_code code;

            printf("Choisissez une colonne (entre 1 et 6)");
            column = get_column();
            size_p = get_size();
            code = place_piece(game, size_p, current, column);

            if(code == EMPTY) {
                print_error("Une pièce est déjà placée à cet emplacement!");
            } else if(code == FORBIDDEN) {
                print_error("Vous avez déjà placez toutes vos pièces de cette taille!");
            } else {
                success = true;
            }
        } while(!success);
        
        change_player(&current);
    }

    printf("Début du jeu\n");

    while(running) {
        show_board(game);
        announce_turn(current);

        direction dir = NORTH;
        
        do {



        } while (!is_move_possible(game, dir));

    }

    return 0;
}
#endif