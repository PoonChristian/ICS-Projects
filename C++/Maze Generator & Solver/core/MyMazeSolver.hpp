#ifndef MYMAZESOLVER_HPP
#define MYMAZESOLVER_HPP

#include "MazeSolver.hpp"

class MyMazeSolver: public MazeSolver
{
public:
    void searchPath(const Maze& maze, MazeSolution& mazeSolution);

    virtual void solveMaze(const Maze& maze, MazeSolution& mazeSolution);
private:
    std::vector<std::vector<bool>> visitedCells;
};

#endif // MYMAZESOLVER_HPP
