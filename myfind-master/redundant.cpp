

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

    //bool optR = false;
    //bool opti = false;

    //get all arguments
    //start new process for every file 
    //check if file exists in search path
    //output if seach was successfull or not

// int listFiles(char* workingDirectory, DIR* dirpath, dirent* direntry){

//     getcwd(workingDirectory, PATH_MAX);
//     printf("Current working directory: %s\n", workingDirectory);

//     if((dirpath = opendir(workingDirectory)) == NULL)
//     {
//         perror("Failed to open directory");
//         return -1;
//     }

//     cout << "Files in current directory: " << endl;
//     while((direntry = readdir(dirpath)) != NULL)
//     {
//         cout << direntry->d_name << " ";
//         cout << to_string(direntry->d_type) << endl; //d_type 4 == folder, d_type 8 == file
//     }
//     cout << endl;

//     chdir(".."); //changes the current directory of the process to .. (which is the parent directory)
//     return 1;
// }