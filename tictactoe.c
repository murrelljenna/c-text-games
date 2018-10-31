#include "tiles.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE 9
#define PLAYERS 2
#define GAME "Tic-Tac-Toe"

int main(int argc, char *argv[]){
	char mark, newFile[2] = "-n", filename[50];
	int game_over = 0, selector = 0, index = -1, other, move;
	struct Tile *board = makeBoard(SIZE);
	struct Player *players = makePlayers(2); 
	
	if (strcmp(newFile, argv[1]) == 0){
		strcpy(filename, argv[2]);
		save(filename, board, 0, SIZE);
	}else{
		strcpy(filename, argv[1]);
	}

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
	
		
		board = updateBoard(4, filename, 10, SIZE);
	
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
		
		save(filename, board, selector, SIZE);
	}

	return 0;
}
