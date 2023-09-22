#ifndef MOVE_H
	#define MOVE_H
	#include <stdbool.h>

	void get_play(char** board, int* row, int* col, int num_row, int num_col);
	void clear_input();
	bool play_is_valid(char** board, int num_args_read, int row, int col, int num_row, int num_col);
	void make_play(char** board, int row, int col, char piece);

#endif