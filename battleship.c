#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "tiles.h"

#define SIZE 100
#define PLAYERS 2
#define BOARDS 4
#define SHIPS 5

int main(int argc, char *argv[]) {
	char newFile[3] = "-n";

	// Check validity of stdin call

	if (argc == 1 || (argc == 2 && argv[1] == newFile)) {
		printf("Save file required.\nUsage: ./battleship [-n] [<filename>]\nUse [-n] to create new file, omit to load existing file\n");
	}else if (argc == 2 && (fileExists(argv[1]) == 0)) {	
		printf("Save file not found.\nUsage: ./battleship [-n] [<filename>]\nUse [-n] to create new file, omit to load existing file\n");
	}else {

		// Validity check successfull

		int user, selector = 0, tempId, otherId, game_over = 0, i, player, j, move, other, input, invalid, winner, quitting = 0;
		char direction;
		int increment, offset, markCount, resume;
		int ships[5] = {2, 3, 3, 4, 5}, buffer[5];
		int userid; // = getuid();
		scanf("%d", &userid);
		char filename[25], idleInput[10];

		const char ship = 'S', hit = 'X', miss = 'O';

		struct Player *players = makePlayers(2); 
		struct Tile **boards = malloc((sizeof(struct Tile) * SIZE) * BOARDS);
		boards[0] = makeBoard(SIZE); // Contains player 0's ships
		boards[1] = makeBoard(SIZE); // Contains player 1's ships
		boards[2] = makeBoard(SIZE); // Records player 0's hits and misses
		boards[3] = makeBoard(SIZE); // Records player 1's hits and misses
	
		struct Tile **boardBuffer = malloc((sizeof(struct Tile) * SIZE) * BOARDS);
		boardBuffer[0] = makeBoard(SIZE);
		boardBuffer[1] = makeBoard(SIZE);
		boardBuffer[2] = makeBoard(SIZE);
		boardBuffer[3] = makeBoard(SIZE);

		// Starting new game or slotting player into existing game

		if (strcmp(newFile, argv[1]) == 0) {
			user = 0;
			players[user].userid = userid;

			strcpy(filename, argv[2]);
			save(players, filename, boards, 0, SIZE, BOARDS);
		}else{
			strcpy(filename, argv[1]);
			tempId = matchPlayers(argv[1], userid);
			if(tempId == -1) {
				printf("\nThis game is full.\n\n");
				game_over = 1;
			}else{
				user = tempId;
				players[user].userid = userid;
			}
		}
		
		
		
		// Game begins

		while (!game_over && !quitting) {
			switch(user) {
				case 0:
					other = 1;
					break;				
				case 1:
					other = 0;
					break;
			}

			otherId = matchOtherPlayer(filename, userid);
			if (otherId != -1) {
				players[other].userid = otherId;
			}
			// Prints user's tracker and main board

			boards = updateBoard(filename, SIZE, BOARDS);
			printBoard(boards[user+2], SIZE);
			printBoard(boards[user], SIZE);
			printf("\n");

			// Ship setups

			markCount = countTiles(boards[user], ship, SIZE) + countTiles(boards[user], hit, SIZE);
			if (markCount < 17) {
				resume = 0;
				if (markCount < 5 && markCount >= 2) {
					printf("de rars");
					resume = 1;
				} else if (markCount < 8 && markCount >= 5) {
					resume = 2;
				} else if (markCount < 12 && markCount >= 8) {
					resume = 3;
				} else if (markCount < 17 && markCount >= 12) {
					resume = 4;
				}

				for (j = resume; j < SHIPS; j++) {
					do {
						printf("Please input starting column/row of ship %d of %d (C/R): ", j+1, SHIPS);
						move = inputMove(SIZE); 
						if (move < 0 || move > SIZE || boards[user][move].mark == ship) {
							printf("\nInvalid move. ");
						}
					} while (move < 0 || move > SIZE || boards[user][move].mark == ship);
					boards[user][move].mark = ship;

					do {
						printf("This ship is %d tiles long. Please direction direction (N/S/E/W): ", ships[j]);
						scanf("%c%*c", &direction);
						printf("%c", direction);
						offset = 0;
						invalid = 0;

						switch (direction) {
							case 'N':
							case 'n':
								increment = -10;
								direction = 'N'; // Direction gets set to one case to shorten future conditional statements.
								break;
							case 'S':
							case 's':
								increment = 10;
								direction = 'S';
								break;
							case 'E':
							case 'e':
								increment = 1;
								direction = 'E';
								break;
							case 'W':
							case 'w':
								increment = -1;
								direction = 'W';
								break;
							default:
								printf("Invalid entry.");
								invalid = 1;
								break;
						}
						if (invalid == 0) {
							for (i = 2; i <= ships[j]; i++) {
								offset+=increment;
								
								if ((move+offset) < 0 || (move+offset) > SIZE || boards[user][move+offset].mark == ship ||
								(direction == 'E' && (move+offset)%10 == 0) ||
								(direction == 'W' && (move+offset)%10 == 9)) {
									invalid = 1;
									printf("Invalid move. ");
									break;
								} else {
									buffer[i-2] = move+offset;
								}
							}
							
							if (invalid == 0) {
								for (i = 2; i <= ships[j]; i++) {
									boards[user][buffer[i-2]].mark = ship;
								}
							}
						}	
					} while (invalid == 1);

					// Ship placement successfull

					boardBuffer = updateBoard(filename, SIZE, BOARDS);
					boards[other] = boardBuffer[other];
					boards[other+2] = boardBuffer[other+2];
				
					save(players, filename, boards, 0, SIZE, BOARDS);
					
					printBoard(boards[user+2], SIZE);
					printBoard(boards[user], SIZE);
					printf("\n");
					
				}
			}
			
			// User finished placing battleships
		
			markCount = countTiles(boards[other], ship, SIZE) + countTiles(boards[other], hit, SIZE);
			while (markCount < 17) { // markCount now reads OTHER player's ship count. If other player not finished, do not start.
				printf("\nPlayer %d has not finished placing their ships. Press <ENTER> to refresh game, or type \"exit\" to quit: ", other);
				fgets(idleInput, 9, stdin);

				if (!strcmp(idleInput, "exit\n")) {
					quitting = 1;
					break;
				}
				markCount = countTiles(boards[other], ship, SIZE) + countTiles(boards[other], hit, SIZE);
			} 

			// Enter into main battle stage if player not exiting game. 

			if (quitting != 1) {
				winner = checkVictoryBat(boards, SIZE); // Check for winning conditions.
				if (winner < 0) {
					while (getTurn(3, filename) != user) {	// Check if is user's turn.
						printf("\nIt is not your turn player %d. Press <ENTER> to refresh game, or type \"exit\" to quit: ", user);
						fflush(stdin);
						fgets(idleInput, 10, stdin);
						if (!strcmp(idleInput, "exit\n")) {
							quitting = 1;
							break;
						}
					}

					if (checkVictoryBat(boards, SIZE) < 0 && quitting != 1) { // If other player won while user is refreshing game, entire game loop will reiterate and fall into the else on line 245.
						do {
							printf("Please select a column & row (C/R) to attack: ");
							move = inputMove(SIZE);
							if (move < 0 || move > 99) {
								printf("Invalid move. ");
							}
						} while (move < 0 || move > 99);
						
						switch (boards[other][move].mark) {
							case 'S':
								boards[other][move].mark = 'X';
								boards[user+2][move].mark = 'X';
								printf("\nShip hit!\n");
								break;
							case ' ':
								boards[other][move].mark = 'O';
								boards[user+2][move].mark = 'O';
								printf("\nMiss!\n");
								break;
						}

						selector = getTurn(3,filename) ^ 1;
						save(players, filename, boards, selector, SIZE, BOARDS);
					}
				} else { // If there is winner while user is in refresh game loop, this block will be entered upon re-iteration of main game loop.
					printBoard(boards[user+2], SIZE);
					printBoard(boards[user], SIZE);
					printf("\n");

					printf("\nPlayer %d wins!\n\n", winner);
					game_over = 1;
				}
			}
		}
		
		freeBoards(boards, BOARDS);
		free(players);
	}
	
	return 0;
}

// Game specific functions

int checkVictoryBat(struct Tile **boards, int tileCount) {
	int i, count, winner = -1;
	for (i = 0; i < 2; i++) {
		if (!countTiles(boards[i], 'S', tileCount)) {
			winner = i ^ 1;
			break;
		}
	}
	
	return winner;
}
