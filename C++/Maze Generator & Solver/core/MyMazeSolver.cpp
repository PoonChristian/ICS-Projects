#include <iostream>
#include <ics46/factory/DynamicFactory.hpp>

#include "MyMazeSolver.hpp"
#include "Maze.hpp"
#include "MazeSolution.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, MyMazeSolver, "Poon's Maze Solver (Required)");

void MyMazeSolver::searchPath(const Maze& maze, MazeSolution& mazeSolution)
{
    int x = mazeSolution.getCurrentCell().first;
    int y = mazeSolution.getCurrentCell().second;
    while (!mazeSolution.isComplete())
    {
        if (!maze.wallExists(x, y, Direction::up) && visitedCells[y - 1][x] == false)
        {
            mazeSolution.extend(Direction::up);
            visitedCells[y - 1][x] = true;
            searchPath(maze, mazeSolution);
        }
        else if (!maze.wallExists(x, y, Direction::down) && visitedCells[y + 1][x] == false)
        {
            mazeSolution.extend(Direction::down);
            visitedCells[y + 1][x] = true;
            searchPath(maze, mazeSolution);
        }
        else if (!maze.wallExists(x, y, Direction::left) && visitedCells[y][x - 1] == false)
        {
            mazeSolution.extend(Direction::left);
            visitedCells[y][x - 1] = true;
            searchPath(maze, mazeSolution);
        }
        else if (!maze.wallExists(x, y, Direction::right) && visitedCells[y][x + 1] == false)
        {
            mazeSolution.extend(Direction::right);
            visitedCells[y][x + 1] = true;
            searchPath(maze, mazeSolution);
        }
        else
        {
            mazeSolution.backUp();
            return;
        }
    }
}

void MyMazeSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
    int x = mazeSolution.getStartingCell().first;
    int y = mazeSolution.getStartingCell().second;
    visitedCells.assign(maze.getHeight(), std::vector<bool>(maze.getWidth(), false));
    visitedCells[x][y] = true;
    searchPath(maze, mazeSolution);
}
