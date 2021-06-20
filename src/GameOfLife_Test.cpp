//!  A test class. 
/*!
    A test class for game of life 
    how to install : https://www.srcmake.com/home/google-cpp-test-framework
    document at https://google.github.io/googletest/
*/

#include "GameOfLife.h"
#include "GameOfLife.cpp"
#include <gtest/gtest.h>

//! A function variable
/*!
    CountNeighBoursTest
    at the begin will init grid and set 9 Element 
    and check value at a position and assert 
	return count neigbours
*/
TEST(CountNeighBoursTest, CountNear){
    GameOfLife *game;
    game = new GameOfLife(512,512);
    game->randomInit();
    
    game->setElement(0,0, 0);
    game->setElement(0,1, 0);
    game->setElement(0,2, 1);

    game->setElement(1,0, 0);
    game->setElement(1,1, 0);
    game->setElement(1,2, 1);

    game->setElement(2,0, 0);
    game->setElement(2,1, 0);
    game->setElement(2,2, 1);

    double countElement = game->countNeighbors(1,1);
    // printf("countElement: %i", countElement);
    ASSERT_EQ(3.0, countElement);
}

//! A function variable
/*!
    CHeck the function getElement
*/
TEST(GetStatusElement, NoNeighbours)
{
    GameOfLife *game;
    game = new GameOfLife(512,512);
    game->randomInit();
    game->setElement(1,1, true);
    bool element = game->getElement(1,1);
    ASSERT_EQ(true, element);
    // check lengt of array grid
}

//! A function variable
/*!
    Run all test at the main function here
*/
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
