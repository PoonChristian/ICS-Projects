#ifndef MY_LS_H
#define MY_LS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <errno.h>


int do_ls(char *dirName);

#endif // MY_LS_H
