#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.h"

enum action_e
{
	SWAP,
	MOVE
};

typedef enum action_e action;

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

	int in;
	int validInput;
	char bin;

	do
	{
		printf("\n%s", prompt);

		validInput = scanf("%d", &in);
		if (!validInput)
		{
			scanf("%s", &bin);
		}

		if (min > in || in > max)
		{
			validInput = 0;
		}

	} while (!validInput);

	return in;
}

char read_char(const char *prompt, int num, ...)
{
	va_list valist;
	char bin;
	int validInput;
	char input;

	num = num > 0 ? num : 0;

	char args[num];

	if (num > 0)
	{
		va_start(valist, num);

		for (int i = 0; i < num; i++)
		{
			args[i] = toupper(va_arg(valist, int));
		}

		va_end(valist);
	}

	do
	{
		printf("%s", prompt);

		validInput = scanf("%s", &input);
		if (validInput)
		{
			if (num > 0)
			{

				for (int i = 0; i < num; i++)
				{
					input = toupper(input);
					// Ceci est un fix de bug à la Estebanc
					if ((int)input == (int)args[i])
					{
						return input;
					}
				}
			}
			else
			{
				return input;
			}

			validInput = 0;
		}
		else
		{
			scanf("%s", &bin);
		}

	} while (!validInput);

	return input;
}

int read_digit_with_quit(const char *prompt)
{
	int in;
	int validInput;

	read_char(prompt, 11, '1', '2', '3', '4', '5', '6', '7', '8', '9', 'Q');

	do
	{
		char val;
		printf("%s", prompt);

		validInput = scanf("%s", &val);

		if (validInput)
		{
			if (strcmp(&val, "q") == 0 || strcmp(&val, "Q") == 0)
			{
				in = -1;
				validInput = 1;
			}
			else if (isdigit(val))
			{
				in = atoi(&val);
			}
			else
			{
				validInput = 0;
			}
		}
	} while (!validInput);

	return in;
}

direction read_direction(const char *prompt)
{
	char input = read_char(prompt, 5, 'N', 'S', 'E', 'O', 'B');
	char in[] = {input, '\0'};
	direction dir;

	if (strcmp(in, "N") == 0)
	{
		dir = NORTH;
	}
	else if (strcmp(in, "S") == 0)
	{
		dir = SOUTH;
	}
	else if (strcmp(in, "E") == 0)
	{
		dir = EAST;
	}
	else if (strcmp(in, "O") == 0)
	{
		dir = WEST;
	}
	else if (strcmp(in, "B") == 0)
	{
		dir = GOAL;
	}

	return dir;
}

void print_error(const char *error)
{
	printf("\n\033[1;31mERREUR :\033[0m\n\033[0;31m%s\033[0m\n", error);
}

bool confirm_quit()
{
	bool mustQuit = false;
	// char confirmation[3];

	char confirmation = read_char("Etes-vous sûr de vouloir quitter ? [O]ui / [N]on\n", 0);

	mustQuit = (int) confirmation == 'O';

	return mustQuit;
	// res = scanf("%s", confirmation);

	// if (res == 1)
	// {
	// 	char letter = tolower(confirmation[0]);

	// 	if (strcmp("o", &letter) == 0)
	// 	{
	// 		mustQuit = true;
	// 	}
	// 	return mustQuit;
	// }
	// else
	// {
	// 	return confirm_quit();
	// }
}

void announce_winner(player winner)
{
	if (winner == SOUTH_P)
	{
		printf("\e[1;33mBRAVO Joueur SUD, vous avez GAGNÉ!\e[0m\n\n");
	}
	else
	{
		printf("\e[1;34mBRAVO Joueur NORD, vous avez GAGNÉ!\e[0m\n\n");
	}
}

// void print_giveup(player player)
// {
// 	if (player == NO_PLAYER)
// 	{
// 		player = SOUTH_P;
// 	}

// 	if (player == NORTH_P)
// 	{
// 		printf("\e[0mLe \e[1;33m");
// 	}
// 	else
// 	{
// 		printf("\e[0mLe \e[1;34m");
// 	}
// 	printf("Joueur %d\e[0m a abandonné.\n", player);
// 	announce_winner(next_player(player));
// }

char *get_piece(player player, size size)
{
	return NULL;
};

//action ask_action() {

//}

void show_board(board game)
{
	int p_line = picked_piece_line(game);
	int p_column = picked_piece_column(game);
	player p_owner = picked_piece_owner(game);

	printf("     \e[1;34mN\e[0m\n");
	printf("/ / / \\ \\ \\\n");

	for (int y = 0; y < DIMENSION; y++)
	{
		for (int x = 0; x < DIMENSION; x++)
		{
			size piece = get_piece_size(game, DIMENSION - y - 1, x);

			if (5 - y == p_line && x == p_column && p_owner != NO_PLAYER)
			{
				if (p_owner == NORTH_P)
				{
					printf("\e[1;34m•\e[0m");
				}
				else
				{
					printf("\e[1;33m•\e[0m");
				}
			}
			else if (piece == NONE)
			{
				printf("o");
			}
			else
			{
				printf("\e[0;32m%d\e[0m", piece);
			}

			if (x != DIMENSION - 1)
			{
				printf("-");
			}
		}
		printf("\n");
		if (y != DIMENSION - 1)
		{
			printf("| | | | | |\n");
		}
	}

	printf("\\ \\ \\ / / /\n");
	printf("     \e[1;33mS\e[0m\n");
}

void announce_turn(player player)
{
	if (player == NO_PLAYER)
	{
		player = SOUTH_P;
	}

	printf("-------------------------------------\n\nJoueur ");
	if (player == SOUTH_P)
	{
		printf("\e[1;33mSUD");
	}
	else
	{
		printf("\e[1;34mNORD");
	}

	printf("\e[0m, à vous de jouer :\n");
}

void change_player(player *current)
{
	if (*current == NORTH_P)
	{
		*current = SOUTH_P;
	}
	else
	{
		*current = NORTH_P;
	}
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
	return read_number("Quelle taille de pièce voulez-vous jouer?\n(1/2/3) ", 1, 3);
}

direction get_direction()
{
	return read_direction("Choisissez une direction (N,S,E,O), l'arrivée (B) ");
}

action get_action() {
	char in = read_char("Vous venez d'arriver sur une piece.\nQue voulez vous faire, [E]changer ou [C]ontinuer ?", 2, 'E', 'C');

	if((int) in == 'E') {
		return SWAP;
	} else {
		return MOVE;
	}
}