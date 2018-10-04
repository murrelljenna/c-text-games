#include <stdlib.h>
#include <stdio.h>

char printBoard(char board[]){
	printf("     0     1     2   \n");
	printf("   -----------------\n");
	printf("  |     |     |     |\n");	
	printf("0 |  %c  |  %c  |  %c  |\n", board[0], board[1], board[2]);	
	printf("  |     |     |     |\n");	
	printf("   -----------------\n");
	printf("  |     |     |     |\n");	
	printf("1 |  %c  |  %c  |  %c  |\n", board[3], board[4], board[5]);	
	printf("  |     |     |     |\n");	
	printf("   -----------------\n");
	printf("  |     |     |     |\n");	
	printf("2 |  %c  |  %c  |  %c  |\n", board[6], board[7], board[8]);	
	printf("  |     |     |     |\n");	
	printf("   -----------------\n");

	return 0;
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

int contains(int needle, int haystack[]){
	int i;
	size_t size = sizeof(haystack)/sizeof(haystack[0]);
	for (i = 0; i <= size; i++){
		if (haystack[i] == needle){
			return 1;
		}
	}

	return 0;
}

int checkVictory(int player[]){
	if (contains(0, player)){
		if ((contains(1, player) && contains(2, player)) || (contains(3, player) && contains(6, player)) || (contains(4, player) && contains(8, player))) {
			return 1;
		}	
	}
	if (contains(1, player)){
		if (contains(4, player) && contains(7, player)){
			return 1;
		}
	}
	if (contains(2, player)){
		if ((contains(5, player) && contains(8, player)) || (contains(4, player) && contains(6, player))){
			return 1;
		}
	}
	if (contains(3, player)){
		if (contains(4, player) && contains(5, player)){
			return 1;
		}
	}
	if (contains(6, player)){
		if (contains(7, player) && contains(8, player)){
			return 1;
		}
	}
	
	return 0;
}

int printArr(int arr[]){
	int i;
	int size = 5;
	for (i = 0; i <= size - 1; i++){
		printf("%d", arr[i]);	
	}
}

int main(void){
	char board[] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
	char mark;
	int game_over = 0, selector = 0, index = -1, other, move;
	int players[2][5] = { {-1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1} };
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
		
		printBoard(board);

		do {
			move = inputMove(selector);
			if (contains(move, players[selector]) || contains(move, players[other]) || move < 0 || move > 8){
				printf("Invalid move. ");	
			}	

		} while (contains(move, players[selector]) || contains(move, players[other]) || move < 0 || move > 8);
		
		players[selector][index] = move;
		board[players[selector][index]] = mark;

		if (checkVictory(players[selector])){
			game_over == 1;
			
			printBoard(board);
			printf("Player %d wins!\n", selector);

			break;
		}
	
		selector ^= 1;		
	}

	return 0;
}
