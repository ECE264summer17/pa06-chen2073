#include <stdlib.h>
#include <stdio.h>
#include "maze.h"

#ifndef READMAZE_OFF
Maze * readMaze(char * mazeFilename) {

int row=0, col=0;

FILE * f = fopen(mazeFilename, "r");
fseek(f, 0, SEEK_SET);
int fptr = fgetc(f);

Maze * labyrinth = (Maze *) malloc(sizeof(*labyrinth));

	//count the row and column size
	while(fptr != EOF){

		if(fptr == '\n')
			row++;
		
		else if(row == 0)
			col++;

	fptr = fgetc(f);}

	//maze row and column size
	labyrinth->width = col;
	labyrinth->height = row;

	//allocate space for 2-D array	
	labyrinth->maze = (MazeSquare * * ) malloc(sizeof(MazeSquare * ) * row);
	
	if(labyrinth->maze == NULL)
		return NULL;

	int i;
	for (i=0; i < row; i++){
		(labyrinth->maze)[i] = (MazeSquare * ) malloc(sizeof(MazeSquare) * col);} 
		
	//assign file character to 2-D array
	fseek(f, 0, SEEK_SET);

	int j; 
	for(i=0; i < row; i++){
		for(j=0; j <= col; j++){

			int k = fgetc(f);
			if(k != '\n'){
				(labyrinth->maze)[i][j].type = k;
				(labyrinth->maze)[i][j].visited = false;}
		}
	}

	//locate start and end position
	fseek(f, 0, SEEK_SET);

	for(i=0; i < row; i++){
		for(j=0; j <= col; j++){

			int k = fgetc(f);
			if(k == 's'){
				labyrinth->start.xpos = i;
				labyrinth->start.ypos = j;}
		
			if(k == 'e'){
				labyrinth->end.xpos = i;
				labyrinth->end.ypos = j;} 
		}
	}
	

	//test section
	//printf("\n");
	//printf("height:%d, width:%d\n", labyrinth->height, labyrinth->width);
	//printf("start(%d, %d), end(%d, %d)\n", labyrinth->start.xpos, labyrinth->start.ypos, labyrinth->end.xpos, labyrinth->end.ypos);

	fclose(f);	
	
	return labyrinth;
}
#endif //#ifndef READMAZE_OFF

#ifndef FREEMAZE_OFF
void freeMaze(Maze * m) {
	//1. Free each of the "rows" of the maze
	int i;
	for(i=0; i < (m->height); i++){
		free( (m->maze)[i] );}

	//2. Free the "spine" of the array
	free(m->maze);
}
#endif //#ifndef FREEMAZE_OFF
