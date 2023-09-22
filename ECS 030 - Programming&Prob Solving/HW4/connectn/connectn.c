//this program plays connect-n
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//functions declared here
int* read_input(int argnum, char* arglist[]);
void create_board(char*** board, int* turn, int num_row, int num_col);
void play_game(char** board, int turn, int num_row, int num_col, int num_to_win);
void destroy_board(char*** board, int num_row);
void print_board(char** board, int num_row, int num_col);


bool game_over(char** board, int num_to_win, int num_row, int num_col);
bool game_won(char** board, int num_to_win, int num_row, int num_col);
bool game_tied (char** board, int num_to_win, int num_row, int num_col);
bool row_win(char** board, int num_to_win, int num_row, int num_col);
bool col_win(char** board,int num_row, int num_col ,int num_to_win);
bool diag_win(char** board, int num_to_win);
bool right_diag_win(char** board);
bool left_diag_win(char** board);

void get_play(char** board, int* row, int* col, int num_row, int num_col);
void clear_input();
bool play_is_valid(char** board, int num_args_read, int row, int col, int num_row, int num_col);
void make_play(char** board, int row, int col, char piece);




int* read_input(int argnum, char* arglist[]){
	if (argnum < 4){ //if less than 3 args entered, tell the user what you want them to enter
		printf("1.Not enough arguments entered\n");
		printf("2.Usage connectn.out num_rows num_columns number_of_pieces_in_a_row_needed_to_win\n");
		exit(EXIT_FAILURE);
	}

	else if (argnum > 4){ //if user enters more than 3 args, tell the user what you want them to enter
		printf("1.Too many arguments entered\n");
		printf("2.Usage connectn.out num_rows num_columns number_of_pieces_in_a_row_needed_to_win\n");
		exit(EXIT_FAILURE);
	}

	else {
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

void create_board(char*** board , int* turn, int num_row, int num_col){
/* 	board: a pointer to the board to be created
	turn: set the starting turn. 0 means player 1 and 1 means player 2
	@modifies: board, turn
*/
	const int NUM_ROWS = num_row;
	const int NUM_COLS = num_col;
	const char BLANK_SPACE = '*';
	int i, j;

	//player always 1 goes first
	*turn = 0;

	//create pointers to the rows
	*board = (char**)malloc(NUM_ROWS *sizeof(char*));
	for(i = 0; i < NUM_ROWS; ++i){//for each row
		(*board)[i] = (char*) malloc(NUM_COLS * sizeof(char));//create it
		//the extra () are needed because of order of operations
		//board[i] == *(board + i)
		//&board[i] == board + i


		//fill in the row
		for(j = 0; j < NUM_COLS; ++j){
			(*board)[i][j] = BLANK_SPACE;//with stars
			//board[i][j] == *(*(board + i) + j)

		}
	}
}



void destroy_board(char*** board, int num_row){
/* Destroy the board created in create_board
	@board: a pointer to the board created by create board
	@modifies: board
*/
	const int NUM_ROWS = num_row;
	int i;
	//delete each row
	for(i = 0; i < NUM_ROWS; ++i){
		free((*board)[i]);
	}

	//delete the pointers to each row
	free(*board);
	*board = NULL;//set board to the null pointers so we know it isn't valid anymore
}

void clear_input(){
	/* consume all remaining input from the standard input
	@modifies: standard input
	*/

	//keep getting characters until
	//we reach a newline or the end of the input
	char c = getchar();
	while(c != '\n' && c != EOF){
		c = getchar();
	}
}


void get_play(char** board, int* row, int* col, int num_row, int num_col){
	/* get a valid move from the user
		@board: the board
		@row: the row that will be read
		@col: the column that will be read
		@returns: None
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
		for (i = 0; i < NUM_ROWS; ++i){
		    if (board[i][*col] != 'X' && board[i][*col] != 'O' ){
		        *row = i;
		    }


		}

	}


}

bool play_is_valid(char** board, int read_args, int row, int col, int num_row, int num_col){
	/*	check if a move is valid
		@board: connect-n board
		@read_args: The number of variables filled in by scanf
		@col: the column number read
		@returns: true if the move is a valid one and false if it isn't
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
	else if(board[row][col] != BLANK_SPACE){//if the move would be on an occupied space
		return false; //it isn't valid
	}
	//if the move isn't invalid
	return true;//it must be valid

}



void make_play(char** board, int row, int col, char piece){
	/*	place the piece on the board at the specified column
		@board: the board to place the piece on
		@row: the row of the board to place the piece on
		@column: the column of the board to place the piece on
		@piece: the marker to place
		@returns: none
		@modifies: board
	*/


     board[row][col] = piece;

}



bool game_over(char** board, int num_to_win, int num_row, int num_col){
	/* check if the game is over over
		@board: the  board
		@returns: true if the game is over and false if not
	*/
	//a game is over if someone wins or there is a tie
	return game_won(board, num_to_win, num_row, num_col) || game_tied(board, num_to_win, num_row, num_col);
}



bool game_won(char** board, int num_to_win, int num_row, int num_col){
	/* check if someone won the game
	@board: the board
	@returns: true if someone won the game and false if not
	*/
	//we can win a game horizontially, vertically, or diagonally
	return row_win(board, num_to_win, num_row, num_col) || col_win(board,num_row ,num_col ,num_to_win) || diag_win(board, num_to_win);

}



bool game_tied(char** board, int num_to_win, int num_row, int num_col){
	/*
	check if the game ended in a tie
	@board: the board
	@returns: true if the game ended in a tie
	*/

	const int NUM_ROWS = num_row;
	const int NUM_COLS = num_col;
	const char BLANK_SPACE = '*';
	int row, col;

	if(game_won(board, num_to_win, num_row, num_col)){//if someone won
		return false;//it can't be a tie
	}


	else{
	//go through all spaces
		for(row = 0; row < NUM_ROWS; ++row){
			for(col = 0; col < NUM_COLS; ++col){
				//looking for blanks
				if(board[row][col] == BLANK_SPACE){
					//if there are any the game is still on
					return false;
				}
			}
		}
		return true;//else the board is full and we tied
	}
}

bool row_win(char** board, int num_to_win, int num_row, int num_col){
/*
	check if there is a win going horizontally
	@board: the board
	@returns: true if there is a horizontal win and false otherwise
	*/
	const int NUM_ROWS = num_to_win;
	const char BLANK_SPACE = '*';
	int j;//rows
	int i; //cols
	int counter = 0;
	//go throught all the rows
	for(j = 0; j < NUM_ROWS; ++j){
		//and see if all the elements are filled in and the same
		for (i = 0; i < num_col; ++i){
		    if(board[j][i] != BLANK_SPACE && (board[j][i] == board[j][i+1])){
		        ++counter;
		        //printf("\nprinting counter  value %d\n", counter);
		        if (counter == num_to_win){
			        //if any column wins
			        return true;//we've won the game
		        }
		    }
		}
	}

	/*for(row = 0; row < NUM_ROWS; ++row){
		//and see if all the elements are filled in
		//and the same
		if(board[row][row] != BLANK_SPACE && board[row][row] == board[row][row+1]){
			 ++counter;
			 if (counter == num_to_win)
			 //if any row wins
			    return true;//we've won the game
		}
	} */
	//we only know that we don't have any row wins
	//after we have checked all the rows
	return false; //no rows were winners
}



bool col_win(char** board,int num_row ,int num_col, int num_to_win){
	/*
	@board: the board
	@returns: true if there is a vertical win and false otherwise
	*/

	const int NUM_COLS = num_col;
	const int NUM_ROWS = num_row;
	const char BLANK_SPACE = '*';
	int i; // cols
	int j; //rows
	int counter = 1;

	//go through all the columns
	for (j = 0; j < NUM_ROWS; ++j){
		//and see if all the elements are filled in and the same
		for(i = 0; i < NUM_COLS; ++i){
		    if(board[j][i] != BLANK_SPACE && (board[j][i] == board[j+1][i])){
		        ++counter;
		        //printf("\nprinting counter  value %d\n", counter);
		        if (counter == num_to_win){
			        //if any column wins
			        return true;//we've won the game
		        }
		    }
		}
	}
	return false; //no columns were winners
}


bool diag_win(char** board, int num_to_win){
	/*
	check if there is a win going diagonally
	@board: the connectn board
	@returns: true if there is a diagonal win and false otherwise
	*/

	const char BLANK_SPACE = '*';
	//upper left to lower right
	if(board[0][0] != BLANK_SPACE &&
		 board[0][0] == board[1][1] &&
		 board[0][0] == board[2][2]){
		 return true;
	}

	//upper right to lower left
	else if(board[0][2] != BLANK_SPACE &&
		 board[0][2] == board[1][1] &&
		 board[0][2] == board[2][0]){
		 return true;
	}

	else{
		return false; //no diagonal win
	}



}

void play_game(char** board, int turn, int num_row, int num_col, int num_to_win){
	/*
	play a game
	@board: the connect-n board
	@turn: whose turn it is
	*/
	const int NUM_ROWS = num_row;
	const int NUM_COLS = num_col;
	const int NUM_TO_WIN = num_to_win;
	int row, col;

	char pieces[] = "XO"; //player 1 is X and player 2 is O
	//keep playing the game until it is over


	while(!game_over(board, NUM_TO_WIN, num_row, num_col)){

		//each turn
		print_board(board, NUM_ROWS, NUM_COLS); //display the board
		get_play(board, &row, &col, NUM_ROWS, NUM_COLS); //get a move from the player
		make_play(board, row, col, pieces[turn]); //make their move

		turn = (turn + 1) % 2; //and change the turn

	}


	//game is now over
	print_board(board, NUM_ROWS, NUM_COLS);//display the final board

	if(game_won(board, num_to_win, num_row, num_col)){ //if someone won
		//declare the winner
		if(turn == 1){
			printf("Player 1 won!\n");
		}

		else{
			printf("Player 2 won!\n");
		}
	}

	else{ //otherwise it is a tie game
		printf("The game is a tie.\n");
	}
}

void print_board(char** board, int num_row, int num_col){
	/*
		display the board
		@board: the board to display
		@returns: None
		@modifies: None
	*/

	const int NUM_ROWS = num_row;
	const int NUM_COLS = num_col;
	int i, j;

	for(i = 0; i < NUM_ROWS; ++i){ //go through the rows

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
	printf("\nvalue of board[2][0]%c\n",board[2][0]);


}

int main(int argc, char* argv[]){
	int* arg_array;
	int num_row, num_col, num_to_win;
	arg_array = read_input(argc, argv);

	num_row = arg_array[1];
	num_col = arg_array[2];
	num_to_win = arg_array[3];
	char** board;
	int turn;

	create_board(&board, &turn, num_row, num_col); //set up game
	play_game(board, turn, num_row, num_col, num_to_win); //play it
	destroy_board(&board, num_row); //then clean up

	return 0;
}

