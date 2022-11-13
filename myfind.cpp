#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#ifndef PATH_MAX
#define PATH_MAX 255
#endif

int main(int argc, char **argv)
{
    char currentWorkingDirectory[PATH_MAX];

    if (getcwd(currentWorkingDirectory, PATH_MAX) == NULL)
    {
        perror("Failed to get current working directory");
        return 1;
    }
    printf("Current working directory: %s\n", currentWorkingDirectory);

    struct dirent *direntry;
    DIR *dirpath;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s directory_name\n", argv[0]);
        return 1;
    }

    if ((dirpath = opendir(argv[1])) == NULL)
    {
        perror("Failed to open directory");
        return 1;
    }

    while ((direntry = readdir(dirpath)) != NULL)
    {
        printf("%s ", direntry->d_name);
        printf("%i\n", direntry->d_type); //d_type 4 == folder, d_type 8 == file
    }
        
    closedir(dirpath);

    printf("\n");

    return 0;
}