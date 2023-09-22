#ifndef GAME_H
	#define GAME_H
	#include<stdlib.h>

	int* read_input(int argnum, char* arglist[]);
	void create_board(char*** board, int* turn, int num_row, int num_col);
	void play_game(char** board, int turn, int num_row, int num_col, int num_to_win);
	void destroy_board(char*** board, int num_row);
	void print_board(char** board, int num_row, int num_col);

#endif

