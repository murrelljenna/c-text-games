#include "tiles.h"
#include <stdlib.h>
#include <stdio.h>

#define SIZE 9

int main(void){
	char mark;
	int game_over = 0, selector = 0, index = -1, other, move;

	struct Tile *board = makeBoard(SIZE);
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
		
		printBoard(board, SIZE);

		do {
			move = inputMove(selector);
			if (board[move].mark == 'X' || board[move].mark == 'O' || move < 0 || move > 8){
				printf("Invalid move. ");	
			}	

		} while (board[move].mark == 'X' || board[move].mark == 'O' || move < 0 || move > 8);
		
		players[selector].moves[index] = move;
		board[players[selector].moves[index]].mark = mark;

		if (checkVictory(board, mark)){
			game_over = 1;
			
			printBoard(board, SIZE);
			printf("Player %d wins!\n", selector);

			break;
		}

		if (checkTie(board)){
			game_over = 1;
			
			printBoard(board, SIZE);
			printf("Tie!\n");
			
			break;
		}
	
		selector ^= 1;		
	}

	return 0;
}
