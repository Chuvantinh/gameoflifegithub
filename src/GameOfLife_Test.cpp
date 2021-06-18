// how to install : https://www.srcmake.com/home/google-cpp-test-framework
// document : https://google.github.io/googletest/
#include "GameOfLife.h"
#include "GameOfLife.cpp"
#include <gtest/gtest.h>

TEST(SquareRootTest, PositiveNos)
{
    ASSERT_EQ(6, squareRoot(36.0));
    ASSERT_EQ(18, squareRoot(324.0));
    ASSERT_EQ(25.4, squareRoot(645.16));
    ASSERT_EQ(0, squareRoot(0.0));
}

TEST(SquareRootTest, NegativeNos)
{
    ASSERT_EQ(-1.0, squareRoot(-15.0));
    ASSERT_EQ(-1.0, squareRoot(-0.2));
}

TEST(CountNeighBoursTest, CountNear){
    GameOfLife *game;
    game = new GameOfLife(512,512);
    game->randomInit();
    
    game->setElement(0,0, false);
    game->setElement(0,1, false);
    game->setElement(0,2, true);

    game->setElement(1,0, false);
    game->setElement(1,1, false);
    game->setElement(1,2, true);

    game->setElement(2,0, false);
    game->setElement(2,1, false);
    game->setElement(2,2, true);

    double countElement = game->countNeighbors(1,1);
    // printf("countElement: %i", countElement);
    ASSERT_EQ(3.0, countElement);
}

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

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
