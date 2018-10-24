#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "tiles.h"

#define SIZE 100

int main(void){
	
	struct Tile *player0Board = makeBoard(SIZE);
	struct Tile *player0Tracker = makeBoard(SIZE);
	struct Tile *player1Board = makeBoard(SIZE);
	struct Tile *player1Tracker = makeBoard(SIZE);
	
	printBoard(player0Board, SIZE);
	printf("\n\n");
	printBoard(player0Tracker, SIZE);
	printf("\n\n");
	printBoard(player1Board, SIZE);
	printf("\n\n");
	printBoard(player1Tracker, SIZE);
	
	// Ship setups

	int ships[5] = {2, 3, 3, 4, 5};
		

	for (player = 0; player
	for (ship = 0; ship < ships; ship++){
		printf(
	}			

	return 0;
}
