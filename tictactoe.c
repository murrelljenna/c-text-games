#include "tiles.h"
#include <stdlib.h>
#include <stdio.h>

int main(void){
	char mark;
	int game_over = 0, selector = 0, index = -1, other, move;
	int players[][10] = { { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1} };

	struct Tile *board = makeBoard(9); 
	while (game_over == 0){
		switch(selector){
			case 0:
				mark = 'X';
				other = 1;
				index++;
				break;				
			case 1:
				mark = 'O';
				other = 0;
				break;
		} 		
		
		printBoard(board);

		do {
			move = inputMove(selector);
			if (contains(move, players[selector], TICTACTOE_PLAYER_LENGTH) || contains(move, players[other], TICTACTOE_PLAYER_LENGTH) || move < 0 || move > 8){
				printf("Invalid move. ");	
			}	

		} while (contains(move, players[selector], TICTACTOE_PLAYER_LENGTH) || contains(move, players[other], TICTACTOE_PLAYER_LENGTH) || move < 0 || move > 8);
		
		players[selector][index] = move;
		board[players[selector][index]].mark = mark;

		if (checkVictory(players[selector])){
			game_over = 1;
			
			printBoard(board);
			printf("Player %d wins!\n", selector);

			break;
		}
	
		selector ^= 1;		
	}

	return 0;
}
