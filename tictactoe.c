#include "tiles.h"
#include <stdlib.h>
#include <stdio.h>

int main(void){
	char mark;
	int game_over = 0, selector = 0, index = -1, other, move;

	struct Tile *board = makeBoard(9);
	struct Player *players = makePlayers(2); 
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
			if (contains(move, players[selector].moves) || contains(move, players[other].moves) || move < 0 || move > 8){
				printf("Invalid move. ");	
			}	

		} while (contains(move, players[selector].moves) || contains(move, players[other].moves) || move < 0 || move > 8);
		
		players[selector].moves[index] = move;
		board[players[selector].moves[index]].mark = mark;

		if (checkVictory(players[selector])){
			game_over = 1;
			
			printBoard(board);
			printf("Player %d wins!\n", selector);

			break;
		}

		if (checkTie(board)){
			game_over = 1;
			
			printBoard(board);
			printf("Tie!\n");
		}
	
		selector ^= 1;		
	}

	return 0;
}
