#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void split_args(char arg_input[1024], char *arg_strings[1024])
{
    const char delim[10] = " \t";
    int pos = 0;
    char *first_arg;
    first_arg = strtok(arg_input, delim);
    while (first_arg != NULL)
    {
        arg_strings[pos++] = first_arg;
        first_arg = strtok(NULL, delim);
    }
}

void check_system_open(int file_descriptor)
{
    if (file_descriptor == -1)
        perror("Failed to open"), exit(1);
}

void check_redirection(char* arg_tokens[1024], char input[128], char output[128], int* in, int* out)
{
	for (int i = 0; arg_tokens[i]; ++i)
	{
		if (strcmp(arg_tokens[i], "<") == 0)
		{
			arg_tokens[i] = NULL;
			strcpy(input, arg_tokens[i+1]);
			*in = 1;
		}
		else if (strcmp(arg_tokens[i], ">") == 0)
		{
			arg_tokens[i] = NULL;
			strcpy(output, arg_tokens[i+1]);
			*out = 1;
		}
	}	
}

void redirect_input(char input[128], int* ifd, int* in)
{
	if (*in)
	{
		*ifd = open(input, O_RDONLY);
		check_system_open(*ifd);
		dup2(*ifd, 0);
		close(*ifd);
		*in = 0;
	}
}

void redirect_output(char output[128], int* ofd, int* out)
{	
	if (*out)
	{
		*ofd = open(output, O_WRONLY | O_CREAT, 0666);
		check_system_open(*ofd);
		dup2(*ofd, 1);
		close(*ofd);
		*out = 0;
	}
}

void prompt_user(char command[1024])
{
	printf("%% ");
	fgets(command, 1024, stdin);
	command[strcspn(command, "\n")] = '\0';
}

int main(int argc, char* argv[])
{
	while (1)
	{
		int pid = fork();
		switch (pid)
		{
			case -1:
				perror("Fork failed"), exit(1);
			case 0:
			{
				char command[1024];
				char* arg_tokens[1024];
				char input[128], output[128];
				int in = 0, out = 0;
				int ifd, ofd;
				
				prompt_user(command);
				split_args(command, arg_tokens);
				check_redirection(arg_tokens, input, output, &in, &out);
				redirect_input(input, &ifd, &in);
				redirect_output(output, &ofd, &out);
				
				if (execvp(arg_tokens[0], arg_tokens) == -1);
				{	
					perror("Execvp"), exit(1);
				}
				printf("It got here\n");
				exit(0);
			}
			default:
			{
				int status;
				wait(&status);
			}
		}
	}
	return 0;
}
