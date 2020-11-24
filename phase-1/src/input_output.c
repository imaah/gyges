#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "input_output.h"

int read_number(const char *prompt, int min, int max)
{
	if (min == -1)
	{
		min = INT_MIN;
	}

	if (max == -1)
	{
		max = INT_MAX;
	}

	char input[MAX_INPUT];
	int validInput;
	char bin;
	int value = -1;

	// Looping until we get a valid input
	do {
		printf("%s", prompt);

		validInput = scanf("%s", input);

		if (validInput)
		{
			value = atoi(input);

			if (min > value || value > max)
			{
				validInput = 0;
			}
		}
		// Filling the overflow into a bin
		else
		{
			scanf("%s", &bin);
		}
	} while (!validInput);

	return value;
}

char read_char(const char *prompt, int args_count, ...)
{
	va_list valist;
	char bin;
	int validInput;
	char input[MAX_INPUT];

	// Avoiding negative args
	if (args_count < 0)
	{
		args_count = 0;
	}

	char args[args_count];

	char value;

	// Making sure that all args are uppercase
	if (args_count > 0)
	{
		va_start(valist, args_count);

		for (int i = 0; i < args_count; i++)
		{
			args[i] = toupper(va_arg(valist, int));
		}

		va_end(valist);
	}

	// Looping through possible values that could be returned (these are known from the function args)
	do {
		printf("%s", prompt);

		validInput = scanf("%s", input);

		// If the input is correct
		if (validInput)
		{
			// Getting only the first char, in case the player wrote something like "Nord" instead of "N"
			value = toupper(input[0]);
			// If there are multiple letters that could be returned, check which one has been entered
			if (args_count > 0)
			{
			 	// Looping through all possible values to be returned, to see if the input is one of them
				for (int i = 0; i < args_count; i++)
				{
				 		// If the inputed char is a possible action, return it
					if ((int) value == (int) args[i])
					{
						return value;
					}
				}
			}
			// If there is only one letter to return, return it
			else
			{
				return value;
			}

			validInput = 0;
		}
		// Filling the bin with the potential overflow
		else
		{
			scanf("%s", &bin);
		}
	} while (!validInput);

	return value;
}

direction read_direction(const char *prompt)
{
	// Asking a letter as input between "N", "S", "E", "O", "B" or "A"
	char input = read_char(prompt, 6, 'N', 'S', 'E', 'O', 'B', 'A');
	direction dir = -1;

	// Switching between all return cases possible to know which direction has been chosen
	switch (input)
	{
		case 'N':
			dir = NORTH;
			break;
		case 'S':
			dir = SOUTH;
			break;
		case 'E':
			dir = EAST;
			break;
		case 'O':
			dir = WEST;
			break;
		case 'B':
			dir = GOAL;
			break;
		case 'A':
			dir = -1;
			break;
	}

	return dir;
}

void print_error(const char *error)
{
	printf("\n\033[1;31mERREUR :\033[0m\n\033[0;31m%s\033[0m\n", error);
}

void announce_winner(board game)
{
	// Getting the winner of the game
	player winner = get_winner(game);

	printf("Bravo ");

	// Checking which player won, to announce the winner in a colored message according to the winner's color
	if (winner == SOUTH_P)
	{
		printf("\e[1;33mSUD");
	}
	else
	{
		printf("\e[1;34mNORD");
	}

	printf("\e[0m !\nTu as remporté cette partie !!!🎉\n");
}

