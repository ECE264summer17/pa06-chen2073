#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "solver.h"

char * solveMaze(Maze * m) {
	char * retval = malloc(sizeof(char) * ((m->width * m->height) + 1));

	MazePos mp = {.xpos = m->start.xpos, .ypos = m->start.ypos};
	
	depthFirstSolve(m, mp, retval, 0);
	return retval;
}

bool depthFirstSolve(Maze * m, MazePos curpos, char * path, int step) {

	//FILL IN

	return false;
}
