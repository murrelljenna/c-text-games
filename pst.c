#include "tiles.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

int fileExists(const char * filename){
    /* try to open file to read */
    FILE *file;
    if (file = fopen(filename, "r")){
        fclose(file);
        return 1;
    }
    return 0;
}

int matchPlayers(char filename[], int userid){
	FILE* file = fopen(filename, "r");
	char line[12];
	int i = 0;
	
	while (fgets(line, sizeof line, file) != NULL && i < 2){
		if (atoi(line) == userid || atoi(line) == 0){
	//		printf("Return: %s, Index: %d", line, i);
			fclose(file);
			return i;
		}
		i++;
	}

	fclose(file);
	
	return -1;

}

int matchOtherPlayer(char filename[], int userid){
	FILE* file = fopen(filename, "r");
	char line[12];
	int i = 0;
	
	while (fgets(line, sizeof line, file) != NULL && i < 2){
		if (atoi(line) != userid && atoi(line) != 0){
			printf("Return: %s, Index: %d", line, i);
			fclose(file);
			return atoi(line);
		}
		i++;
	}

	fclose(file);

	return -1;

}

int save(struct Player *players, char filename[], struct Tile *board, int selector, int size){
	FILE* file = fopen(filename, "w");

	int i;	
	for (i = 0; i < 2; i++){
 		fprintf(file, "%d\n", players[i].userid);
	}
	
	fprintf(file, "%d\n", selector);

	for (i = 0; i < size; i++){
		fprintf(file, "%c", board[i].mark);
	}

	fclose(file);

	return 0;
}

struct Tile *updateBoard(int lineNumber, char filename[], int length, int size){
	FILE* file = fopen(filename, "r");
	char line[12];
	int count = 1;
	
    	while (fgets(line, sizeof line, file) != NULL) /* read a line */
    	{
		if (count == lineNumber)
		{
			break;
		}
		else
		{
			count++;
		}
	}
	fclose(file);
	struct Tile *board = malloc(sizeof(struct Tile) * size);
	
	int i;
	for (i = 0; i < size; i++){
		board[i].mark = line[i];
	}

	return board;
}

int getTurn(int lineNumber, char filename[]){
	FILE* file = fopen(filename, "r");
	char line[10];
	int count = 1, selector;
	
    	while (fgets(line, sizeof line, file) != NULL) 
    	{
		if (count == lineNumber)
		{
			selector = atoi(line);
			break;
		}
		else
		{
			count++;
		}
	}
	
	fclose(file);
	return selector;
}

