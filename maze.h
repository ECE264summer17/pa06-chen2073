#ifndef _MAZE_H_
#define _MAZE_H_

#include <stdbool.h>


//Maze square
typedef struct MazeSquare {
	char type;
	bool visited;
} MazeSquare;

//Maze position
typedef struct MazePos {
	int xpos;
	int ypos;
} MazePos;

//Maze structure
typedef struct Maze {
	MazeSquare * * maze; //2D array holding maze
	int width; //Number of columns in maze
	int height; //Number of rows in maze
	MazePos start; //Location of 's'
	MazePos end; //Location of 'e'
} Maze;

/*
Allocate Maze structure, read in and build maze from mazeFilename, return maze

Make sure that you get the coordinates of your maze correct. Please pay
careful attention to the README's discussion of 2D array coordinates vs.
cartesian coordinates.

The layout of the file is as follows:

Each character represents one "square" of the maze:
's': the starting square
'e': the ending square
'#': a wall
'.': an empty square you can move through

You can assume the file is formatted correctly (you do not have to check for
poorly formatted files). 

Arguments:
mazeFilename: name of file where maze data is stored

Return:
NULL if readMaze fails to successfully allocate and initialize a Maze
Pointer to an initialized Maze structure otherwise.
*/ 
Maze * readMaze(char * mazeFilename);

/*
Deallocate the MazeSquare array

Arguments:
m: pointer to the maze whose MazeSquare should be deallocated

DO NOT call free(m) in this function
*/
void freeMaze(Maze * m);

#endif
