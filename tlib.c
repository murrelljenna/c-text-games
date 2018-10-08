#include "tiles.h"
#include <stdlib.h>
#include <stdio.h>

struct Tile *makeBoard(int count){
	struct Tile *board = malloc(sizeof(struct Tile) * count);

	int i;
	for (i = 0; i < count; i++){
		board[i].mark = ' ';
	}

	return board;
}

void printBoard(struct Tile *board){
	printf("     0     1     2   \n");
	printf("   -----------------\n");
	printf("  |     |     |     |\n");
	printf("0 |  %c  |  %c  |  %c  |\n", board[0].mark, board[1].mark, board[2].mark);
	printf("  |     |     |     |\n");
	printf("   -----------------\n");
	printf("  |     |     |     |\n");
	printf("1 |  %c  |  %c  |  %c  |\n", board[3].mark, board[4].mark, board[5].mark);
	printf("  |     |     |     |\n");
	printf("   -----------------\n");
	printf("  |     |     |     |\n");
	printf("2 |  %c  |  %c  |  %c  |\n", board[6].mark, board[7].mark, board[8].mark);
	printf("  |     |     |     |\n");
	printf("   -----------------\n");

	return;
}

int inputMove(int pNo){
	int input, row, col, index;

	printf("Player %d, please input your column & row (CR): ", pNo);
	scanf("%d", &input);

	col = input/10;
	row = input%10;
	index = row*3+col;

	return index;
}

int contains(int needle, int *haystack, int length){
	int i;
	for (i = 0; i <= length; i++){
		if (haystack[i] == needle){
			return 1;
		}
	}

	return 0;
}

int checkVictory(int player[]){
	if (contains(0, player, TICTACTOE_PLAYER_LENGTH)){
		if ((contains(1, player, TICTACTOE_PLAYER_LENGTH) && contains(2, player, TICTACTOE_PLAYER_LENGTH)) || (contains(3, player, TICTACTOE_PLAYER_LENGTH) && contains(6, player, TICTACTOE_PLAYER_LENGTH)) || (contains(4, player, TICTACTOE_PLAYER_LENGTH) && contains(8, player, TICTACTOE_PLAYER_LENGTH))) {
			return 1;
		}
	}
	if (contains(1, player, TICTACTOE_PLAYER_LENGTH)){
		if (contains(4, player, TICTACTOE_PLAYER_LENGTH) && contains(7, player, TICTACTOE_PLAYER_LENGTH)){
			return 1;
		}
	}
	if (contains(2, player, TICTACTOE_PLAYER_LENGTH)){
		if ((contains(5, player, TICTACTOE_PLAYER_LENGTH) && contains(8, player, TICTACTOE_PLAYER_LENGTH)) || (contains(4, player, TICTACTOE_PLAYER_LENGTH) && contains(6, player, TICTACTOE_PLAYER_LENGTH))){
			return 1;
		}
	}
	if (contains(3, player, TICTACTOE_PLAYER_LENGTH)){
		if (contains(4, player, TICTACTOE_PLAYER_LENGTH) && contains(5, player, TICTACTOE_PLAYER_LENGTH)){
			return 1;
		}
	}
	if (contains(6, player, TICTACTOE_PLAYER_LENGTH)){
		if (contains(7, player, TICTACTOE_PLAYER_LENGTH) && contains(8, player, TICTACTOE_PLAYER_LENGTH)){
			return 1;
		}
	}

	return 0;
}

void printArr(int arr[]){
	int i;
	int size = 5;
	for (i = 0; i <= size - 1; i++){
		printf("%d", arr[i]);
	}

	return;
}


