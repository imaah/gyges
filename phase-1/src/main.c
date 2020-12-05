#include <stdbool.h>
#include <stdio.h>

#include "board.h"
#include "game.h"
#include "input_output.h"

/**
 * @file main.c
 * @brief Main loop of the game.* 
 * @author Guibout & Morisse
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
