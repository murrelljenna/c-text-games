#include "tiles.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
char *getLine(int lineNumber, char filename[], int length){
	return NULL;
}

int save(char filename[], struct Tile *board, int selector, int size){
	FILE* file = fopen(filename, "w");
	
	fprintf(file, "%d\n", selector);

	int i;	
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

