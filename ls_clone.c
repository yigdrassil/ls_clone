/** Trying to make a smaller implementation of the ls command, to practice C a little bit */


#include <stdio.h>
#include <stdlib.h>

#include <dirent.h> // This library contains the DIR pointer for a directory and functions to manipulate the DIR pointer. Check man page for it

#include <errno.h> // Using this to handle possible errors


int main(int argc, char **argv)
{

    const char *path = argv[1];

    DIR *dirpath = opendir(path);

    if(!dirpath)
    {
        perror("opendir");

        return 1;
    }

    struct dirent *entry; // Declaring a struct of type dirent, to access the value returned by readdir() function
    

/** If the function is continuously called, it reads the next directory in the dirpath. Make it a loop and iterate untill NULL !!!Need to debug this shit to understand it!!!
 * 
    entry = readdir(dirpath); // Storing the info from readdir func
    printf("%s\n", entry->d_name);

    entry = readdir(dirpath); // Storing the info from readdir func
    printf("%s\n", entry->d_name);

    entry = readdir(dirpath); // Storing the info from readdir func
    printf("%s\n", entry->d_name);

    entry = readdir(dirpath); // Storing the info from readdir func
    printf("%s\n", entry->d_name);

    entry = readdir(dirpath); // Storing the info from readdir func
    printf("%s\n", entry->d_name);
*/

    while ( (entry = readdir(dirpath)) != NULL )
    {
        printf( "%s \n", (*entry).d_name );  // entry->d_name can be rewritten as (*entry).d_name  you basically dereference the pointer
    }


    return 0;

}