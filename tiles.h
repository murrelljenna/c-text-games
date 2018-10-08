struct Tile {
	char mark;
};
struct Tile *makeBoard(int count); 
void printBoard(struct Tile *board);
int inputMove(int pNo);
int contains(int needle, int *haystack, int length);
int checkVictory(int player[]);
void printArr(int arr[]);


#define TICTACTOE_PLAYER_LENGTH 5
