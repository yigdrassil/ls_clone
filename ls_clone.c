/** Trying to make a smaller implementation of the ls command, to practice C a little bit */


#include <stdio.h>
#include <stdlib.h>

#include <dirent.h> // This library contains the DIR pointer for a directory and functions to manipulate the DIR pointer. Check man page for it

#include <errno.h> // Using this to handle possible errors

#include <unistd.h> // Need this for the getopt() function to process cmd line arguments

#include <sys/stat.h> // This one contains the struct for the different data on the files/folders


/**
 * types.h is needed by the pwd.h library. What we need is the pwd.h library to use the lookup functions to actually make the numbers into user id and group
 * 
 * for more information check out the man 3 getpwuid
 */
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>


int show_all = 0; //declaring an option for the ls command


/**
 * Hleper func for gettint the appropriate string formatting for each file/document
 * 
 * check man 2 stat -> talks about the C stat library and some implementations
 * 
 * check man 7 inode -> talks about the macros implemented to check if the file is a dir, a socket, a block device, etc, or the masks if i wanna go full nelson :))
 */

void mode_string(mode_t mode, char *str)
{
    //fingering out the file/dir type, well dir is also a file, but hey
    if (S_ISDIR(mode))
    {
        str[0] = 'd';
    }
    else if (S_ISLNK(mode))
    {
        str[0] = 'l';
    }
    else if (S_ISCHR(mode))
    {
        str[0] = 'c';
    }
    else if (S_ISBLK(mode))
    {
        str[0] = 'b';
    }
    else if (S_ISFIFO(mode))
    {
        str[0] = 'p';
    }
    else if (S_ISSOCK(mode))
    {
        str[0] = 's';
    }
    else
    {
        str[0] = '-';
    }


    // Do the checks for the rights part, with masks
    str[1] = (mode & S_IRUSR) ? 'r' : '-';
    str[2] = (mode & S_IWUSR) ? 'w' : '-';
    str[3] = (mode & S_IXUSR) ? 'x' : '-';
    str[4] = (mode & S_IRGRP) ? 'r' : '-';
    str[5] = (mode & S_IWGRP) ? 'w' : '-';
    str[6] = (mode & S_IXGRP) ? 'x' : '-';
    str[7] = (mode & S_IROTH) ? 'r' : '-';
    str[8] = (mode & S_IWOTH) ? 'w' : '-';
    str[9] = (mode & S_IXOTH) ? 'x' : '-';
    str[10] = '\0'; //Terminathor char

}



/**
 * The print function fo print user names and the group
 */

void print_long(const char *dir, const char *name) {
    char fullpath[4096];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", dir, name);

    struct stat stats;
    if (lstat(fullpath, &stats) < 0) {
        perror(name);
        return;
    }
    char modes[11];
    mode_string(stats.st_mode, modes);

    struct passwd *pw = getpwuid(stats.st_uid);
    struct group  *gr = getgrgid(stats.st_gid);
    const char *user = pw ? pw->pw_name : "?";
    const char *group = gr ? gr->gr_name : "?";

    printf("%s %s %s %s \n", modes, user, group, name);











}



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
        
        print_long(path, entry->d_name);

        //printf( "%s \n", (*entry).d_name );  // entry->d_name can be rewritten as (*entry).d_name  you basically dereference the pointer
    }

    closedir(dirpath);

    return 0;

}