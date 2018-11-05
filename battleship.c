#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "tiles.h"

#define SIZE 100
#define PLAYERS 2
#define BOARDS 4

int main(void){
	int i;	

	struct Tile *player0Board = makeBoard(SIZE);
	struct Tile *player0Tracker = makeBoard(SIZE);
	struct Tile *player1Board = makeBoard(SIZE);
	struct Tile *player1Tracker = makeBoard(SIZE);	
	
	struct Tile **boards = malloc((sizeof(struct Tile) * 100) * BOARDS);
	boards[0] = player0Board;
	boards[1] = player1Board;
	boards[2] = player0Tracker;
	boards[3] = player1Tracker;

	boards[0][0].mark = 'X';
	boards[3][0].mark = 'X';

	for (i = 0; i < BOARDS; i++){
		printBoard(boards[i], SIZE);
	}
/*
	printBoard(player0Board, SIZE);
	printf("\n\n");
	printBoard(player0Tracker, SIZE);
	printf("\n\n");
	printBoard(player1Board, SIZE);
	printf("\n\n");
	printBoard(player1Tracker, SIZE);
*/	
	// Ship setups

	int ships[5] = {2, 3, 3, 4, 5};
	int player;
/*
	for (player = 0; player<PLAYERS; player++) {
		printf("\n\nPlayer %d, please begin placing your ships\n\n", player);
		
		for (ship = 0; ship < ships; ship++){
			printf(
		}			
	}
	return 0;
*/
	free(boards);
	free(player0Board);
	free(player1Board);
	free(player0Tracker);
	free(player1Tracker);
}
