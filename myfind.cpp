#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <filesystem>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include<sys/types.h>
#include<sys/wait.h>

#ifndef PATH_MAX
#define PATH_MAX 255
#endif

using namespace std;


int listFiles(char* workingDirectory, DIR* dirpath, dirent* direntry){

    getcwd(workingDirectory, PATH_MAX);
    printf("Current working directory: %s\n", workingDirectory);

    if((dirpath = opendir(workingDirectory)) == NULL)
    {
        perror("Failed to open directory");
        return -1;
    }

    cout << "Files in current directory: " << endl;
    while((direntry = readdir(dirpath)) != NULL)
    {
        cout << direntry->d_name << " ";
        cout << to_string(direntry->d_type) << endl; //d_type 4 == folder, d_type 8 == file
    }
    cout << endl;

    chdir(".."); //changes the current directory of the process to .. (which is the parent directory)
    return 1;
}

bool file_exist(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

void myfork(const char* path, char* fileToFind){
    
    //seach for file in path
    //output if file exists and pid

    pid_t childpid;

    childpid = fork();

    if (childpid == -1)
    {
        perror("Failed to fork");
    }
    else if(childpid == 0){
        chdir(path);
        if(file_exist(fileToFind))
        {
            cout << (long)getpid() << ": " << fileToFind << ": " << path << endl;
        }

        wait(NULL);
        kill((long)getpid(), SIGKILL);
    }

}

void getOptions(int argc, char **argv)
{
    const char* searchPath;
    int opt;
    int counter = 0;
    while((opt = getopt(argc, argv, "Ri")) != -1)
    {
        switch(opt)
        {
            case 'R': 
                //optR = true; 
                cout << "opt R specified" << endl;
                counter++;
                continue;
            case 'i': 
                //opti = true; 
                cout << "opt i specified" << endl; 
                counter++;
                continue;
            case '?': 
            default: 
                break;
            case -1:
                break;
        }
    }
    //cout << "number of options: " << counter << endl;

    for(; optind < argc; optind++){     
        string argString = string(argv[optind]);
        if(argString.find('/')<argString.length())
        {
            searchPath = argv[optind];
            cout << searchPath << " is searchpath" << endl;
        }
        else
        {
            myfork(searchPath, argv[optind]); //optI, optR
        }
    }
}

int main(int argc, char **argv)
{
    //bool optR = false;
    //bool opti = false;

    //get all arguments
    //start new process for every file 
    //check if file exists in search path
    //output if seach was successfull or not



    
    getOptions(argc, argv);

    // for(int i = 0; i < argc; i++)
    // {
    //     cout << "argv[" << i << "]: " << argv[i] << endl;
        
    // // }

    // char workingDirectory[PATH_MAX];
    // if (getcwd(workingDirectory, PATH_MAX) == NULL)
    // {
    //     perror("Failed to get current working directory");
    //     return 1;
    // }

    // struct dirent *direntry; //struct dirent stores name and type of the directory entry (among other things)
    // DIR *dirpath;

    // if ((dirpath = opendir(workingDirectory)) == NULL)
    // {
    //     perror("Failed to open directory");
    //     return -1;
    // }

    // direntry = readdir(dirpath);

    // listFiles(workingDirectory, dirpath, direntry);
    // listFiles(workingDirectory, dirpath, direntry);
    // listFiles(workingDirectory, dirpath, direntry);
    // listFiles(workingDirectory, dirpath, direntry);

    // if((dirpath = opendir("..")) == NULL)
    // {
    //     perror("Failed to open directory");
    //     return -1;
    // }

    // direntry = readdir(dirpath);
    
    // cout << direntry->d_name << " ";
    // cout << to_string(direntry->d_type) << endl;
    
    
    return 0;
}