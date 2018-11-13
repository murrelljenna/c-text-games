#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "tiles.h"

#define SIZE 100
#define PLAYERS 2
#define BOARDS 4
#define SHIPS 5

int main(int argc, char *argv[]){
	char newFile[3] = "-n";

	// Check validity of stdin call

	if (argc == 1 || (argc == 2 && argv[1] == newFile)){
		printf("Save file required.\nUsage: ./battleship [-n] [<filename>]\nUse [-n] to create new file, omit to load existing file\n");
	}else if (argc == 2 && (fileExists(argv[1]) == 0)){	
		printf("Save file not found.\nUsage: ./battleship [-n] [<filename>]\nUse [-n] to create new file, omit to load existing file\n");
	}else {

		// Validity check successfull

		int user, selector = 0, tempId, otherId, game_over = 0, i, player, j, move, other, input, invalid;
		int increment, offset, markCount, resume;
		int ships[5] = {2, 3, 3, 4, 5}, buffer[5];
		int userid = getuid();
		char filename[25];

		const char ship = 'S', hit = 'X', miss = 'O';

		struct Player *players = makePlayers(2); 
		struct Tile **boards = malloc((sizeof(struct Tile) * SIZE) * BOARDS);
		boards[0] = makeBoard(SIZE);
		boards[1] = makeBoard(SIZE);
		boards[2] = makeBoard(SIZE);
		boards[3] = makeBoard(SIZE);
	
		struct Tile **boardBuffer = malloc((sizeof(struct Tile) * SIZE) * BOARDS);
		boardBuffer[0] = makeBoard(SIZE);
		boardBuffer[1] = makeBoard(SIZE);
		boardBuffer[2] = makeBoard(SIZE);
		boardBuffer[3] = makeBoard(SIZE);

		// Starting new game or slotting player into existing game

		if (strcmp(newFile, argv[1]) == 0){
			user = 0;
			players[user].userid = userid;

			strcpy(filename, argv[2]);
			save(players, filename, boards, 0, SIZE, BOARDS);
		}else{
			strcpy(filename, argv[1]);
			tempId = matchPlayers(argv[1], userid);
			if(tempId == -1){
				printf("\nThis game is full.\n\n");
				game_over = 1;
			}else{
				user = tempId;
			}
		}
		
		// Game begins

		while (!game_over){
			switch(user){
				case 0:
					other = 1;
					break;				
				case 1:
					other = 0;
					break;
			}

			otherId = matchOtherPlayer(filename, userid);
			if (otherId != -1){
				players[other].userid = otherId;
			}
			
			boards = updateBoard(filename, SIZE, BOARDS);
			for (i = 0; i < BOARDS; i++){
				printBoard(boards[i], SIZE);
			}
			
			// Ship setups

			markCount = countTiles(boards[user], ship, SIZE) + countTiles(boards[user], hit, SIZE);
			if (markCount < 17){
				resume = 0;
				if (markCount < 5 && markCount >= 2){
					resume = 1;
				} else if (markCount < 8 && markCount >= 5){
					resume = 2;
				} else if (markCount < 12 && markCount >= 8){
					resume = 3;
				} else if (markCount < 17 && markCount >= 12){
					resume = 4;
				}

				for (j = resume; j <= SHIPS; j++){
					do {
						printf("Please input starting column/row of ship %d of %d (C/R): ", j+1, SHIPS);
						move = inputMove(selector, SIZE); 
						if (move < 0 || move > SIZE || boards[user][move].mark == ship){
							printf("\nInvalid move. ");
						}
					} while (move < 0 || move > SIZE || boards[user][move].mark == ship);
					boards[user][move].mark = ship;

					do {
						printf("This ship is %d tiles long. Please input direction (N/S/E/W): ", ships[j]);
						scanf("%c%*c", &input);
						printf("%c", input);
						offset = 0;
						invalid = 0;

						switch (input){
							case 'N':
							case 'n':
								increment = -10;
								break;
							case 'S':
							case 's':
								increment = 10;
								break;
							case 'E':
							case 'e':
								increment = 1;
								break;
							case 'W':
							case 'w':
								increment = -1;
								break;
							default:
								printf("Invalid entry.");
								invalid = 1;
								break;
						}
						if (invalid == 0){
							for (i = 2; i <= ships[j]; i++){
								printf("Offset: %d", offset);
								offset+=increment;
								if ((move+offset) < 0 || (move+offset) > SIZE || boards[user][move+offset].mark == ship){
									invalid = 1;
									printf("%d", offset);
									printf("Invalid move. ");
									break;
								} else {
									buffer[i-2] = move+offset;
									printf("Offset: %d", offset);
								}
							}
							
							if (invalid == 0){
								for (i = 2; i <= ships[j]; i++){
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
					
					for (i = 0; i < BOARDS; i++){
						printBoard(boards[i], SIZE);
					}
				}
			}
			
			// Game starts here
			
				
			selector ^= 1;
			game_over = 1;
		}
		
		freeBoards(boards, BOARDS);
		free(players);
	}
	
	return 0;
}
