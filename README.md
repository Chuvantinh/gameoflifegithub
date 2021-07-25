# Conway's Game of Life in GLUT/OpenGL

## Rules
* an organism with 0, 1, 4, 5, 6, 7 or 8 neighbors dies
* an organism with 2 or 3 neighbors survives
* organisms are born in empty cells with 3 neighbors

## Configuration File

Some game variables can be changed using a configuration file like `game.config` (configuration file reading is powered by Richard J. Wagner's [ConfigFile](http://ai.stanford.edu/~gal/Code/FindMotifs/ConfigFile.h)). The configuration file is passed as an argument to the executable:

`./game game.config`

The example configuration lists all the possible configurations each accompanied by a small explanation.

## Compilation

The included makefile can be used to compile the code. To compile and run the code type `make` in your terminal. `make compile will compile the code but not run it.
## doxygen
file config: https://gist.githubusercontent.com/ugovaretto/261bd1d16d9a0d2e76ee/raw/63acd4081fdcfebf091f4110d91f91d40cf4f782/Doxyfile
doxygen -g dconfig create file config
doxygen dconfig run in the project

## openmp attention
A variable in an OpenMP parallel region can be either shared or private.
If a variable is SHARED, then there exists one instance of this variable which is shared among all threads.
If a variable is PRIVATE, then each thread in a team of threads has its own local copy of the private variable.

Default (shared)
The default(shared) clause sets the data-sharing attributes of all variables in the construct to shared. In the following example
int a, b, c, n;
...

#pragma omp parallel for default(shared)
for (int i = 0; i < n; i++)
{
    // using a, b, c
}
a, b, c and n are shared variables.

1. lock and unlock
2. ATOMIC

how to run

mp:
	gcc src/main.cpp src/GameOfLife.cpp -g -o src/game -lOpenCL -lglut -lGLEW -lGLU -lGL -fopenmp -lstdc++ -lm

dmp:
	valgrind --tool=helgrind src/game

cl:
	gcc opencl/gol.cpp -o opencl/gol -g -lOpenCL -lglut -lGLEW -lGLU -lGL -fopenmp -lstdc++ -lm

dcl:
	valgrind --tool=helgrind ./opencl/gol
