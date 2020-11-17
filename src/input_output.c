#include <stdio.h>
#include <stdbool.h>
#include "board.h"
#include <limits.h>

int read_number(const char *prompt, int min, int max)
{
	if(min == -1) {
		min = INT_MIN;
	}

	if(max == -1) {
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

		if(min > in || in > max) {
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

char *get_piece(player player, size size) { };

void show_board(board game) { };

void announce_turn(player player)
{
	if (player == NO_PLAYER)
	{
		player = SOUTH_P;
	}

	printf("-------------------------------------\n\n");
	if (player == SOUTH_P)
	{
		printf("\e[1;33m");
	}
	else
	{
		printf("\e[1;34m");
	}

	printf("Joueur %d\e[0m, à vous de jouer :\n\n", player);
}

int get_line()
{
	return read_number("Sur quelle ligne voulez-vous jouer? ", 1, 6) - 1;
}

int get_column()
{
	return read_number("Sur quelle colonne voulez-vous jouer? ", 1, 6) - 1;
}

size get_size()
{
	return read_number("Quelle taille de pièce voulez-vous jouer?\n(1/2/3) ", 1, 3);
}

/*
À changer
- show_board


Nouveau
- Placer les pions au début
- is_valid_move
- déplacement des pions
- validateur de victoire

*/