void show_board(board game)
{
	// Getting the current picked piece to print it in color and differently
	int picked_line = picked_piece_line(game);
	int picked_column = picked_piece_column(game);
	player picked_owner = picked_piece_owner(game);

	// Printing the "Header" of the board
	printf("\n\n-------------------------------------\n\n");
	printf("            \e[1;34mNORD\e[0m\n");
	printf("      /  /  /  \\  \\  \\\n");

	// Looping through lines
	for (int line = 0; line < DIMENSION; line++)
	{
		printf("      ");
		// Looping through columns
		for (int column = 0; column < DIMENSION; column++)
		{
			// Getting which piece to place in these coordinates
			size piece = get_piece_size(game, DIMENSION - line - 1, column);

			if (5 - line == picked_line && column == picked_column && picked_owner != NO_PLAYER)
			{
			 	// Checking which player is currently holding the piece, to print it according to his color
				if (picked_owner == NORTH_P)
				{
					printf("\e[1;34m•\e[0m");
				}
				else
				{
					printf("\e[1;33m•\e[0m");
				}
			}
			// Printing the regular "o" if no piece is selected
			else if (piece == NONE)
			{
				printf("o");
			}
			// Else priting the piece itself
			else
			{
				printf("\e[0;32m%d\e[0m", piece);
			}

			if (column != DIMENSION - 1)
			{
				printf("﹘");
			}
		}

		// First check to see if we are printing the middle of the board. If so, we print a compass
		if (line == 2)
		{
			printf("        ↑");
		}
		else if (line == 3)
		{
			printf("        ↓");
		}

		printf("\n");
		// Printing the separator between lines only if we are not on the last line
		if (line != DIMENSION - 1)
		{
			printf("      |  |  |  |  |  |");

			// Second check to print the compass at the middle height of the board
			if (line == 1)
			{
				printf("        N");
			}
			else if (line == 2)
			{
				printf("    O ←   → E");
			}
			else if (line == 3)
			{
				printf("        S");
			}

			printf("\n");
		}
	}

	// Priting the "Footer" of the board
	printf("      \\  \\  \\  /  /  /\n");
	printf("            \e[1;33mSUD\e[0m\n\n");
	printf("-------------------------------------\n\n");
}

void announce_turn(player player)
{
	// Making sure that there is always a selected player
	if (player == NO_PLAYER)
	{
		player = SOUTH_P;
	}

	// Checking which players' turn it is to print the announcement according to their colors
	printf("\nJoueur ");
	if (player == SOUTH_P)
	{
		printf("\e[1;33mSUD");
	}
	else
	{
		printf("\e[1;34mNORD");
	}

	printf("\e[0m, à vous de jouer :\n\n");
}

int get_line()
{
	return read_number("Sur quelle ligne voulez-vous jouer (entre 1 et 6) ? ", 1, DIMENSION) - 1;
}

int get_column()
{
	return read_number("Sur quelle colonne voulez-vous jouer (entre 1 et 6) ? ", 1, DIMENSION) - 1;
}

size get_size()
{
	return read_number("Quelle taille de pièce voulez-vous jouer?\n(1/2/3) ", 1, NB_SIZE);
}

direction get_direction()
{
	return read_direction("Choisissez une direction (N,S,E,O), l'arrivée (B) ou annuler (A)\n");
}

cancel_type get_cancel_type()
{
	// Asking if the player wants to comeback to inital position, of rollback only 1 step behind
	char input = read_char("Voulez-vous annuler le dernier [P]as ou retourner à la position [I]nitiale ? ", 2, 'P', 'I');

	// Setting default type to STEP, because there are two existing (STEP and MOVEMENT)
	cancel_type type = STEP;

	// Checking which cancelling type has been chosen
	switch (input)
	{
		case 'P':
			type = STEP;
			break;
		case 'I':
			type = MOVEMENT;
			break;
	}

	return type;
}

action get_action()
{
	// Asking the player if he wants to continue moving or if he wants to swap pieces when his last step is on another piece
	char input = read_char("Vous venez d'arriver sur une piece.\nQue voulez vous faire, [E]changer ou [C]ontinuer ? ", 2, 'E', 'C');

	// Setting default type to CONTINUE, because there are two existing (SWAP and CONTINUE)
	action action_i = CONTINUE;

	// Checking which action has been chosen
	switch (input)
	{
		case 'E':
			action_i = SWAP;
			break;
		case 'C':
			action_i = CONTINUE;
	}

	return action_i;
}

bool confirm(char *prompt)
{
	// Asking if the player really wants to quit
	char input = read_char(prompt, 2, 'O', 'N');

	// If the returned char in "O", we quit
	if ((int) input == 'O')
	{
		return true;
	}

	return false;
}

bool confirm_swap()
{
	return confirm("Voulez-vous vraiment échanger la pièce ?[O]UI/[N]ON");
}

bool confirm_continue()
{
	return confirm("Voulez-vous vraiment continuer à déplacer la pièce ? [O]ui/[N]on ");
}
