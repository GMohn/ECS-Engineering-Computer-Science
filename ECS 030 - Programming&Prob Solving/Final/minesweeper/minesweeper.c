/*This program plays the game minesweeper through the command prompt*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "minesweeper.h"
/*define external variables */
extern void printBoard(board *b, tile **t);
extern void markTile(board *b, tile **t, int row, int col);
extern void questionTile(board *b, tile **t, int row, int col);
extern void revealTile(board *b, tile **t, int row, int col);
extern void initBoard(board *b, tile **t, int numrow, int numcol, int nummin, int randseed);
extern int uncoveredMarked(board *b, tile **t);
int* read_input(int argc, char *argv[]);
/*main function calls read input*/
int main(int argc, char *argv[])
{
 read_input(argc, argv);
  return 0;
}
/*This function checks if there are enough inputted arguments  then continues to build the board, play the game and call the rest of the functions*/
int* read_input(int argc, char*argv[])
{
    /*dynamically allocate the board and declare variables for rows columns, and seeding random*/
    int numrow, numcol, nummin, randseed=time(NULL);
  board *b = (board *)calloc (1, sizeof(board));
  tile **t;
  int i;
  /* check if enough arguments*/
  if (argc < 4)
  {
    printf("Not enough arguments. Usage:\n./mine_sweeper.out num_rows num_cols num_mines [seed])");
    exit(0);
  }
  else if(argc >5)
  {
    printf("Too many arguments. Usage:\n./mine_sweeper.out num_rows num_cols num_mines [seed])");
    exit(0);
  }
  /*check if number of mines is bigger than the array given*/
  numrow=atoi(argv[1]);
  numcol=atoi(argv[2]);
  nummin=atoi(argv[3]);
  if(nummin > numrow*numcol)
  {
    printf("Incorrect number of mines\n");
    exit(0);
  }
  /*allocate space for array and call functions to make random seed and print board*/
  if (argc==5) randseed=atoi(argv[4]);
  t = (tile **)calloc(1, sizeof(tile*)*(numrow));
  for (i=0; i<numrow; i++)
    t[i] = (tile *)calloc(1, sizeof(tile)*numcol);
  initBoard(b, t, numrow, numcol, nummin, randseed);
  printf("There are %d mines left\n", b->nummin-b->marked);
  printBoard(b, t);
/*while true, enter a row between the given arraw and prompt for further options*/
  int row, col, option;
  while(1)
  {
    printf("Enter row a row between 0-%d and a column between 0-%d: ", numrow-1, numcol-1);
    scanf("%d %d", &row, &col);
    if(row<0 || row>=numrow || col <0 || col>=numcol)
    {
       continue;
    }
    else
    {
      if(t[row][col].status==REVEALED)
      {
        printf("This tile is already revealed.\n");
        continue;
      }
      else if (t[row][col].status==MARKED)
      {
        printf("Enter Action\n0. UnMark\n1. Cancel\nAction: ");
        scanf("%d", &option);
        if(option==0){
          t[row][col].status=CONCEALED;
          b->marked--;
        }
        else continue;
      }
      else if (t[row][col].status==POTENTIAL)
      {
        printf("Enter Action\n0. UnQuestion\n1. Cancel\nAction: ");
        scanf("%d", &option);
        if(option==0){
          t[row][col].status=CONCEALED;
        }
      }
      else
      {
        printf("Enter Action\n0. Reveal\n1. Question\n2. Mark\n3. Cancel\nAction: ");
        scanf("%d", &option);
        switch(option)
        {
          case 0:
            revealTile(b, t, row, col);
            break;
          case 1:
            questionTile(b, t, row, col);
            break;
          case 2:
            markTile(b, t, row, col);
            break;
          case 3:
             break;
          default:
             continue;
        }
      }
      if (b->leftmin==0 && uncoveredMarked(b,t)==numrow*numcol && b->marked==b->nummin)
      {
        b->blasted=1;
        printBoard(b, t);
        printf("You Won!!");
        break;
      }
      printf("There are %d mines left\n", b->nummin-b->marked);
      printBoard(b, t);
    }
  }
  return 0;
}

