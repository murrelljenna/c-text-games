#include "tiles.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SIZE 9
#define PLAYERS 2
#define GAME "Tic-Tac-Toe"

int main(int argc, char *argv[]){
	char mark, newFile[2] = "-n", filename[50], idleInput[10];
	int game_over = 0, user, selector = 0, index = -1, other, move;
	int userid;// = getuid();
	char buffer[10];
	fgets(buffer, 9, stdin);
	sscanf(buffer, "%d", &userid);

	struct Tile *board = makeBoard(SIZE);
	struct Player *players = makePlayers(2); 
	
	if (strcmp(newFile, argv[1]) == 0){
		printf("rar");
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
	selector = getTurn(3, filename);
	
	while (game_over == 0){
		switch(user){
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

		if (matchOtherPlayer(filename, userid) != -1){
			players[other].userid = matchOtherPlayer(filename, userid);
		}			
		
		do {
			board = updateBoard(6, filename, 10, SIZE);
			printBoard(board, SIZE);
			if (getTurn(3, filename) != user){
				printf("\nIt is not your turn player %d. Press <ENTER> to refresh game.\n\n", user);
				fflush(stdin);
				fgets(idleInput, 9, stdin);
			}
		} while (getTurn(3, filename) != user);

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
			printf("Player %d wins!\n\n", selector);
			save(players, filename, board, selector, SIZE);

			//printf("Play again? (Y/N): ");
			//scanf
			break;
		}

		if (checkTie(board)){
			game_over = 1;
			
			printBoard(board, SIZE);
			printf("Tie!\n");			
			save(players, filename, board, selector, SIZE);

			break;
		}
	
		selector ^= 1;
		
		save(players, filename, board, selector, SIZE);
	}

	return 0;
}
