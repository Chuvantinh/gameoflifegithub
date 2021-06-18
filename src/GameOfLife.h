#pragma once

#include <cstdlib>
#include <ctime>

class GameOfLife {
private:
	bool** grid;
    bool** tempGrid;
    
    int *xdomain;
    int *ydomain;
    
	int width;
	int height;
public:
    GameOfLife(const int w, const int h);
	~GameOfLife();
	void randomInit(const double probability = 0.1);
	void iterate();
    bool getElement(const int x, const int y);
    bool setElement(int x, int y, bool value);
    int countNeighbors( int x,  int y);
    
    void printGrid();
    double squareRoot(const double a);
};
