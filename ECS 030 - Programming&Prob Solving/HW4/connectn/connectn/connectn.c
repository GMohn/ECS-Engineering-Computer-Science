//this program plays connect-n

#include <stdio.h>

//runs all the code to play connect-n
int main(int argc, char* argv[]){
	int* arg_array; 
	int num_row, num_col, num_to_win;
	arg_array = read_input(argc, argv);
	
	num_row = arg_array[1];
	num_col = arg_array[2];
	num_to_win = arg_array[3];		
	char** board;
	int turn;

	//sets up the game
	create_board(&board, &turn, num_row, num_col);
	//runs game
	play_game(board, turn, num_row, num_col, num_to_win); 
	//clears game
	destroy_board(&board, num_row);

	return 0;
}