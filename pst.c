#include "tiles.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

int callValid(int argc, char filename[]){

}

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
		//	printf("Return: %s, Index: %d", line, i);
			fclose(file);
			return atoi(line);
		}
		i++;
	}

	fclose(file);

	return -1;

}

int save(struct Player *players, char filename[], struct Tile **boards, int selector, int size, int BOARDS){
	FILE* file = fopen(filename, "w");

	int i, j;	
	for (i = 0; i < 2; i++){
 		fprintf(file, "%d\n", players[i].userid);
	}
	
	fprintf(file, "%d", selector);
	
	for (i = 0; i < BOARDS; i++){
		fprintf(file, "\n");
		for (j = 0; j < size; j++){
			fprintf(file, "%c", boards[i][j].mark);
		}
	}

	fclose(file);

	return 0;
}

struct Tile **updateBoard(char filename[], int SIZE, int BOARDS){
	FILE* file = fopen(filename, "r");
	char line[SIZE+1];
	int count = 1, target, i;
	struct Tile **boards = malloc((sizeof(struct Tile) * SIZE) * BOARDS);
	for (i = 0; i < BOARDS; i++){
		boards[i] = makeBoard(SIZE);
	}

	for (target = 4; target < (BOARDS + 4); target++){
		while (fgets(line, sizeof line, file) != NULL) /* read a line */
		{
			if (count == target)
			{
				//printf("Entered: %d\n", target);
				//printf("Content: %s\n", line);
				for (i = 0; i < SIZE; i++){
					boards[target-4][i].mark = line[i];
				}

				break;
			}
			else
			{
				count++;
				//printf("Count: %d\n", count);
			}
		}

	}

	fclose(file);
	return boards;
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

