#include "tiles.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SIZE 9
#define PLAYERS 2
#define BOARDS 1
int main(int argc, char *argv[]){
	char mark, newFile[2] = "-n", filename[50], idleInput[10], userWin, otherWin, otherMark;
	int game_over = 0, user, selector = 0, index = -1, other, move, winner, tempId = 0, otherId = 0;
	int userid = getuid();
	
	if (argc == 1){
		printf("Save file required.\nUsage: ./tictactoe [-n] [<filename>]\nUse [-n] to create new file, omit to load existing file\n");
		return 0;
	}	

	//char buffer[10];
	//fgets(buffer, 9, stdin);
	//sscanf(buffer, "%d", &userid);

	struct Tile **boards = malloc((sizeof(struct Tile) * SIZE) * BOARDS);
	boards[0] = makeBoard(SIZE);
	
	struct Player *players = makePlayers(2); 
	
	if (strcmp(newFile, argv[1]) == 0){
		user = 0;
		players[user].userid = userid;

		strcpy(filename, argv[2]);
		save(players, filename, boards, 0, SIZE, BOARDS);
	}else{
		strcpy(filename, argv[1]);
		if (fileExists(filename)){
			tempId = matchPlayers(argv[1], userid);
			if(tempId == -1){
				printf("\nThis game is full.\n\n");
				return 0;
			}else{
				user = tempId;
			}
		}else{
			printf("Save file not found.\nUsage: ./tictactoe [-n] [<filename>]\nUse [-n] to create new file, omit to load existing file\n");
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

		otherId = matchOtherPlayer(filename, userid);
		if (otherId != -1){
			players[other].userid = otherId;
		}			
		
		// First round of checking if game is won or tied.

		boards[0] = updateBoard(6, filename, 10, SIZE);

		userWin = checkVictory(boards[0], mark);
		otherWin = checkVictory(boards[0], otherMark);
		if (userWin || otherWin){
			game_over = 1;	
			printBoard(boards[0], SIZE);
			winner = (userWin == 1) ? user : other;
			printf("\nPlayer %d wins!\n\n", winner);
			save(players, filename, boards, selector, SIZE, BOARDS);

			return 0;
		}

		if (checkTie(boards[0])){
			game_over = 1;
			
			printBoard(boards[0], SIZE);
			printf("\nTie!\n");			
			save(players, filename, boards, selector, SIZE, BOARDS);

			return 0;
		}

		// If no victory yet, check if game has been updated

		while (getTurn(3, filename) != user) {
			printBoard(boards[0], SIZE);
	
			printf("\nIt is not your turn player %d. Press <ENTER> to refresh game: ", user);
			fflush(stdin);
			fgets(idleInput, 9, stdin);
		}
		
		// Once game has been returned to user, check boards[0] for victories again
	
		boards[0] = updateBoard(6, filename, 10, SIZE);
		selector = getTurn(3, filename);

		userWin = checkVictory(boards[0], mark);
		otherWin = checkVictory(boards[0], otherMark);
		if (userWin || otherWin){
			game_over = 1;	
			printBoard(boards[0], SIZE);
			winner = (userWin == 1) ? user : other;
			printf("\nPlayer %d wins!\n\n", winner);
			save(players, filename, boards, selector, SIZE, BOARDS);

			return 0;
		}

		if (checkTie(boards[0])){
			game_over = 1;
			
			printBoard(boards[0], SIZE);
			printf("\nTie!\n");			
			save(players, filename, boards, selector, SIZE, BOARDS);

			return 0;
		}

		printBoard(boards[0], SIZE);

		do {
			move = inputMove(selector);
			if (boards[0][move].mark == 'X' || boards[0][move].mark == 'O' || move < 0 || move > 8){
				printf("Invalid move. ");	
			}	

		} while (boards[0][move].mark == 'X' || boards[0][move].mark == 'O' || move < 0 || move > 8);
		
		players[selector].moves[index] = move;
		boards[0][players[selector].moves[index]].mark = mark;

		selector ^= 1;
		
		save(players, filename, boards, selector, SIZE, BOARDS);
	}

	return 0;
}
