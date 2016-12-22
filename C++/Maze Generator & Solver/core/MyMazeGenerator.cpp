#include <iostream>
#include <random>
#include <ics46/factory/DynamicFactory.hpp>

#include "MyMazeGenerator.hpp"
#include "Maze.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, MyMazeGenerator, "Poon's Maze Generator (Required)");

namespace
{
    std::random_device device;
    std::default_random_engine engine{device()};
    std::uniform_int_distribution<int> distribution{1, 4};
}

bool MyMazeGenerator::adjacentCellsAreNotVisited(Maze& maze, int x, int y)
{
    if (x == 0) // Left edge
    {
        if (y == 0) // Top left corner
        {
            if (visitedCells[y + 1][x] == false || visitedCells[y][x + 1] == false)
                return true;
            else
                return false;
        }
        else if (y == maze.getHeight() - 1) // Bottom left corner
        {
            if (visitedCells[y - 1][x] == false || visitedCells[y][x + 1] == false)
                return true;
            else
                return false;
        }
        else // Left edge in general
        {        
            if (visitedCells[y - 1][x] == false ||
                visitedCells[y + 1][x] == false ||
                visitedCells[y][x + 1] == false)
                return true;
            else
                return false;
        }
    }
    else if (x == maze.getWidth() - 1) // Right edge
    {
        if (y == 0) // Top right corner
        {
            if (visitedCells[y + 1][x] == false || visitedCells[y][x - 1] == false)
                return true;
            else
                return false;
        }
        else if (y == maze.getHeight() - 1) // Bottom right corner
        {
            if (visitedCells[y - 1][x] == false || visitedCells[y][x - 1] == false)
                return true;
            else
                return false;
        }
        else // Right edge in general
        {
            if (visitedCells[y - 1][x] == false ||
                visitedCells[y + 1][x] == false ||
                visitedCells[y][x - 1] == false)
                return true;
            else
                return false;
        }
    }
    else if (y == 0) // Top edge
    {
        if (visitedCells[y + 1][x] == false ||
            visitedCells[y][x - 1] == false ||
            visitedCells[y][x + 1] == false)
            return true;
        else
            return false;
    }
    else if (y == maze.getHeight() - 1) // Bottom edge
    {
        if (visitedCells[y - 1][x] == false ||
            visitedCells[y][x - 1] == false ||
            visitedCells[y][x + 1] == false)
            return true;
        else
            return false;
    }
    else // Every other cell inside
    {   
        if (visitedCells[y - 1][x] == false ||
            visitedCells[y + 1][x] == false ||
            visitedCells[y][x - 1] == false ||
            visitedCells[y][x + 1] == false)
            return true;
        else
            return false;
    }
}

bool MyMazeGenerator::checkAllCells(Maze& maze)
{   
    for (int i = 0; i < maze.getHeight(); ++i)
    {
        for (int j = 0; j < maze.getWidth(); ++j)
        {
            if (visitedCells[i][j] == false)
                return true;
        }
    }
    return false;
}

void MyMazeGenerator::createTunnel(Maze& maze, int x, int y)
{
    bool isVisitingCells = true;
    while (isVisitingCells)
    {
        int direction = distribution(engine);
        if (!adjacentCellsAreNotVisited(maze, x, y)) // Backtrack
        {
            return;
        }
        switch (direction)
        {
            case 1:
            {
                if (y - 1 >= 0 && maze.wallExists(x, y, Direction::up))
                {
                    if (visitedCells[y-1][x] == false)
                    {
                        maze.removeWall(x, y, Direction::up);
                        visitedCells[y - 1][x] = true;
                        createTunnel(maze, x, y - 1);
                    }
                }
                break;
            }
            case 2:
            {
                if (y + 1 <= maze.getHeight() - 1 &&
                    maze.wallExists(x, y, Direction::down))
                {
                    if (visitedCells[y + 1][x] == false)
                    {
                        maze.removeWall(x, y, Direction::down);
                        visitedCells[y + 1][x] = true;
                        createTunnel(maze, x, y + 1);
                    }
                }
                break;
            }
            case 3:
            {
                if (x - 1 >= 0 &&
                    maze.wallExists(x, y, Direction::left))
                {
                    if (visitedCells[y][x - 1] == false)
                    {
                        maze.removeWall(x, y, Direction::left); 
                        visitedCells[y][x - 1] = true;
                        createTunnel(maze, x - 1, y);
                    }
                }
                break;
            }
            case 4:
            {
                if (x + 1 <= maze.getWidth() - 1 &&
                    maze.wallExists(x, y, Direction::right))
                {
                    if (visitedCells[y][x + 1] == false)
                    {
                        maze.removeWall(x, y, Direction::right);
                        visitedCells[y][x + 1] = true;
                        createTunnel(maze, x + 1, y);
                    }
                }
                break;
            }
        }
        isVisitingCells = checkAllCells(maze);
    }
}

void MyMazeGenerator::generateMaze(Maze& maze)
{
    maze.removeAllWalls();
    maze.addAllWalls();
    int x = 0;
    int y = 0;
    visitedCells.assign(maze.getHeight(), std::vector<bool>(maze.getWidth(), false));
    visitedCells[x][y] = true;
    createTunnel(maze, x, y);
}
