#include "GameOfLife.h"
#include <iostream>
#include <omp.h>
#include <math.h>

double squareRoot(const double a)
{
	double b = sqrt(a);
	if (b != b) // NaN check
	{
		return -1.0;
	}
	else
	{
		return sqrt(a);
	}
}

GameOfLife::GameOfLife(const int w, const int h) : width(w), height(h)
{
	grid = new bool *[width];
	tempGrid = new bool *[width];

	for (size_t i = 0; i < width; ++i)
	{
		grid[i] = new bool[height];
		tempGrid[i] = new bool[height];
	}

	xdomain = new int[3];
	ydomain = new int[3];

	srand((unsigned)time(NULL));
};

GameOfLife::~GameOfLife()
{
	for (size_t i = 0; i < width; ++i)
	{
		delete[] grid[i];
		delete[] tempGrid[i];
	}

	delete[] grid;
	delete[] tempGrid;

	delete[] xdomain;
	delete[] ydomain;
}

// default probality = 0.1
void GameOfLife::randomInit(const double probability)
{
	for (size_t i = 0; i < width; ++i)
	{
		for (size_t j = 0; j < height; ++j)
		{
			double r = (double)rand() / RAND_MAX;
			//std::cout << r;
			if(r < probability){
				grid[i][j] = 1;
			}else{
				grid[i][j] = 0;
			}
			// grid[i][j] = (r < probability) == 0 ? false : true; // grid will be true or false
		}
	}
	// printGrid();

}
// none parallel ; 1 min
/** This function runs 2 for loop to represent the grid by the caculating of neighbors
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

	// bool **temporary = new bool *[width];

	// for (size_t i = 0; i < width; ++i)
	// {
	// 	temporary[i] = new bool[height];
	// }

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
			if( i == 0 || i == (width - 1) || j == 0 || j == (height -1) ){
				// grid[i][j] = grid[i][j];
			}else{
				int neighbors = countNeighbors(i, j);
				//#pragma omp critical
							if (grid[i][j] == true)
							{
								if (neighbors == 2 || neighbors == 3)
								{
									// element survives
									grid[i][j] = 1;
								}
								else
								{
									// element dies
									grid[i][j] = 0;
								}
							}
							else
							{
								if (neighbors == 3)
								{
									// element is born
									grid[i][j] = 1;
								}
								else
								{
									// element empty
									grid[i][j] = 0;
								}
							}
			}
		}
	}

	// bool **t = grid;
	// grid = temporary;
	// temporary = t;

	// // free temporary
	// for (size_t i = 0; i < width; ++i)
	// {
	// 	delete[] temporary[i];
	// }
}
// not count the edges of grid , see above code in the funtion iterator
int GameOfLife::countNeighbors(int x, int y)
{
	/**
	// int neighbors = 0;

	// // if cursor out site , we will move previous 1 step
	// xdomain[0] = (x == 0 ? width - 1 : x - 1);
	// xdomain[1] = x;
	// xdomain[2] = (x == width - 1 ? 0 : x + 1);

	// ydomain[0] = (y == 0 ? height - 1 : y - 1);
	// ydomain[1] = y;
	// ydomain[2] = (y == height - 1 ? 0 : y + 1);

	// for (size_t i = 0; i < 3; ++i)
	// {
	// 	for (size_t j = 0; j < 3; ++j)
	// 	{
	// 		if (!(xdomain[i] == x && ydomain[j] == y))
	// 		{ // not cout the element of x and y
	// 			if (grid[xdomain[i]][ydomain[j]])
	// 			{
	// 				++neighbors;
	// 			}
	// 		}
	// 	}
	// }

	// return neighbors;
	*/
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

bool GameOfLife::getElement(const int x, const int y)
{
	return grid[x][y];
}

bool GameOfLife::setElement(int x, int y, bool value){
	grid[x][y] = value;
	return true;
}

// echo element of Grid
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
