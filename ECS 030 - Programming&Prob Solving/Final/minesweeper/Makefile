HEADERS = minesweeper.h

default: mine_sweeper.out

minesweeper.o: minesweeper.c $(HEADERS)
	gcc -Wall -c minesweeper.c -o minesweeper.o

helper.o: helper.c $(HEADERS)
	gcc -Wall -c helper.c -o helper.o

mine_sweeper.out: minesweeper.o helper.o
	gcc -Wall minesweeper.o helper.o -o mine_sweeper.out

clean:
	rm -f *.o mine_sweeper.out
