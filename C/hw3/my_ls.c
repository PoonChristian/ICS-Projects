#include "my_ls.h"

#define MAX_WIDTH 6

char *getUserName(uid_t uid)
{
	struct passwd *pw = getpwuid(uid);
	return pw->pw_name ? pw->pw_name : "";
}

char *getGroupName(gid_t gid)
{
	struct group *gr = getgrgid(gid);
	return gr->gr_name ? gr->gr_name : "";
}

char *printDirectoryInfo(mode_t mode)
{
	printf(S_ISDIR(mode) ? "d" : "-");
}

char *convertOwnerInfo(mode_t mode)
{
	printf(mode & S_IRUSR ? "r" : "-");
	printf(mode & S_IWUSR ? "w" : "-");
	printf(mode & S_IXUSR ? "x" : "-");
}

char *convertGroupInfo(mode_t mode)
{
	printf(mode & S_IRGRP ? "r" : "-");
	printf(mode & S_IWGRP ? "w" : "-");
	printf(mode & S_IXGRP ? "x" : "-");
}

char *convertOtherInfo(mode_t mode)
{
	printf(mode & S_IROTH ? "r" : "-");
	printf(mode & S_IWOTH ? "w" : "-");
	printf(mode & S_IXOTH ? "x" : "-");
}

char *printFilePermissions(mode_t mode)
{
	printDirectoryInfo(mode);
	convertOwnerInfo(mode);
	convertGroupInfo(mode);
	convertOtherInfo(mode);
}

static char *convertStatTime(time_t time)
{
	struct tm localTime;
	localtime_r(&time, &localTime);
	static char timebuffer[100];
	strftime(timebuffer, sizeof(timebuffer), "%b %d %I:%M", &localTime);
	return timebuffer;
}

int checkArgument(char *dirName, DIR *dp, FILE *fp)
{ 
    if (!(dp = opendir(dirName)) && (!(fp = fopen(dirName, "r"))))
    {
        fprintf(stderr, "Error(%d) opening %s\n", errno, dirName);
        return errno;
    }
}

void checkStatStatus(char path[1024], struct stat long_stat)
{
    if (stat(path, &long_stat) == -1)
        perror("ERROR"), exit(1);
}

char *createNewPath(char new_path[1024], char* dirName, struct dirent *direntp)
{
    strcpy(new_path, dirName);
    strcat(new_path, "/");
    strcat(new_path, direntp->d_name);
    return new_path;
}

void printLongDataWithinDirectory(char buffer[1024], char tabs[1024],
                                    struct dirent *dp, struct stat long_stat)
{
    sprintf(buffer, " %d %s %s %*d %s %s\n", long_stat.st_nlink,
                                    getUserName(long_stat.st_uid),
                                    getGroupName(long_stat.st_gid),
                                    MAX_WIDTH, long_stat.st_size,
                                    convertStatTime(long_stat.st_mtime),
                                    dp->d_name);
    printf("%s", tabs);
    printFilePermissions(long_stat.st_mode);
    printf("%s", buffer);
}

void printLongDataOfSingleFile(char buffer[1024], char *dirName, struct stat long_stat)
{
    sprintf(buffer, " %d %s %s %*d %s %s\n", long_stat.st_nlink,
                                    getUserName(long_stat.st_uid),
                                    getGroupName(long_stat.st_gid),
                                    MAX_WIDTH, long_stat.st_size,
                                    convertStatTime(long_stat.st_mtime),
                                    dirName);
    printFilePermissions(long_stat.st_mode);
    printf("%s", buffer);
}

void traverseDirectory(DIR *dirp, char *dirName, char tabs[1024]) /* EXCEEDING 5 LINES */
{
	struct dirent *direntp;
	struct stat mystat;
    char buffer[1024];
	char path[1024];
	while ((direntp = readdir(dirp)))
	{
		if (direntp->d_name[0] != '.')
		{
			sprintf(path, "%s/%s", dirName, direntp->d_name);
			stat(path, &mystat);
			DIR *new_dirp;
			checkStatStatus(path, mystat);	
			
            if (new_dirp = opendir(path))
			{
				stat(direntp->d_name, &mystat);
                printLongDataWithinDirectory(buffer, tabs, direntp, mystat);
				char new_path[1024];
                createNewPath(new_path, dirName, direntp);
				strcat(tabs, "    ");
				traverseDirectory(new_dirp, new_path, tabs);
				tabs[strlen(tabs)-4] = '\0';;
			}
			else
                printLongDataWithinDirectory(buffer, tabs, direntp, mystat);	
		}
	}	
		
}

void readDirectory(DIR *dirp, struct dirent *direntp, char *dirName, char tabs[1024])
{
    direntp = readdir(dirp);
    traverseDirectory(dirp, dirName, tabs);
    closedir(dirp);
}

int do_ls(char *dirName)
{
	DIR *dirp;
    FILE *filp;
    struct dirent *direntp;
	struct stat mystat;
    char buffer[1024];
	char tabs[1024] = "";
	dirp = opendir(dirName);
    checkArgument(dirName, dirp, filp);
	stat(dirName, &mystat);

	if ((dirp = opendir(dirName)))
		readDirectory(dirp, direntp, dirName, tabs);
	else
        printLongDataOfSingleFile(buffer, dirName, mystat);
}

