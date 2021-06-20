#include "GameOfLife.h"
#include <iostream>
#include <omp.h>
#include <math.h>
//! A constructor
/*!
	Game of life will init here with the width and height 
*/
GameOfLife::GameOfLife(const int w, const int h) : width(w), height(h)
{
	grid = new bool *[width];
	tempGrid = new bool *[width];

	for (size_t i = 0; i < width; ++i)
	{
		grid[i] = new bool[height];
		tempGrid[i] = new bool[height];
	}

	srand((unsigned)time(NULL));
};
//! A destructor
/*!
	Game of life will delete variable after run finishes via function delete
*/
GameOfLife::~GameOfLife()
{
	for (size_t i = 0; i < width; ++i)
	{
		delete[] grid[i];
		delete[] tempGrid[i];
	}

	delete[] grid;
	delete[] tempGrid;
}
//! A function variable
    /*!
      The element of grid will be initialized 
	  default probality = 0.1
    */
void GameOfLife::randomInit(const double probability)
{
	for (size_t i = 0; i < width; ++i)
	{
		for (size_t j = 0; j < height; ++j)
		{
			double r = (double)rand() / RAND_MAX;
			//std::cout << r;
			if (r < probability)
			{
				grid[i][j] = 1; /// lives
			}
			else
			{
				grid[i][j] = 0; /// die
			}
			// grid[i][j] = (r < probability) == 0 ? false : true; // grid will be true or false
		}
	}
	// printGrid();
}
//! Interator function
/*! This function runs 2 for loop to represent the grid by the caculating of neighbors
 *  and redisplay this grid by the function glutredisplay
 * I am using in this function also OPENMP to enhance the speed of proramm
 * atomic to avoid race of coditions  or reduction https://www.bu.edu/tech/files/2017/09/OpenMP_2017Fall.pdf
 * start = omp_get_wtime();
 * end = omp_get_wtime();
 * printf("time: %f\n", end - start); ex: https://github.com/almazhankapan/game-of-life/blob/main/game_of_life.c
 * 
 * https://www.ibm.com/docs/en/xl-c-aix/13.1.2?topic=processing-pragma-omp-taskwait
 * */
void GameOfLife::iterate()
{
	// std::cout << "w in iterate " << width ;

	bool **temporary = new bool *[width];

	for (size_t i = 0; i < width; ++i)
	{
		temporary[i] = new bool[height];
	}

	// omp_set_num_threads(16);
	// int nProcessors = omp_get_max_threads();
	// std::cout << "nProcessors. " << nProcessors ;
	// printf("nProcessors: %d\n",nProcessors);

#pragma omp parallel for
	for (size_t i = 0; i < width; ++i)
	{
		for (size_t j = 0; j < height; ++j)
		{
			// Edges
			if (i == 0 || i == (width - 1) || j == 0 || j == (height - 1))
			{
				// grid[i][j] = grid[i][j];
			}
			else
			{
				int neighbors = countNeighbors(i, j);
				//#pragma omp critical
				if (grid[i][j] == true)
				{
					if (neighbors == 2 || neighbors == 3)
					{
						// element survives
						temporary[i][j] = 1;
					}
					else
					{
						// element dies
						temporary[i][j] = 0;
					}
				}
				else
				{
					if (neighbors == 3)
					{
						// element is born
						temporary[i][j] = 1;
					}
					else
					{
						// element empty
						temporary[i][j] = 0;
					}
				}
			}
		}
	}

	bool **t = grid;
	grid = temporary;
	temporary = t;

	// free temporary
	for (size_t i = 0; i < width; ++i)
	{
		delete[] temporary[i];
	}
}

//! A function variable
    /*!
      Count the number of Neighbors without itself
	  not count the edges of grid , see above code in the funtion iterator
    */
int GameOfLife::countNeighbors(int x, int y)
{
	int neighbors = 0;
	neighbors += grid[x - 1][y - 1];
	neighbors += grid[x][y - 1];

	neighbors += grid[x + 1][y - 1];
	neighbors += grid[x + 1][y];
	neighbors += grid[x + 1][y + 1];

	neighbors += grid[x][y + 1];
	neighbors += grid[x - 1][y + 1];
	neighbors += grid[x - 1][y];

	return neighbors;
}

//! A function variable
    /*!
      get Element at position
	  return value of element
    */
bool GameOfLife::getElement(const int x, const int y)
{
	return grid[x][y];
}

//! A function variable
    /*!
      set Element at position with value
	  return true
    */
bool GameOfLife::setElement(int x, int y, int value)
{
	grid[x][y] = value;
	return true;
}

///! A function variable
    /*!
      just print value and position of function
    */
void GameOfLife::printGrid()
{
	for (size_t i = 0; i < width; ++i)
	{
		for (size_t j = 0; j < height; ++j)
		{
			std::cout << "position: " << i << "," << j;
			std::cout << " is ";
			std::cout << grid[i][j] << std::endl;
		}
	}
}