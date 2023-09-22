#include "move.h"
#include <stdio.h>
#include <stdbool.h>

//clear_input wipes out all other input from standard input

void clear_input(){

	//keep getting chars until we reach a newline or the end of the input
	char c = getchar();
	while(c != '\n' && c != EOF){
		c = getchar();
	}
}

//this function gets valid plays from the user
void get_play(char** board, int* row, int* col, int num_row, int num_col){
	/*	@board: the board
		@row: the row that will be read
		@col: the col that will be read
		@modifies: row, col
	*/
	const int NUM_ROWS = num_row;
	const int NUM_COLS = num_col;
	int i;
	int read_args = 0;
	*row = 0;
	*col = 0;

	//while the user hasn't entered a valid move
	while(!play_is_valid(board, read_args, *row, *col, NUM_ROWS, NUM_COLS)){
		//ask for a valid move
		printf("Enter a column between 0 and %d to play in: ", NUM_COLS - 1);
		read_args = scanf("%d", col);
		//check each row, while descending, assign row to piece above it
		for (i = NUM_ROWS - 1; i >= 0; --i){
		    if (board[i][*col] != 'X' && board[i][*col] != 'O' ){
		        *row = i;
		    }
		}
	}
}

//function checks if the play is valid
bool play_is_valid(char** board, int read_args, int row, int col, int num_row, int num_col){
	/*	@board: connect-n board
		@read_args: num of variables filled in by scanf 
		@col: the column number read
		returns true only if the move is a valid one 
	*/

	const int NUM_ROWS = num_row;
	const int NUM_COLS = num_col;
	const char BLANK_SPACE = '*';

	if(read_args != 1){//if both row and column weren't read
		return false;//then not valid
	}
	else if( row < 0){//if the move is above the board
		return false;//it isn't valid
	}
	else if(row >= NUM_ROWS){//if the move is below the board
		return false;//it isn't valid
	}
	else if(col < 0 || col >= NUM_COLS){
		//if the move is to the left or right of board
		return false;//it isn't valid
	}
	else if(board[row][col] != BLANK_SPACE){//if the move would be on a space that's already occupied
		return false; //it isn't valid
	}

	//if the move isn't invalid it must be valid
	return true;
}


//makes the play on the board
void make_play(char** board, int row, int col, char piece){
	/*	@board: the board to place the piece on
		@piece: puts the marker at the coordinate [row][col]
		@modifies: board
	*/
	
     board[row][col] = piece;    
}
