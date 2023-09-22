#include "game.h"
#include "move.h"
#include "win.h"
#include <stdio.h>
#include <stdlib.h>

//reads the users input and changes its type from chars into ints
int* read_input(int argnum, char* arglist[]){
	if (argnum < 4){ //if less than 3 args entered, tell the user what you want them to enter
		printf("Not enough arguments entered\n"); 
		printf("Usage connectn.out num_rows num_columns number_of_pieces_in_a_row_needed_to_win\n");
		exit (0);
	}

	else if (argnum > 4){ //if user enters more than 3 args, tell the user what you want them to enter
		printf("Too many arguments entered\n"); 
		printf("Usage connectn.out num_rows num_columns number_of_pieces_in_a_row_needed_to_win\n"); 
		exit (0);
	}

	else {//changes chars into ints if users entered valid input
		int* args_array;
		args_array = malloc(argnum * sizeof(int *));
		//int* input = (int*) malloc ((argnum - 1) * sizeof(int));
		int i;

		//take user input and turn it into ints instead of chars
		for (i = 0; i < argnum; ++i){
			sscanf(arglist[i], "%d", &args_array[i]);
		}
		return(args_array);
	}
}

//this function sets up the board
void create_board(char*** board , int* turn, int num_row, int num_col){
/* 	board: a pointer to the board to be created
	turn: 0 = player 1 and 1 = player 2
	@modifies: board, turn
*/
	const int NUM_ROWS = num_row;
	const int NUM_COLS = num_col;
	const char BLANK_SPACE = '*';
	int i, j;
	
	//player 1 goes first
	*turn = 0;

	//create pointers to the rows
	*board = (char**)malloc(NUM_ROWS *sizeof(char*));
	for(i = 0; i < NUM_ROWS; ++i){//for each row
		(*board)[i] = (char*) malloc(NUM_COLS * sizeof(char));
		
		//fill in rows with star characters
		for(j = 0; j < NUM_COLS; ++j){
			(*board)[i][j] = BLANK_SPACE;
		}
	}
}


//this function plays the game
void play_game(char** board, int turn, int num_row, int num_col, int num_to_win){
	/*
	@board: the connect-n board
	@turn: whose turn it is
	*/
	const int NUM_ROWS = num_row;
	const int NUM_COLS = num_col;
	const int NUM_TO_WIN = num_to_win;
	int row, col;

	char pieces[] = "XO"; 
	//player 1 == X and player 2 == O
	//play the game until it's over

	while(!game_over(board, NUM_TO_WIN, num_row, num_col)){

		print_board(board, NUM_ROWS, NUM_COLS); //display the board
		//get play from the user
		get_play(board, &row, &col, NUM_ROWS, NUM_COLS);
		//make the play
		make_play(board, row, col, pieces[turn]);
		//take turns between player 1 and 2
		turn = (turn + 1) % 2; 
	}

	//game is over
	print_board(board, NUM_ROWS, NUM_COLS);//display the final board

	if(game_won(board, num_to_win, num_row, num_col)){ //if a player won
		//declare a winner
		if(turn == 1){
			printf("Player 1 Won!\n");
		}

		else{
			printf("Player 2 Won!\n");
		}
	}

	else{ //it's a tie game
		printf("Tie game!\n");
	}
}

//this function destroys the board
void destroy_board(char*** board, int num_row){
	// @board: a pointer to the board created by create board
	// @modifies: board

	const int NUM_ROWS = num_row;
	int i;
	//delete each row
	for(i = 0; i < NUM_ROWS; ++i){
		free((*board)[i]);
	}

	//delete pointers to each row
	free(*board);
	*board = NULL;//set board to the null pointers so we know it isn't valid anymore
}

//prints the board to the screen
void print_board(char** board, int num_row, int num_col){

	const int NUM_ROWS = num_row;
	const int NUM_COLS = num_col;
	int i, j;

	for(i = NUM_ROWS - 1; i >= 0; --i){ //go through rows

		printf("%d ", i); //print the row header
		for(j = 0; j < NUM_COLS; ++ j){ //go through the elements in each row
			printf("%c ", board[i][j]); //display the element
		}

		printf("\n");//print out a new line between the rows

	}
    printf("  ");
	for (i = 0; i < NUM_COLS;++i){
	    printf("%d ",i); //print the bottom header
	}
	printf("\n");

}