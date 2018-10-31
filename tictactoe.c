#include "tiles.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SIZE 9
#define PLAYERS 2
#define GAME "Tic-Tac-Toe"

int main(int argc, char *argv[]){
	char mark, newFile[2] = "-n", filename[50];
	int game_over = 0, user, selector = 0, index = -1, other, move;
	int userid = getuid();
	struct Tile *board = makeBoard(SIZE);
	struct Player *players = makePlayers(2); 
	
	if (strcmp(newFile, argv[1]) == 0){
		user = 0;
		players[user].userid = userid;

		strcpy(filename, argv[2]);
		save(players, filename, board, 0, SIZE);
	}else{
		strcpy(filename, argv[1]);
		if(matchPlayers(argv[1], userid) == -1){
			printf("This game belongs to other players!\n");
			return 0;
		}else{
			user = matchPlayers(argv[1], userid);
		}
	}

	players[user].userid = userid;

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
	
		
		board = updateBoard(6, filename, 10, SIZE);
	
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
		
		save(players, filename, board, selector, SIZE);
	}

	return 0;
}
