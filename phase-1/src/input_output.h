#ifdef _BOARD_H_
#ifndef _INPUT_OUTPUT_H_
#define _INPUT_OUTPUT_H_

#include "board.h"

int read_number(const char *prompt);
int read_digit_with_quit(const char *prompt);
void print_error(const char *error);
bool confirm_quit();
void show_board();
void announce_turn(player player);
direction read_direction(const char *prompt);
direction get_direction();
void announce_winner(player winner);
void print_error(const char *error);
int get_column();
int get_line();
void change_player(player * current);
size get_size();

#endif /* _INPUT_OUTPUT_H_ */ 
#endif /* _BOARD_H_ */