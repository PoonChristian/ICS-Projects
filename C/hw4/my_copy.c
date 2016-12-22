#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "Timer.h"

double time_array[3] = {0, 0, 0};

FILE* library_open(char* filename, char* mode)
{ 
    FILE* fp = fopen(filename, mode);
    if (fp == NULL)
        fprintf(stderr, "Can't open %s\n", filename), exit(1);
    return fp;
}

void check_system_open(int file_descriptor)
{
    if (file_descriptor == -1)
        perror("Failed to open"), exit(1);
}

void systemCheckWriteStatus(ssize_t written, ssize_t read)
{
    if (written != read)
        perror("Failed to write"), exit(1);
}

double* fcopy_in_to_out(char* input, char *output)
{
    FILE* ifp = library_open(input, "r");
    FILE* ofp = library_open(output, "w"); 
    int c;
    static double times[3] = {0, 0, 0};
    Timer_start();
    while ((c = fgetc(ifp)) != EOF)
        fputc(c, ofp);
    Timer_elapsedTime(&times[0], &times[1], &times[2]);
    fclose(ifp), fclose(ofp);
    return times;
}

double* sys_copy_one(char* input, char* output)
{
    int ifd = open(input, O_RDONLY);
    check_system_open(ifd);
    int ofd = open(output, O_WRONLY | O_CREAT, 0666);
    check_system_open(ofd);
    ssize_t c_in, c_out;
    char character[2];
    static double times[3] = {0, 0, 0};
    Timer_start();
    while ((c_in = read(ifd, &character, 1)) > 0)
    {
        c_out = write(ofd, &character, c_in);
        systemCheckWriteStatus(c_out, c_in);
    }
    Timer_elapsedTime(&times[0], &times[1], &times[2]);
    close(ifd), close(ofd);
    return times;
}

double* sys_copy_buffer(char* input, char* output)
{
    int ifd = open(input, O_RDONLY);
    check_system_open(ifd);
    int ofd = open(output, O_WRONLY | O_CREAT, 0666);
    check_system_open(ofd); 
    ssize_t b_in, b_out;
    char buffer[BUFSIZ];
    static double times[3] = {0, 0, 0};
    Timer_start();
    while ((b_in = read(ifd, &buffer, BUFSIZ)) > 0)
    {
        b_out = write(ofd, &buffer, b_in);
        systemCheckWriteStatus(b_out, b_in);
    }
    Timer_elapsedTime(&times[0], &times[1], &times[2]);
    close(ifd), close(ofd);
    return times;
}

void perform_copy_function(int method, char* input, char* output, int n)
{
    double final_wc, final_ut, final_st;
    double* times;
    for (int i = 1; i <= n; ++i)
    {
        switch (method)
        {
            case 1:
            {
                times = fcopy_in_to_out(input, output);
                final_wc += times[0];
                final_ut += times[1];
                final_st += times[2];
                if (i == n)
                    printf("wallclock %lf, user %lf, system time %lf (moderate speed)\n",
                            final_wc, final_ut, final_st);
                break;
            }
            case 2:
            {
                times = sys_copy_one(input, output);
                final_wc += times[0];
                final_ut += times[1];
                final_st += times[2];
                if (i == n)
                    printf("wallclock %lf, user %lf, system time %lf (really slow)\n",
                            final_wc, final_ut, final_st);
                break;
            }
            case 3:
            {
                times = sys_copy_buffer(input, output);
                final_wc += times[0];
                final_ut += times[1];
                final_st += times[2];
                if (i == n)
                    printf("wallclock %lf, user %lf, system time %lf (really fast)\n",
                            final_wc, final_ut, final_st);
                break;
            default:
                fprintf(stderr, "No such method\n"), exit(1);
            }
        }
    }
}

int main(int argc, char* argv[])
{
    int method = atoi(argv[1]);
    char* inputFilename = argv[2];
    char* outputFilename = argv[3];
    if (argv[4] == NULL)
        perform_copy_function(method, inputFilename, outputFilename, 1);
    else
        perform_copy_function(method, inputFilename, outputFilename, atoi(argv[4]));
    
    return 0;   
}
