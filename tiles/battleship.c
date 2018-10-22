#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define SIZE 100

int main(void){
	
	struct Tile *board = makeBoard(SIZE);
	
	printBoard(board, SIZE);

	return 0;
}
