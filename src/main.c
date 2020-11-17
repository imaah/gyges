#include <stdio.h>
#include <stdbool.h>
#include "board.h"
#include "input_output.h"

int main(void)
{
    bool running = true;
    board game = new_game();
    player current = SOUTH_P;
    
    for(int i = 0; i < 12; i++) {
        int column, line;
        size size_p, piece;

        printf("%d/12", i);
        announce_turn(current);
        show_board(game);

        if(current == SOUTH_P) {
            line = 1;
        } else if (current == NORTH_P) {
            line = 6;
        } else {
            print_error("Aucun joueur n'a été défini.");
        }
        
        do {
            printf("Choisissez une colonne (entre 1 et 6)");
            column = get_column();
            size_p = get_size();

            piece = get_piece_size(game, line, column);

            if(piece != NONE) {
                print_error("Une piece est déjà placée à cet emplacement!");
            }
        } while(piece != NONE);

        place_piece(game, size_p, current, column);
    }

    while(running) {
        


    }

    return 0;
}
