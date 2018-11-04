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
	int userid; 
};

// Game functions in tlib.c

struct Tile *makeBoard(int count); 
struct Player *makePlayers(int count);
void printBoard(struct Tile *board, int size);
int inputMove(int pNo);
int contains(int needle, int *haystack);
int checkVictory(struct Tile *board, char mark);
int checkTie(struct Tile *board);
void printArr(int arr[]);

// Reading/writing functions in pst.c

int fileExists(const char * filename);
int matchPlayers(char filename[], int userid);
int matchOtherPlayer(char filename[], int userid);
char *getLine(int lineNumber, char filename[], int length);
int save(struct Player *players, char filename[], struct Tile *board, int selector, int size);
struct Tile *updateBoard(int lineNumber, char filename[], int length, int size);
int getTurn(int lineNumber, char filename[]);
