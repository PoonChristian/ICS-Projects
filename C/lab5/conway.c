#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void copy_grid(int original_grid[24][82], int grid_copy[24][82])
{
    for (int i = 0; i < 24; ++i)
    {
        for (int j = 0; j < 82; ++j)
            grid_copy[i][j] = original_grid[i][j];
    }
}

void life(int grid[24][82])
{
    int temp_grid[24][82];
    copy_grid(grid, temp_grid);
    for (int i = 1; i < 23; i++)
    {
        for (int j = 1; j < 81; j++)
        {
            int neighbors = 0;
            neighbors = grid[i-1][j-1] +
                        grid[i-1][j]   +
                        grid[i-1][j+1] +
                        grid[i][j+1]   +
                        grid[i+1][j+1] +
                        grid[i+1][j]   +
                        grid[i+1][j-1] +
                        grid[i][j-1];
            if (neighbors < 2 || neighbors > 3)
                temp_grid[i][j] = 0;
            if (neighbors == 2)
                temp_grid[i][j] = grid[i][j];
            if (neighbors == 3)
                temp_grid[i][j] = 1;
         }       
    }
    copy_grid(temp_grid, grid);
}

void print_grid(int grid[24][82])
{
    for (int i = 0; i < 24; ++i)
    {
        for (int j = 0; j < 82; ++j)
        {
            if (grid[i][j] == 1)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
}

void generate_initial_grid(int grid[24][82])
{
    srand(time(NULL));
    for (int i = 0; i < 24; ++i)
    {
        for (int j = 0; j < 82; ++j)
        {
            if (i == 0 || i == 23)
                grid[i][j] = 0;
            else if (j == 0 || j == 81)
                grid[i][j] = 0;
            else   
                grid[i][j] = rand() % 2;
        }
    }
}

int main()
{
    int grid[24][82];
    generate_initial_grid(grid);
    int i = 0;
    while (i <= 25)
    {
        printf("Generation %d\n\n", i);
        print_grid(grid);
        printf("\n\n");
        life(grid);
        i++;
        sleep(1);
    }
    return 0;
}
