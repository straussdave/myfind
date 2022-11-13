#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <filesystem>
#include <iostream>
#ifndef PATH_MAX
#define PATH_MAX 255
#endif

using namespace std;


int listFiles(char* currentWorkingDirectory, DIR* dirpath, dirent* direntry){
    getcwd(currentWorkingDirectory, PATH_MAX);

    printf("Current working directory: %s\n\n", currentWorkingDirectory);

    if((dirpath = opendir(currentWorkingDirectory)) == NULL)
    {
        perror("Failed to open directory");
        return -1;
    }

    cout << "Files in current directory: " << endl;

    while((direntry = readdir(dirpath)) != NULL)
    {
        printf("%s ", direntry->d_name);
        printf("%i\n", direntry->d_type); //d_type 4 == folder, d_type 8 == file
    }
    chdir("..");
    return 1;
}

int main(int argc, char **argv)
{
    char currentWorkingDirectory[PATH_MAX];
    int counter = 0;
    if (getcwd(currentWorkingDirectory, PATH_MAX) == NULL)
    {
        perror("Failed to get current working directory");
        return 1;
    }

    struct dirent *direntry;
    DIR *dirpath;

    if ((dirpath = opendir(currentWorkingDirectory)) == NULL)
    {
        perror("Failed to open directory");
        return -1;
    }

    direntry = readdir(dirpath);

    listFiles(currentWorkingDirectory, dirpath, direntry);
    listFiles(currentWorkingDirectory, dirpath, direntry);
    listFiles(currentWorkingDirectory, dirpath, direntry);
    return 0;
}