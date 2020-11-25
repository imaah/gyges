#include "board.h"
#include "input_output.h"
#include "game.h"

int main()
{
    board game = new_game();
    player current = SOUTH_P;

    // Initializing the game by placing 6 pieces for each player
    initialize_game(game, &current);


    return 0;
}
