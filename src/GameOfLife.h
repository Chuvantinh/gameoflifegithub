//! A class library for Game of life
/*!
  It contains the grid variable for storing the matrix of the element
  However, It has some the 
*/
#pragma once

#include <cstdlib>
#include <ctime>

class GameOfLife {
private:
    //! A public variable.
    /*!
      Grid: to store all element on openGL
    */
	bool** grid;

  //! A public variable.
    /*!
      Temproray variable: to store all element on openGL
      and then copy all into gird variable
    */
  bool** tempGrid;
  
  //! A public variable.
    /*!
      with of game
    */
	int width;

  //! A public variable.
    /*!
      height of game
    */
	int height;
public:
    //! A constructor
    /*!
        Game of life will init here with the width and height 
    */
    GameOfLife(const int w, const int h);

    //! A destructor.
    /*!
      The grid and tempGrid will be deleted after the life time ends.
    */
	~GameOfLife();

    /*!
      return grid 
    */
    bool **getGrid(){
      return grid;
    }
    //! A function variable
    /*!
      The element of grid will be initialized 
    */
	void randomInit(const double probability = 0.1);

    //! A function variable
    /*!
      The iterate function for redisplay grid, call back function will be called 
    */
	void iterate();

    //! A function variable
    /*!
      Get element of grid at the codinator x and y
      x with 
      y height
    */
    bool getElement(const int x, const int y);

    //! A function variable
    /*!
      Set element of grid at the codinator x and y
      x with 
      y height
      value is 0 die 1 live
    */
    bool setElement(int x, int y, int value);

    //! A function variable
    /*!
      Count the number of Neighbors without itself
    */
    int countNeighbors( int x,  int y);
    
    //! A function variable
    /*!
      2 for loop will print postion and value of element
    */
    void printGrid();
};
