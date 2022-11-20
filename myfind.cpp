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
#include <sys/types.h>
#include <sys/wait.h>
#include <bits/stdc++.h>
#include <filesystem>

#ifndef PATH_MAX
#define PATH_MAX 255
#endif

using namespace std;

bool file_exist(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

void myfork(const char* path, char* fileToFind, bool optI, bool optR){
    
    //seach for file in path
    //output if file exists and pid
    pid_t childpid;
    DIR *dir; struct dirent *diread;
    vector<char *> files;
    
    childpid = fork();

    char tmp[256];
    getcwd(tmp, 256); //this gets the full current directory of the process and stores it in tmp

    if (childpid == -1)
    {
        perror("Failed to fork");
    }
    else if(childpid == 0)
    {
        chdir(path);
        if(file_exist(fileToFind) && !optI && !optR)
        {
            cout << (long)getpid() << ": " << fileToFind << ": " << tmp << endl;
        }
        else if(!optI && optR)
        {
            
            if(file_exist(fileToFind))
            {
                cout << (long)getpid() << ": " << fileToFind << ": " << tmp << endl;
            }
            else
            {
            myfork("..", fileToFind, optI, optR);
            }
        }
        else if (optI && !optR)
        {
            if ((dir = opendir(path)) != nullptr) 
            {
                while ((diread = readdir(dir)) != nullptr) 
                {
                    files.push_back(diread->d_name);
                }       
                closedir (dir);
            }
            else
            {
                wait(NULL);
                kill((long)getpid(), SIGKILL);
                return;
            }

            //file to find lower case
            string ftf = fileToFind;
            transform(ftf.begin(), ftf.end(), ftf.begin(), ::tolower);

            for (string file : files) 
            {
                string realFile = file;
                transform(file.begin(), file.end(), file.begin(), ::tolower);
                int res = ftf.compare(file);
                if(res == 0)
                {
                    cout << (long)getpid() << ": " << realFile << ": " << tmp << endl;
                }
            }
        }
        else if(optI && optR)
        {
            if ((dir = opendir(path)) != nullptr) 
            {
                while ((diread = readdir(dir)) != nullptr) 
                {
                    files.push_back(diread->d_name);
                }
                closedir(dir);
            }
            else
            {
                wait(NULL);
                kill((long)getpid(), SIGKILL);
                return;
            }

            //file to find lower case
            string ftf = fileToFind;
            transform(ftf.begin(), ftf.end(), ftf.begin(), ::tolower);

            int res = -1;
            for (string file : files) 
            {
                string realFile = file;
                transform(file.begin(), file.end(), file.begin(), ::tolower);
                res = ftf.compare(file);
                if(res == 0)
                {
                    cout << (long)getpid() << ": " << realFile << ": " << tmp << endl;
                }
            }
            if(res != 0)
            {
                myfork("..", fileToFind, optI, optR);
            }
        }

        wait(NULL);
        kill((long)getpid(), SIGKILL);
    }
}


void getoptions(int argc, char **argv)
{
    const char* searchPath;
    int opt;
    bool optR, optI = false;
    while((opt = getopt(argc, argv, "Ri")) != -1)
    {
        switch(opt)
        {
            case 'R': 
                optR = true; 
                continue;
            case 'i': 
                optI = true; 
                continue;
            case '?': 
            default: 
                break;
            case -1:
                break;
        }
    }

    for(; optind < argc; optind++)
    {     
        string argString = string(argv[optind]);
        if(argString.find('/')<argString.length())
        {
            searchPath = argv[optind];
        }
        else
        {
            myfork(searchPath, argv[optind], optI, optR);
        }
    }
}

int main(int argc, char **argv)
{
    //get all arguments
    //start new process for every file 
    //check if file exists in search path
    //output if seach was successfull or not
    
    getoptions(argc, argv);
    
    return 0;
}