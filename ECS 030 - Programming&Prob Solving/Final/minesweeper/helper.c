/*this program helps the main program to run.
 It prints the board, Makes moves on the cells, and builds the board*/
#include <stdio.h>
#include <stdlib.h>
#include "minesweeper.h"

/*creates cases to use options*/
void printBoard(board *b, tile **t)
{
  int i, j;
  for(i=b->numrow -1; i>= 0; i--)
   for (j=0; j < b->numcol; j++)
   {
     if(j==0) printf("%d ", i);
     if (b->blasted)
     {
       if(t[i][j].ismine)printf("* ");
       else printf("%d ", t[i][j].neighbours);
     }
     else
     {
       switch(t[i][j].status)
       {
         case CONCEALED:
           printf("# ");
           break;
         case REVEALED:
           printf("%d ", t[i][j].neighbours);
           break;
         case MARKED:
           printf("! ");
           break;
         case POTENTIAL:
           printf("? ");
           break;
       }
     }
     if (j==b->numcol-1)printf("\n");
   }
   printf("  ");
   for(j=0;j<b->numcol; j++)
     printf("%d ", j);
   printf("\n");

}
/*marks tile with ! */
void markTile(board *b, tile **t, int row, int col)
{
  t[row][col].status=MARKED;
  b->marked++;
  if(t[row][col].ismine)
  {
    b->leftmin--;
  }

}

int uncoveredMarked(board *b, tile **t)
{
  int i, j, count=0;
  for(i=0; i<b->numrow; i++)
    for(j=0; j< b->numcol; j++)
     if(t[i][j].status==REVEALED || t[i][j].status==MARKED) count++;
  return count;
}
/*used to put question mark on the cell*/
void questionTile(board *b, tile **t, int row, int col)
{
  t[row][col].status=POTENTIAL;
}
/*unconvers the cells*/
void revealTile(board *b, tile **t, int row, int col)
{
  if(row<0 || row>=b->numrow || col <0 || col>=b->numcol || t[row][col].status!=CONCEALED) return;
  if(t[row][col].ismine)
  {
    b->blasted=1;
    printBoard(b, t);
    printf("You Lost :(");
    exit(0);
  }
  t[row][col].status=REVEALED;
  if(t[row][col].neighbours==0)
  {
    revealTile(b, t, row-1, col);
    revealTile(b, t, row-1, col-1);
    revealTile(b, t, row-1, col+1);
    revealTile(b, t, row, col+1);
    revealTile(b, t, row, col-1);
    revealTile(b, t, row+1, col+1);
    revealTile(b, t, row+1, col);
    revealTile(b, t, row+1, col-1);
  }

}
/*creates the random seed of mines and checks the number of minds near revealed cells*/
void initBoard(board *b, tile **t, int numrow, int numcol, int nummin, int randseed)
{
  int i, randomrow, randomcol;
  b->numrow = numrow;
  b->numcol = numcol;
  b->nummin = nummin;
  b->leftmin = nummin;

  srand(randseed);

  for (i=0; i< nummin; i++)
  {
    randomrow = rand() % numrow;
    randomcol = rand() % numcol;
    if (t[randomrow][randomcol].ismine) i--;
    else
    {
      printf("Placing mine at %d, %d\n", randomrow, randomcol);
      t[randomrow][randomcol].ismine = 1;
      if(randomrow>0){
        t[randomrow-1][randomcol].neighbours++;
        if(randomcol>0)t[randomrow-1][randomcol-1].neighbours++;
        if(randomcol<numcol-1)t[randomrow-1][randomcol+1].neighbours++;
      }
      if (randomcol>0) {
        t[randomrow][randomcol-1].neighbours++;
        if(randomrow<numrow-1)t[randomrow+1][randomcol-1].neighbours++;
      }
      if(randomrow<numrow-1) {
        t[randomrow+1][randomcol].neighbours++;
        if(randomcol<numcol-1)t[randomrow+1][randomcol+1].neighbours++;
      }
      if(randomcol<numcol-1) {
        t[randomrow][randomcol+1].neighbours++;
      }
    }
  }
}

