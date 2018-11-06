#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "tiles.h"

#define SIZE 100
#define PLAYERS 2
#define BOARDS 4
#define SHIPS 5
int main(void){
	int i;	

	struct Tile **boards = malloc((sizeof(struct Tile) * SIZE) * BOARDS);
	boards[0] = makeBoard(SIZE);
	boards[1] = makeBoard(SIZE);
	boards[2] = makeBoard(SIZE);
	boards[3] = makeBoard(SIZE);

	for (i = 0; i < BOARDS; i++){
		printBoard(boards[i], SIZE);
	}
	
	// Ship setups

	int ships[5] = {2, 3, 3, 4, 5};
	int player, ship;

	for (player = 0; player<PLAYERS; player++) {
		printf("\n\nPlayer %d, please begin placing your ships\n", player);
		
		for (ship = 0; ship < SHIPS; ship++){
			printf("\nPlayer %d, please input ship %d of %d", player, ship, SHIPS);
		}			
	}

	free(boards);
	
	return 0;
}
