#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

void checkSize(off_t size, char * inputFilename)
{
    if (size >= 10000)
        printf("%lldK ", size/1000);
    else if (size < 10000 && size > 1000)
        printf("%.1fK ", (float)size/1000);
    else
        printf("%lld ",size);
}

void checkDirectory(DIR * dp, char * inputFilename)
{
    off_t total = 0;
    struct dirent * file;
    struct stat buf;
    char path[1024];
    while ((file = readdir(dp))) 
    {
        if ((strcmp(file->d_name, ".") == 0) || (strcmp(file->d_name,"..") == 0))
            continue;
        sprintf(path,"%s/%s",inputFilename,file->d_name);

        stat(path, &buf);
        DIR * new_dp;
        if ((new_dp = opendir(path)))
        {
            // Recursion
            char new_path[1024];
            strcpy(new_path, inputFilename);
            strcat(new_path, "/");
            strcat(new_path, file->d_name);

            checkDirectory(new_dp,new_path);
            total += buf.st_size;
        }
        else
        {
            checkSize(buf.st_size, file->d_name);
            printf("%8s\n", path);
            total += buf.st_size;
        }

    }
    stat(inputFilename, &buf);
    total += buf.st_size;
    checkSize(total, inputFilename);
    printf("%8s\n", inputFilename);
}

int main(int argc, char * argv[])
{
    
    struct stat buf;
    char * inputFilename = argv[1];
    FILE * fp;
    DIR * dp;
    struct dirent * file;

    if ((!(dp = opendir(inputFilename))) && (!(fp = fopen(inputFilename, "r"))))
    {
        fprintf(stderr, "Error(%d) opening %s\n", errno, inputFilename);
        return errno;
    }
    else if ((dp = opendir(inputFilename)))
    {
        file = readdir(dp);
        checkDirectory(dp,inputFilename);
    }
    else
    {
        stat(inputFilename, &buf);
        checkSize(buf.st_size, inputFilename);
    }

    return 0;
}
