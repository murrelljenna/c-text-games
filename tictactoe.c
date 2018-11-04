#include "tiles.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SIZE 9
#define PLAYERS 2

int main(int argc, char *argv[]){
	char mark, newFile[2] = "-n", filename[50], idleInput[10], userWin, otherWin, otherMark;
	int game_over = 0, user, selector = 0, index = -1, other, move, winner;
	int userid = getuid();
	
	//char buffer[10];
	//fgets(buffer, 9, stdin);
	//sscanf(buffer, "%d", &userid);

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
			printf("\nThis game is full.\n\n");
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
				otherMark = 'O';
				index++;
				break;				
			case 1:
				mark = 'O';
				other = 0;
				otherMark = 'X';
				break;
		} 		

		if (matchOtherPlayer(filename, userid) != -1){
			players[other].userid = matchOtherPlayer(filename, userid);
		}			
		
		// First round of checking if game is won or tied.

		board = updateBoard(6, filename, 10, SIZE);

		userWin = checkVictory(board, mark);
		otherWin = checkVictory(board, otherMark);
		if (userWin || otherWin){
			game_over = 1;	
			printBoard(board, SIZE);
			winner = (userWin == 1) ? user : other;
			printf("\nPlayer %d wins!\n\n", winner);
			save(players, filename, board, selector, SIZE);

			return 0;
		}

		if (checkTie(board)){
			game_over = 1;
			
			printBoard(board, SIZE);
			printf("\nTie!\n");			
			save(players, filename, board, selector, SIZE);

			return 0;
		}

		// If no victory yet, check if game has been updated

		while (getTurn(3, filename) != user) {
			printBoard(board, SIZE);
	
			printf("\nIt is not your turn player %d. Press <ENTER> to refresh game: ", user);
			fflush(stdin);
			fgets(idleInput, 9, stdin);
		}
		
		// Once game has been returned to user, check board for victories again
	
		board = updateBoard(6, filename, 10, SIZE);
		selector = getTurn(3, filename);

		userWin = checkVictory(board, mark);
		otherWin = checkVictory(board, otherMark);
		if (userWin || otherWin){
			game_over = 1;	
			printBoard(board, SIZE);
			winner = (userWin == 1) ? user : other;
			printf("\nPlayer %d wins!\n\n", winner);
			save(players, filename, board, selector, SIZE);

			return 0;
		}

		if (checkTie(board)){
			game_over = 1;
			
			printBoard(board, SIZE);
			printf("\nTie!\n");			
			save(players, filename, board, selector, SIZE);

			return 0;
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

		selector ^= 1;
		
		save(players, filename, board, selector, SIZE);
	}

	return 0;
}
