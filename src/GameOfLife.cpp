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
	tempGrid = new bool *[width * width];

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

	// bool **temporary = new bool *[width];

	// for (size_t i = 0; i < width; ++i)
	// {
	// 	temporary[i] = new bool[height];
	// }

	// omp_set_num_threads(16);
	// int nProcessors = omp_get_max_threads();
	// std::cout << "nProcessors. " << nProcessors ;
	// printf("nProcessors: %d\n",nProcessors);
// schedule(static) ordered
// #pragma omp for collapse(2)

int num_interaion = 100;
while (num_interaion > 0){
	num_interaion--;
	printf("num_interaion: %d\n",num_interaion);
// int neighbors = 0;
//#pragma omp parallel for shared(grid, tempGrid)
// for run 2 loops: https://stackoverflow.com/questions/13357065/how-does-openmp-handle-nested-loops?rq=1
//#pragma omp parallel default(none) shared(grid, tempGrid) private ( i, j, neighbors) reduction (+:num_interaion)
//{
// #pragma omp parallel for collapse(2)
//#pragma omp parallel for shared(i, j) reduction(+: neighbors)
// OpenMP 4.5 because of #define _OPENMP 201511
//omp_lock_t writelock;
//omp_init_lock(&writelock);

int i; 
#pragma omp parallel for default(shared)
	for ( i = 0; i < width; ++i)
	{
		#pragma omp parallel for shared(i, width)
			for ( int j = 0; j < height; ++j)
			{
				// Edges
				if (i == 0 || i == (width - 1) || j == 0 || j == (height - 1))
				{	
					//omp_set_lock(&writelock);
					//#pragma omp atomic write
					tempGrid[i][j] = grid[i][j];
					//omp_unset_lock(&writelock);
				}
				else
				{		
					//omp_set_lock(&writelock);
					//#pragma opm atomic read
					bool element =  grid[i][j];
					//omp_unset_lock(&writelock);

					//omp_set_lock(&writelock);
					//	#pragma opm atomic read
						int neighbors = countNeighbors(i, j);
					//omp_unset_lock(&writelock);

						if (element == true)
						{
							if (neighbors == 2 || neighbors == 3)
							{
								// element survives
								//omp_set_lock(&writelock);
								//#pragma omp atomic write
								tempGrid[i][j] = 1;
								//omp_unset_lock(&writelock);
							}
							else
							{
								// element dies
								//omp_set_lock(&writelock);
								//#pragma omp atomic write
								tempGrid[i][j] = 0;
								//omp_unset_lock(&writelock);
							}
						}
						else
						{
							if (neighbors == 3)
							{
								// element is born
								//omp_set_lock(&writelock);
								//#pragma omp atomic write
								tempGrid[i][j] = 1;
								//omp_unset_lock(&writelock);
							}
							else
							{
								// element empty
								//#pragma omp atomic write
								tempGrid[i][j] = 0;
								//omp_unset_lock(&writelock);
							}
						}

					
				}
			}
	}

	bool **t = grid;
	grid = tempGrid;
	tempGrid = t;
	//omp_destroy_lock(&writelock);
}// while for

	//neighbors = 0; // come back to 0
//}
	
	
	// // free temporary
	// for (size_t i = 0; i < width; ++i)
	// {
	// 	delete[] temporary[i];
	// }
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