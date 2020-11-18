#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "board.h"

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

int read_digit_with_quit(const char *prompt)
{
	int in;
	int validInput;

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

char read_dir_char(const char *prompt)
{
	printf("%s", prompt);
	char bin;

	int validInput;
	const char *validDirections = "NSWE";
	char dir;

	validInput = scanf(" %c", &dir);

	if (validInput)
	{
		switch (dir)
		{
		case 'N':
			return NORTH;
			break;

		case 'S':
			return SOUTH;
			break;
		case 'O':
			return WEST;
			break;

		case 'E':
			return EAST;
			break;
		default:
			read_dir_char(prompt);
		}
	}
	else
	{
		scanf("%s", &bin);
	}

	// for (int i = 0; i < sizeof(validDirections) / sizeof(dir); i++)
	// {
	// 	if (dir == validDirections[i])
	// 	{
	// 		switch (dir)
	// 		{
	// 		case 'N':
	// 			return NORTH;
	// 			break;

	// 		case 'S':
	// 			return SOUTH;
	// 			break;
	// 		case 'O':
	// 			return WEST;
	// 			break;

	// 		case 'E':
	// 			return EAST;
	// 			break;
	// 		}
	// 	}
	// 	else
	// 	{
	// 		read_dir_char(prompt);
	// 	}
	// }

	// return dir;
};

void print_error(const char *error)
{
	printf("\033[1;31mERREUR :\033[0m\n\033[0;31m%s\033[0m", error);
}

bool confirm_quit()
{
	bool mustQuit = false;
	int res;
	char confirmation[3];

	printf("Etes-vous sûr de vouloir quitter ? [O]ui / [N]on\n");

	res = scanf("%s", confirmation);

	if (res == 1)
	{
		char letter = tolower(confirmation[0]);

		if (strcmp("o", &letter) == 0)
		{
			mustQuit = true;
		}
		return mustQuit;
	}
	else
	{
		return confirm_quit();
	}
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

void show_board(board game)
{

	printf("     \e[1;34mN\e[0m\n");
	printf("/ / / \\ \\ \\\n");
	for (int y = 5; y >= 0; y--)
	{
		for (int x = 1; x < 7; x++)
		{
			size piece = get_piece_size(game, y, x);

			if (piece == NONE)
			{
				printf("o");
			}
			else
			{
				printf("\e[1;32m%d\e[0m", piece);
			}

			if (x != 6)
			{
				printf("-");
			}
		}
		printf("\n");
		if (y != 0)
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
	return read_number("Sur quelle ligne voulez-vous jouer? ", 1, 6) - 1;
}

int get_column()
{
	return read_number("Sur quelle colonne voulez-vous jouer? ", 1, 6);
}

size get_size()
{
	return read_number("Quelle taille de pièce voulez-vous jouer?\n(1/2/3) ", 1, 3);
}

char get_direction()
{
	return read_dir_char("Choisissez une direction (N,S,E,O), l'arrivée (B))");
}

/*
À changer



Nouveau
- is_valid_move
- déplacement des pions
- validateur de victoire

*/