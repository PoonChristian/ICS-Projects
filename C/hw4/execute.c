#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void split_args(char *arg_strings[1024], char arg_input[1024])
{
    const char delim[10] = " \t<>";
    int pos = 0;
    char *first_arg;
    first_arg = strtok(arg_input, delim);
    while (first_arg != NULL)
    {
        arg_strings[pos++] = first_arg;
        first_arg = strtok(NULL, delim);
    }
}

int main(int argc, char* argv[], char* envp[])
{
    char *arg_strings[1024];
    char arg_input[1024];
    fgets(arg_input, 1024, stdin);
    arg_input[strcspn(arg_input, "\n")] = 0;
    split_args(arg_strings, arg_input);
    int ret = execvpe(arg_strings[0], arg_strings, envp);
    if (ret == -1)
        perror(arg_strings[0]), exit(-1); 
    return 0;
}
