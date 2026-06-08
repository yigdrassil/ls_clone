/** Trying to make a smaller implementation of the ls command, to practice C a little bit */


#include <stdio.h>
#include <stdlib.h>

#include <dirent.h> // This library contains the DIR pointer for a directory and functions to manipulate the DIR pointer. Check man page for it

#include <errno.h> // Using this to handle possible errors

#include <unistd.h> // Need this for the getopt() function to process cmd line arguments


int show_all = 0; //declaring an option for the ls command

int main(int argc, char **argv)
{

    int opt;

    while ( (opt = getopt(argc, argv, "a")) != -1 )
    {
        if (opt == 'a')
        {
            show_all = 1;
            printf("option set\n"); //testing if the code comes in here :)  didn't set up debugging yet
        }
        else
        {
            
                fprintf(stderr, "usage: %s [-a] [path]\n", argv[0]); // print an error message to the standard output, and give a hint of usage

                return 1;
        }
    }



    const char *path = (optind < argc) ? argv[optind] : ".";

    DIR *dirpath = opendir(path);

    if(!dirpath)
    {
        perror("opendir");  // Tis one sends out nicely formatted error messages :D

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
        if ( !show_all && entry->d_name[0] == '.' ) // if the first character in the directory name starts with a . then ignore it
        {
            continue; 
        } 
            

        printf( "%s \n", (*entry).d_name );  // entry->d_name can be rewritten as (*entry).d_name  you basically dereference the pointer
    }

    closedir(dirpath);

    return 0;

}