This assignment takes
PA04 one step further. Rather than just reading and writing a maze into a file, this
assignment asks you save the maze in a structure and to *discover* the solution to a maze (if one exists). You
will build on the methods you developed in PA04 (though, we will
provide files that you may use if you don't have a working version of PA04).

Learning Goals
==============

You will learn:

* Nested structures
* More recursion
* Depth first search

Background
==========

Complex Structures
------------------

Up until now, we have mostly dealt with structures whose fields are simple
data types or arrays. But we can also have the fields of a structure be
*another type* like a structure or an enumeration. Consider the types we will
use to define our maze:

```
typedef struct MazeSquare {
	char type;
	bool visited;
} MazeSquare;
```

This is a structure that represents a single square in the maze. It has a
particular type , and a flag that lets
us know whether we've visited this square before or not (useful for checking
if your path has loops).

`type` can have 4 values :

* 's': the starting square
* 'e': the ending square
* '#': a wall
* '.': an empty square you can move through

```
typedef struct MazePos {
	int xpos;
	int ypos;
} MazePos;
```

This is a simple structure that captures the location of a particular square
in a maze.

```
typedef struct Maze {
	MazeSquare * * maze; //2D array holding maze
	int width; //Number of columns in maze
	int height; //Number of rows in maze
	MazePos start; //Location of 's'
	MazePos end; //Location of 'e'
} Maze;
```

This structure represents an entire maze. It has a width and height, it uses
the `MazePos` structure to capture the starting position in the maze and the
ending position in the maze, and it uses a *2D Array* of `MazeSquare`s to
represent the maze grid itself.

Depth first search
------------------

*Depth first search* is one of the most common search strategies and it is one
that lends itself to recursion. Suppose you are standing in the middle of a
maze (sort of like you are in this assignment!) and want to figure out where
the exit is. How might you find your way out?

Here is one strategy: start walking through the maze. Each time you arrive at
a choice of directions, pick one and keep walking. If you reach a dead end, or
get to a part of the maze you've seen before, back up to the last place you
made a choice and make a different one. Eventually, you will either find the
exit of the maze or explore the entire maze and decide that there is no way
out.

Consider trying to find your way out of this maze:

```
.#.#
...#
e#..
#s.#
```

Assume that at each square, we try to go north, then south, then east, then
west.

We start at `s`, and try to go N. We hit a wall, so we back up and try to go
S. We go out of bounds, so we try to go E, which succeeds. We're now in this
situation, where the `*` shows where we are:

```
.#.#
...#
e#..
#s*#
```

We try to go N, which succeeds. We try to go N again, which succeeds. We try
to go N again, which succeeds. We're now in this situation:

```
.#*#
...#
e#..
#s.#
```

