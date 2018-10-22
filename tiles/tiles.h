/*
 * To Do:
 *
 * - Change player-side victory checking to board-side checking.
 *
 *
 */

struct Tile{
	char mark;
	int owner;
};

struct Player{
	int *moves;
	int moveCount; 
};

struct Tile *makeBoard(int count); 
struct Player *makePlayers(int count);
void printBoard(struct Tile *board, int size);
int inputMove(int pNo);
int contains(int needle, int *haystack);
int checkVictory(struct Tile *board, char mark);
int checkTie(struct Tile *board);
void printArr(int arr[]);


#define TICTACTOE_PLAYER_LENGTH 5
