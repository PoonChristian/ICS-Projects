#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


void print_k_characters(int k, char c)
{
    for (int i = 0; i < k; ++i)
    {
        putchar(c);
        fflush(stdout);
    }
}

void fork_processes(int k)
{
    int num_process = 4;
    char alpha_array[5] = {'A', 'B', 'C', 'D'};
    for (int i = 0; i < num_process; ++i)
    {
        int childPID;
        switch (childPID = fork())
        {
            case -1:
                perror("Fork failed"), exit(1);
            case 0:
                print_k_characters(k, alpha_array[i]), exit(0);
        }
    } 
    int status;
    for (int j = 0; j < num_process; ++j)
        wait(&status);
    
}

int main(int argc, char *argv[])
{
    if (argv[1] == NULL)
        fork_processes(10000);
    else
    {
        int k = atoi(argv[1]);
        fork_processes(k);
    }
    return 0;
}
