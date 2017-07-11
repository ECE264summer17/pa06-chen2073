#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "solver.h"

char * solveMaze(Maze * m) {
	char * retval = malloc(sizeof(char) * ((m->width * m->height) + 1));

	MazePos mp = {.xpos = m->start.xpos, .ypos = m->start.ypos};   //initialze start as current position
	
	
	
	if( depthFirstSolve(m, mp, retval, 0) == false)
		{retval[0] = '\0';}

	else{
		depthFirstSolve(m, mp, retval, 0);}

	return retval;
}

bool depthFirstSolve(Maze * m, MazePos curpos, char * path, int step) {
	
	if(curpos.xpos == m->end.xpos && curpos.ypos == m->end.ypos) //check if == end position
		{	path[step] = '\0';
			//printf("step: %d\n" step);
			return true;}	

	if ( ( (curpos.xpos < 0) || (curpos.xpos >= (m->height) ) ) || ((curpos.ypos >= (m->width)) || (curpos.ypos < 0) ) ) //out of bounds
		{return false;}

	if ((m->maze)[curpos.xpos][curpos.ypos].type == '#') //reaches wall
		{return false;}

	if ((m->maze)[curpos.xpos][curpos.ypos].visited == true) //already visited
		{return false;}

			
		(m->maze)[curpos.xpos][curpos.ypos].visited = true; //update visited
		
		//printf("X: %d, Y: %d\n", curpos.xpos, curpos.ypos); //REMOVE BEFORE SUBMITTING!!!!!!!
		
		MazePos temp = curpos;
		temp.xpos = temp.xpos - 1;

		
		if( depthFirstSolve(m, temp, path, step+1) == true ) //check north
			
			{	path[step] = 'n'; //write path
				return true;} 	//recusion		

		temp = curpos;
		temp.ypos = temp.ypos + 1;

		if( depthFirstSolve(m, temp, path, step+1) == true ) //check east
			
			{	path[step] = 'e'; //write path
				return true;} 	//recusion
		
		temp = curpos;
		temp.xpos = temp.xpos + 1;

		if( depthFirstSolve(m, temp, path, step+1) == true ) //check south
			
			{	path[step] = 's'; //write path
				return true;} 	//recusion

		temp = curpos;
		temp.ypos = temp.ypos - 1;

		if( depthFirstSolve(m, temp, path, step+1) == true ) //check west
			
			{	path[step] = 'w'; //write path
				return true;} 	//recusion

	return false;}
	


	/* if( ((curpos.ypos+1) < (m->width)) && ((m->maze)[curpos.xpos][curpos.ypos+1].visited == false) && ((m->maze)[curpos.xpos][curpos.ypos+1].type != '#'))	//check east of current position
		{
		

		++curpos.ypos;	//update position

		
		(m->maze)[curpos.xpos][curpos.ypos].visited = true;	//update visited
		
		if( depthFirstSolve(m, curpos, path, ++step) == true )
			{path[step] = 'E';
			return true;} }//recusion
		
		else {return false;}

	 if( ((curpos.xpos+1) < (m->height)) && ((m->maze)[curpos.xpos+1][curpos.ypos].visited == false) && ((m->maze)[curpos.xpos+1][curpos.ypos].type != '#') ) //check south
		
		{++curpos.xpos;	//update position
		
		
		(m->maze)[curpos.xpos][curpos.ypos].visited = true;	//update visited
		
		if( depthFirstSolve(m, curpos, path, ++step) == true )
			
			{path[step] = 'S';
			return true;} }//recusion

		else {return false;}


	 if( ((curpos.ypos-1) >= 0) && ((m->maze)[curpos.xpos][curpos.ypos-1].visited == false) && ((m->maze)[curpos.xpos][curpos.ypos-1].type != '#'))	//check west of current position
		{
		--curpos.ypos;	//update position
		

		(m->maze)[curpos.xpos][curpos.ypos].visited = true;	//update visited
		
		if( depthFirstSolve(m, curpos, path, ++step) == true )
			{path[step] = 'W';
			return true;} }//recusion
		
		else {return false;}
	 
	if( ((curpos.xpos-1) < (m->height)) && ((m->maze)[curpos.xpos-1][curpos.ypos].visited == false) && ((m->maze)[curpos.xpos-1][curpos.ypos].type != '#') ) //check north
		
		{++curpos.xpos;	//update position
		
		
		(m->maze)[curpos.xpos][curpos.ypos].visited = true;	//update visited
		
		if( depthFirstSolve(m, curpos, path, ++step) == true )
			
			{path[step] = 'S';
			return true;} }//recusion

		else {return false;}	
*/

