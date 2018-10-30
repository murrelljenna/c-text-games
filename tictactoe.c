#include "tiles.h"
#include <stdlib.h>
#include <stdio.h>

#define SIZE 9
#define PLAYERS 2
#define GAME "Tic-Tac-Toe"

int gameMenu(void){
	char game[] = GAME;
	int selection;

	printf("Welcome to %s. Please select a menu option:\n", game);
	printf("1. New Game\n");
	printf("2. Load Game\n");
	printf("0. Exit\n\n");
	scanf("%d", &selection);

	return selection;
}


int main(void){
	int selection = gameMenu();
	switch(selection){
		case 0:
			printf("Case 0");
			break;
		case 1:
			printf("Case 1");
		case 2:
			printf("Case 2");
			break;
	}

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
	
		
		board = updateBoard(4, "save.txt", 10, SIZE);
	
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
		
		save("save.txt", board, 0, SIZE);
	}

	return 0;
}
