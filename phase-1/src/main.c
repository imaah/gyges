#include <stdio.h>
#include <stdbool.h>

#include "board.h"
#include "input_output.h"

#ifdef TEST

int main(void)
{
    direction dir = read_dir_char("(N/S/E/O), l'arrivée (B)");

    printf("%d", dir);

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
                print_error("Mauvais paramètre!");
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

        direction dir = NORTH;
        
        do {



        } while (!is_move_possible(game, dir));

    }

    return 0;
}
#endif