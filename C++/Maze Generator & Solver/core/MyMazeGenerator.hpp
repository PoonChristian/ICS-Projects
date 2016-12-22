#ifndef MYMAZEGENERATOR_HPP
#define MYMAZEGENERATOR_HPP

#include "MazeGenerator.hpp"

class MyMazeGenerator: public MazeGenerator
{
public:
    bool adjacentCellsAreNotVisited(Maze& maze, int x, int y);

    bool checkAllCells(Maze& maze);
    
    void createTunnel(Maze& maze, int x, int y);
    
    virtual void generateMaze(Maze& maze);
private:
    std::vector<std::vector<bool>> visitedCells;
};

#endif // MYMAZEGENERATOR_HPP
