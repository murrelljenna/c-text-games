#include "tiles.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct Tile *makeBoard(int count){
	struct Tile *board = malloc(sizeof(struct Tile) * count);
	int i;

	for (i = 0; i < count; i++){
		board[i].mark = ' ';
	}

	return board;
}

struct Player *makePlayers(int count){
	struct Player *players = malloc(sizeof(struct Player) * count);
	int i, j;

	for (i = 0; i < count; i++){
		players[i].moves = malloc(sizeof(int) * 5);
		players[i].moveCount = 5;
		
		for (j = 0; j <= 5; j++){
			players[i].moves[j] = -1;
		} 
	}

	return players;
}

void printBoard(struct Tile *board, int size){
	int i, j;
	double dRows = sqrt((double)size);
	int rows = (int)dRows;

	printf("\n   ");
	for (i = 0; i < rows; i++){
		printf("   %d    ", i);
	}

	for (i = 0; i < size; i+=rows){
		printf("\n   ");

		for (j = 0; j < rows; j++){
			printf("--------");
		}

		printf("\n  |");
		for (j = 0; j < rows; j++){
			printf("       |");
		}

		printf("\n%d |", i/rows);
		for (j = 0; j < rows; j++){
			printf("   %c   |", board[i+j].mark);	
		}

		printf("\n  |");
		for (j = 0; j < rows; j++){
			printf("       |");
		}
		
	} 

	printf("\n   ");
	for (j = 0; j < rows; j++){
		printf("--------");
	}

	printf("\n");
	return;
}

int inputMove(int pNo){
	int input, row, col, index;
	char garbage;

	printf("\nPlayer %d, please input your column & row (CR): ", pNo);
	scanf("%d%c", &input, &garbage);

	col = input/10;
	row = input%10;
	index = row*3+col;

	return index;
}

int contains(int needle, int *haystack){
	int i;
	size_t length = sizeof(haystack)/sizeof(haystack[0]);

	for (i = 0; i <= length; i++){
		if (haystack[i] == needle){
			return 1;
		}
	}

	return 0;
}

int checkVictory(struct Tile *board, char mark){
	if (board[0].mark == mark){
		if ((board[1].mark == mark && board[2].mark == mark) || (board[3].mark == mark && board[6].mark == mark) || (board[4].mark == mark && board[8].mark == mark)) {
			return 1;
		}
	}
	if (board[1].mark == mark){
		if (board[4].mark == mark && board[7].mark == mark){
			return 1;
		}
	}
	if (board[2].mark == mark){
		if ((board[5].mark == mark && board[8].mark == mark) || (board[4].mark == mark && board[6].mark == mark)){
			return 1;
		}
	}
	if (board[3].mark == mark){
		if (board[4].mark == mark && board[5].mark == mark){
			return 1;
		}
	}
	if (board[6].mark == mark){
		if (board[7].mark == mark && board[8].mark == mark){
			return 1;
		}
	}
	
	return 0;
}

int checkTie(struct Tile *board){
	int i, counter;
	for (i = 0; i < 9; i++){
		if (board[i].mark == ' '){
			return 0;
		}
	}
	return 1;
}

void printArr(int arr[]){
	int i;
	int size = 5;
	for (i = 0; i <= size - 1; i++){
		printf("%d", arr[i]);
	}

	return;
}


