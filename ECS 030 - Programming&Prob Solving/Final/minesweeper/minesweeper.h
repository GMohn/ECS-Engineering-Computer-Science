#ifndef _MINESWEEPER_H_
#define _MINESWEEPER_H_

#define CONCEALED 0
#define REVEALED 1
#define MARKED 2
#define POTENTIAL 3

typedef struct tile {
  int status;
  int ismine;
  int neighbours;
} tile;

typedef struct board {
  int numcol;
  int numrow;
  int nummin;
  int leftmin;
  int marked;
  int blasted;
} board;
#endif /* _MINESWEEPER_H_ */
