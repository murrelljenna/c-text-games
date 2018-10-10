/*
 * To Do:
 *
 *  - Make contains() function automatically detect size of pointer.
 *	- Eliminate TICTACTOE_PLAYER_LENGTH
 *
 *
 *
 */

struct Tile{
	char mark;
	int owner;
};

struct Player{
	int *moves; 
};

struct Tile *makeBoard(int count); 
struct Player *makePlayers(int count);
void printBoard(struct Tile *board);
int inputMove(int pNo);
int contains(int needle, int *haystack);
int checkVictory(struct Player player);
int checkTie(struct Tile *board);
void printArr(int arr[]);


#define TICTACTOE_PLAYER_LENGTH 5
