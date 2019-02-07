#ifndef TILES_H
#define TILES_H

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
int inputMove(int SIZE);
int contains(int needle, int *haystack);
void printArr(int arr[]);
void clearKeyboard(void);
void pauseForInput(void);

// Reading/writing functions in pst.c

int fileExists(const char * filename);
int matchPlayers(char filename[], int userid);
int matchOtherPlayer(char filename[], int userid);
char *getLine(int lineNumber, char filename[], int length);
int save(struct Player *players, char filename[], struct Tile **boards, int selector, int size, int BOARDS);
struct Tile **updateBoard(char filename[], int SIZE, int BOARDS);
int getTurn(int lineNumber, char filename[]);
int countTiles(struct Tile *board, char c, int SIZE);
void freeBoards(struct Tile **boards, int BOARDS);

// Game specific functions

int checkVictoryTic(struct Tile *board, char mark);
int checkTieTic(struct Tile *board);
int checkVictoryBat(struct Tile **boards, int tileCount);

#endif
