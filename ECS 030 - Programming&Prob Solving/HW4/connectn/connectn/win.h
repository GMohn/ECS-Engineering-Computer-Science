#ifndef WIN_H
	#define WIN_H
	#include <stdbool.h>

	bool game_over(char** board, int num_to_win, int num_row, int num_col);
	bool game_won(char** board, int num_to_win, int num_row, int num_col);
	bool game_tied (char** board, int num_to_win, int num_row, int num_col);
	bool row_win(char** board, int num_to_win, int num_row, int num_col);
	bool col_win(char** board,int num_row, int num_col ,int num_to_win);
	bool diag_win(char** board,int num_row, int num_col, int num_to_win);
	bool right_diag_win(char** board, int num_row, int num_col, int num_to_win);
	bool left_diag_win(char** board, int num_row, int num_col, int num_to_win);

#endif