We try to go N again, which fails (out of bounds). We try to go S, which fails
(we've already been to that square!), E, which fails (we hit a wall), then W,
which fails (we hit a wall). Since we don't have anywhere to go from here, we
back up to the last place we made a choice:

```
.#.#
..*#
e#..
#s.#
```

Now we try to go N (fails: already been to that square); S (fails: already
been to that square); E (fails: wall); then W (succeeds):

```
.#.#
.*.#
e#..
#s.#
```

Now we try to go N (fails: wall); S (fails: wall); E (fails: already been
there); and W (succeeds):

```
.#.#
*..#
e#..
#s.#
```

We then go N, which succeeds:

```
*#.#
...#
e#..
#s.#
```

From here, there is no successful move to make, so we back up to the last place we made a choice:

```
.#.#
*..#
e#..
#s.#
```

and try the next choice, S, which gets us to the exit!

The reason we call this a depth-first search is that we try each possible path
until we can't keep moving forward, then we back up one choice and try again,
and so forth. Other searches may not explore a single path all the way to the
end before trying a different path.

Depth First Search with Recursion
---------------------------------

Depth first search can be readily solved with recursion. Each recursive call
"visits" a single square in the maze and explores each of the possible paths
leading out from that square. The goal of a sequence of recursive calls is to
explore a specific path through the maze, and each time you call the recursive
function, you're making the path one step longer and visiting one more square
of the maze.

You should interpret your recursive function as implementing the following
logic: "Given all the squares I have visited so far, can I exit the maze by
adding this square to the solution path?"" If the answer is no, that means the
current square is not part of the solution path, and the recursive method
should return false. If the answer is yes, that means the current square *is*
part of the solution path, and you should add the square to the current path
and return true.

The *base case* for a square is that the square represents the *end* of a
path:

1. It has been visited already -- the path can't be extended this way, so return false
2. It is a wall -- this path fails, so return false.
3. It is out of bounds -- this path fails, so return false.
4. It is the exit -- this path succeeds, so return true and add this square as 
  the last square in the path

The *recursive* case for a square is that it doesn't fall into one of the
above four categories: it is an empty square that you haven't visited before.
In that case, the recursive case tries to make the path one step longer by
visiting one more square in the maze: recursively call your search method
*four times*, once for each of the four directions you could possibly move.

So what do you do with the return value of the four recursive calls you make?

1. If one of them returns true, that means the direction that call explores is on the solution path, which also means the *current* square is on the    solution path. Add the current square to the solution path, and return true.
2. If the recursive call returns false, that means that direction doesn't 
  work, so move on to the next recursive call.
3. If *all* the recursive calls return false, that means the *current* square 
  can't be on the solution path, so return false.
  
(Don't forget to mark the current square as visited when the recursive method
returns!)

Note that this recursive function follows the usual pattern: it calls itself
and *assumes those calls do the right thing*.

2D Array Coordinates vs. Cartesian Coordinates
----------------------------------------------

Note that 2D arrays (and matrices) work very differently than Cartesian
coordinates. Suppose you have a 2D grid of letters:

```
a b c d
e f g h
i j k l
```

Then your 2D grid has 4 columns (width = 4) and 3 rows (height = 3) You should
thus create a 2D array with 3 rows and 4 columns (note that with arrays we
list the rows first, then the columns).

The coordinate system we use for 2D arrays (and matrices) is different than
Cartesian coordinates.

In Cartesian coordinates, `(0, 0)` is at the bottom left of the grid (the
letter 'i'). In 2D arrays (and matrices), `[0][0]` is at the top left of the
grid (the letter 'a').

In Cartesian coordinates, we list the x position first and then the y
position. For 2D arrays (and matrices), we list the y position (the row) first
and then the x position (the column).

In Cartesian coordinates, incrementing the "y" position moves *up*. In 2D
arrays (and matrices), incrementing the row number moves *down* (the first row
is row 0, the second row is row 1, etc.).

So in Cartesian coordinates, `(2, 3)` would represent the letter 'b', but in
2D arrays, `[2][3]` would represent the letter 'l'.


What do you need to do?
=======================

We have provided `pa06.c`, `maze.h` for you. You will need to
fill in `maze.c` with the functions specified. 

* `maze.c` has two functions: `readMaze`, which reads in the maze data from an
  input file and builds a Maze structure (don't forget to initialize the
  starting and ending positions!) and `freeMaze` which deallocates the 2D
  array holding the maze. 
  
You should build on the functions you wrote in pa04.
  
  
You also need to write *one method*, `depthFirstSolve` in
`solver.c`. `depthFirstSolve` is called by `solveMaze`, as you can see in the
code, and is meant to be the recursive method that implements the logic
described above. It takes four arguments:

1. `Maze * m`: the maze you are trying to solve.
2. `MazePos curPos`: the current square in the maze being "visited."
3. `char * path`: a character array containing the current path. This path 
  should match the format of the path from PA07 (i.e., it should be a 
  null-terminated string with a sequence of directions to move).
4. `int step`: a counter telling you how far along the current path you are.

and returns a boolean: `true` means that the current square being visited by
`depthFirstSolve` *is* part of the solution, and `false` means that current
square *is not* part of the solution.

The path string is formatted as a sequence of characters: 'n' for north (move
up), 's' for south (move down), 'e' for east (move right), 'w' for west (move
left). Don't forget that in 2D array coordinates, moving *up* means
*decrementing* the row you are at, and moving *down* means *incrementing* the
row you are at.

`For maze1 given in input folder, string "enennn" should be stored in path. Note that \0 (null terminating character) is added at the end of the string.` 

One tricky bit here is figuring out how to update `path` correctly. Two hints:
(i) `step` tells you how far along in the current path you are; and (ii) if
you successfully exit the maze on the `n`th step, `path[n]` should be `\0`.

**Warning:** This assignment will probably have the highest ratio of *time spent thinking about what code to write* to *amount of code written* of any
assignment so far. Recursive code is often quite short -- the instructors'
version of `depthFirstSolve` has about 25 lines of code -- but takes a while
to get right. Start thinking about your solution now, and don't be afraid to
ask questions on Piazza or in office hours to make sure your logic is right.

Testing your code
-----------------

Depending on the order you choose to do your recursion (do you decide to look
North first, or South first, etc) you can get a different path than someone
else if a maze has many paths to the exit! How can you test if your path is correct?
You need a path checker to see if your path is correct or not.You can use that
to verify if the path you create is valid or not. To check that you should compile your progarm with `path.o` which provides a funtion named `checkPath` to check if your
path is valid or not. We have provided 'pa06.c' with appropriate functions to test your code. If your functions are correct it should print `Success` for valid mazes and `Failure` for invalid mazes on the console.

You should compile your files with following command :

> gcc -std=c99 -g -Wall -Wshadow -Wvla -Wunreachable-code -Werror pa06.c maze.c solver.c path.o -o pa06


Do not forget to add null terminating character '\0' at the end of path string. `checkPath` function inside path.o will not work correctly unless you have null terminating character at the end.

We have provided several mazes for you. `maze1`, `maze3` and `maze4` have
valid solutions, while `maze2` and `maze5` do not.

Also check that your program does not produce any errors while running with valgrind. 40 % points will be deducted for any valgrind error.


What do you need to turn in?
----------------------------

Turn in your version of `maze.c` and `solver.c`, with your implementation of
`depthFirstSolve`. You do not need to submit any other files.

