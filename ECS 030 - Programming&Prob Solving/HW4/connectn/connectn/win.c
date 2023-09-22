#include "win.h"

//this function checks if game is over
bool game_over(char** board, int num_to_win, int num_row, int num_col){

	// @returns: true if the game is over and false if it's not
	//a game is over if someone wins or there's a tie

	return game_won(board, num_to_win, num_row, num_col) || game_tied(board, num_to_win, num_row, num_col);
}


//this function checks if someone won the game
bool game_won(char** board, int num_to_win, int num_row, int num_col){
	// @returns: true if someone won the game and false if not
	
	// game can be won horizontially, vertically, or diagonally (left or right)
	return row_win(board, num_to_win, num_row, num_col) || col_win(board,num_row ,num_col ,num_to_win) || diag_win(board, num_row, num_col, num_to_win);

}

// checks if it was a tie game
bool game_tied(char** board, int num_to_win, int num_row, int num_col){

	// @returns: true if the game ended in a tie

	const int NUM_ROWS = num_row;
	const int NUM_COLS = num_col;
	const char BLANK_SPACE = '*';
	int row, col;
	
	//if someone won, return false because it's not a tie
	if(game_won(board, num_to_win, num_row, num_col)){
		return false;
	}

	else{
	//go through all spaces
		for(row = 0; row < NUM_ROWS; ++row){
			for(col = 0; col < NUM_COLS; ++col){
				//looking for blanks
				if(board[row][col] == BLANK_SPACE){
					//if there are any blank spaces game is still going on
					return false;
				}
			}
		}
		return true; //we tied
	}
}

// checks row / horizontal win
bool row_win(char** board, int num_to_win, int num_row, int num_col){
	// @returns: true if there is a horizontal win and false otherwise
	
	const int NUM_ROWS = num_row;
	const char BLANK_SPACE = '*';
	int j;//rows
	int i; //cols
	//go through all the rows
	for(j = 0; j < NUM_ROWS; ++j){
		int counter = 1;
		for (i = 0; i < num_col-1; ++i){
			int c;
		    	c = i + 1;
		    	if(board[j][i] != BLANK_SPACE && (board[j][i] == board[j][c])){
		        	++counter;
		        	if (counter == num_to_win){
		            		return true;
		    		}
			}
		            
		}
	}

	//we only know that we don't have any row wins after we have checked all the rows
	return false; //no rows were winners
}

// checks columns / vertical wins	
bool col_win(char** board,int num_row ,int num_col, int num_to_win){
	// @returns: true if there is a vertical win and false otherwise
	
	const int NUM_COLS = num_col;
	const int NUM_ROWS = num_row;
	const char BLANK_SPACE = '*';
	int i; // cols
	int j; //rows
	int c;
	
	//go through all the columns
	for (i = 0; i < NUM_COLS; ++i){
	    int counter = 1;
		//and see if all the elements are filled in and the same
		for(j = 0; j < NUM_ROWS-1; ++j){
		    c = j + 1;

		    if(board[j][i] != BLANK_SPACE && (board[j][i] == board[c][i])){
		        ++counter;
		        if (counter == num_to_win){
			       //if any column wins
			        return true;		        }
		    }
		}
	}
	return false; //no columns won
}

// calls right and left diag win to determine if player won
bool diag_win(char** board,int num_row, int num_col, int num_to_win){

		return right_diag_win(board, num_row, num_col, num_to_win) || left_diag_win(board, num_row, num_col, num_to_win); 

}

// checks if there's a right diagonal win
bool right_diag_win(char** board, int num_row, int num_col, int num_to_win){
    	// @returns: true if there is a diagonal win and false otherwise
    
	const char BLANK_SPACE = '*';
	//upper left to lower right
	int i, j, counter_x, counter_o;
	
	for (i = 0; i < num_col - 1; ++i){
		counter_x = 1;
		counter_o = 1;
		//and see if all the elements are filled in and the same
		for(j = num_row - 1; j > 0 ; --j){
			int c;
            		c = j - 1;
            		int d;
            		d = i + 1;
		    	//printf("diag right Checking if %d %d matches %d %d\n", j,i,j-1,i+1);
		    	//printf("col_win row col coordinate %d %d \n", j,i);

		    	//if (j < 0 || i < 0 || j > num_row - 1 || i > num_col - 1 || (j == 0 && i ==0)){
		        //	continue;
		    	//} 
            
		    	if(board[j][i] != BLANK_SPACE && (board[j][i] == board[c][d])){
		        	if (board[j][i] == 'X'){
		            		++counter_x;
		       		}
		       		 else if (board[j][i] == 'O') { 
		     		 	++counter_o;
		        		//printf("\n %d and %d matches with %d and %d diag counter_x: %d\n",j,i,j-1,i+1, counter_x);
				}

				else{
					break;
				}


		        if (counter_x == num_to_win || counter_o == num_to_win){
			       		//if any column wins
				return true;//we've won the game
		        }
		    }
		}
	}
	
	return false; //no diagonal win
}

// checks a left diagonal win
bool left_diag_win(char** board, int num_row, int num_col, int num_to_win){
    	// @returns: true if there is a diagonal win and false otherwise

	const char BLANK_SPACE = '*';
	//upper right to lower left
	int i,j, counter_x, counter_o;
	
	for (i = num_col -1; i > 0; --i){
	    counter_x = 1;
	    counter_o = 1;
		//and see if all the elements are filled in and the same
		for(j = 0; j < num_row - 1 ; ++j){
		    //printf("diag left Checking if %d %d matches %d %d\n", j,i,j+1,i-1);
		    //printf("col_win row col coordinate %d %d \n", j,i);

            
		    if(board[j][i] != BLANK_SPACE && (board[j][i] == board[j+1][i-1])){
		        if (board[j][i] == 'X'){
		            ++counter_x;
		        }
		        else{ 
		            ++counter_o;
			}

		        if (counter_x == num_to_win || counter_o == num_to_win){
			       //if any column wins
			        return true;//we've won the game
		        }
		    }
		}
	}
	
	return false; //no diagonal win
}
