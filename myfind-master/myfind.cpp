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
#include<bits/stdc++.h>

#ifndef PATH_MAX
#define PATH_MAX 255
#endif

using namespace std;



bool file_exist(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

void myfork(const char* path, char* fileToFind, bool opti, bool optR){
    
    //seach for file in path
    //output if file exists and pid
    //vector to store the individual files and transform them into lower case
    pid_t childpid;
    DIR *dir; struct dirent *diread;
    vector<char *> files;
    
    //opening fork
    childpid = fork();

    //-1 = error opening fork
    if (childpid == -1)
    {
        perror("Failed to fork");
    }
    //0 = child fork
    else if(childpid == 0){
        //changing dir to current one
        //if our file exist and the 2 arguments are not set -> normal output
        chdir(path);
        if(file_exist(fileToFind) && opti == false && optR == false)
        {
            cout << (long)getpid() << ": " << fileToFind << ": " << path << endl;
        }
        //if the argument -i is set -> read our current dir and store in vector
        else if (opti == true)
        {
           if ((dir = opendir(path)) != nullptr) {
                while ((diread = readdir(dir)) != nullptr) {
                    files.push_back(diread->d_name);
        }
        closedir (dir);
           }
        }
        else if (optR == true)
        {
            //d_type 4 = folder, 8 = file
            if ((dir = opendir(path)) != nullptr) {
                while ((diread = readdir(dir)) != nullptr) {
                    //files.push_back(diread->d_type);
                    if(diread->d_type == 4)
                    {
                        string spath = path;
                        string dname = diread->d_name;
                        string newPath = spath + dname;
                        int n = newPath.length();

                        char char_array[n+1];

                        strcpy(char_array, newPath.c_str());
                        myfork(char_array, fileToFind, opti, optR);

                        
                    }
                    files.push_back(diread->d_name);
        }
        closedir (dir);
        }
        }

        //file to find lower case
        //we need BOTH files to be lower case, because we have to compare them
        string ftf = fileToFind;
        transform(ftf.begin(), ftf.end(), ftf.begin(), ::tolower);

        //transforming the files from our dir into lower case and storing them in a vector
        for (string file : files) 
        {
            string realFile = file;
            transform(file.begin(), file.end(), file.begin(), ::tolower);
            //we compare both files -> output is an int value (0 = they are the same)
            //output like above
            int res = ftf.compare(file);
            if(res == 0)
            {
                cout << (long)getpid() << ": " << realFile << ": " << path << endl;
            }
            //else -> nothing found

        }

        //wait for all the child forks
        //kill them if they come here
        wait(NULL);
        kill((long)getpid(), SIGKILL);
        }

        
    }


/* function to read the input via getopt() and do different 
things depending on the paramter (-i, -R) and start the searchpath function */

void getOptions(int argc, char **argv)
{
    //defining variables
    const char* searchPath;
    int opt;
    bool optR, opti = false;
    int counter = 0;

    //different case for different input
    //goes through the whole input
    // -i and -R are enabled via a boolean that will switch to true
    while((opt = getopt(argc, argv, "Ri")) != -1)
    {
        switch(opt)
        {
            case 'R': 
                // true = argument is being used
                optR = true; 
                cout << "opt R specified" << endl;
                counter++;
                continue;
            case 'i': 
                opti = true; 
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

    //if it finds a '/' -> searchpath found 
    //else -> it's a file we are searching for -> calling function myfork()
    for(; optind < argc; optind++){     
        string argString = string(argv[optind]);
        if(argString.find('/')<argString.length())
        {
            searchPath = argv[optind];
            cout << searchPath << " is searchpath" << endl;
        }
        else
        {
            myfork(searchPath, argv[optind], opti, optR); //optI, optR
        }
    }
}

int main(int argc, char **argv)
{
    getOptions(argc, argv);
    return 0;
}