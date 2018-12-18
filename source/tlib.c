#include "tiles.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


struct Tile *makeBoard(int count) {
	struct Tile *board = malloc(sizeof(struct Tile) * count);
	int i;

	for (i = 0; i < count; i++) {
		board[i].mark = ' ';
	}

	return board;
}

struct Player *makePlayers(int count) {
	struct Player *players = malloc(sizeof(struct Player) * count);
	int i, j;

	for (i = 0; i < count; i++) {
		players[i].moves = malloc(sizeof(int) * 5);
		players[i].moveCount = 5;
		
		for (j = 0; j <= 5; j++) {
			players[i].moves[j] = -1;
		} 
	}

	return players;
}

void clearKeyboard(void)
{
    while (getchar() != '\n')   ; // empty execution code block on purpose
}

void pauseForInput(void) {
	printf("(Press Enter to Continue)");
	clearKeyboard();
}

void printBoard(struct Tile *board, int size) {
	int i, j;
	double dRows = sqrt((double)size);
	int rows = (int)dRows;

	printf("\n   ");
	for (i = 0; i < rows; i++) {
		printf(" %d  ", i);
	}

	for (i = 0; i < size; i+=rows) {
		printf("\n   ");

		for (j = 0; j < rows; j++) {
			printf("----");
		}
		/*
		printf("\n  |");
		for (j = 0; j < rows; j++) {
			printf("     |");
		}
		*/
		printf("\n%d |", i/rows);
		for (j = 0; j < rows; j++) {
			printf(" %c |", board[i+j].mark);	
		}
		/*
		printf("\n  |");
		for (j = 0; j < rows; j++) {
			printf("     |");
		}
		*/
	} 

	printf("\n   ");
	for (j = 0; j < rows; j++) {
		printf("----");
	}

	return;
}

int inputMove(int SIZE) {
	int input, row, col, index;
	int length = sqrt(SIZE);
	char garbage;

	scanf("%d%c", &input, &garbage);

	col = input/10;
	row = input%10;
	index = row*length+col;

	return index;
}

int contains(int needle, int *haystack) {
	int i;
	size_t length = sizeof(haystack)/sizeof(haystack[0]);

	for (i = 0; i <= length; i++) {
		if (haystack[i] == needle) {
			return 1;
		}
	}

	return 0;
}



void printArr(int arr[]) {
	int i;
	int size = 5;
	for (i = 0; i <= size - 1; i++) {
		printf("%d", arr[i]);
	}
	return;
}

int countTiles(struct Tile *board, char c, int SIZE) {
	int i, count = 0;
	for (i = 0; i<SIZE; i++) {
		if (board[i].mark == c) {
			count++;
		}
	}
	return count;
}

void freeBoards(struct Tile **boards, int BOARDS) {
	int i;
	for (i = 0; i < BOARDS; i++) {
		free(boards[i]);
	}

	free(boards);
	return;
}
