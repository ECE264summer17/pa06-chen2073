#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "path.h"
#include "solver.h"

int main(int argc, char ** argv) {
	if (argc != 2) {
		fprintf(stderr, "Wrong number of command line args\n");
		fprintf(stderr, "Usage: ./pa06 mazeFile \n");
		return EXIT_FAILURE;
	}
	
	Maze * m = readMaze(argv[1]);
	
	if (m == NULL) {
		return EXIT_FAILURE;
	}

	char * path = solveMaze(m);
	
	if (checkPath(m, path)) { // function defined in path.o
		printf("Success!\n");
	} else {
		printf("Failure!\n");
	}
	
	//Clean up memory
	freeMaze(m);
	free(m);
	free(path);
	
	return EXIT_SUCCESS;
}
