#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

/* This is just a sample code, modify it to meet your need */
int main(int argc, char **argv)
{
    DIR* dirp;
    struct dirent* dp;
    FILE    *entry_file;
    char    buffer[BUFSIZ];
    
    printf("space ");
    scanf("%s", dirname);

    /* Scanning the in directory */
    if (NULL == (dirp = opendir (dirname))) 
    {
        fprintf(stderr, "Error : Failed to open input directory - %s\n", strerror(errno));
        fclose(common_file);

        return 1;
    }
    while ((dp = readdir(dirp))) 
    {
        /* On linux/Unix we don't want current and parent directories
         * On windows machine too, thanks Greg Hewgill
         */
        if (!strcmp (dp->d_name, "."))
            continue;
        if (!strcmp (dp->d_name, ".."))    
            continue;
        
        /* Open directory entry file for common operation */
        /* TODO : change permissions to meet your need! */
        entry_file = fopen(dp->d_name, "rw");
        if (entry_file == NULL)
        {
            fprintf(stderr, "Error : Failed to open entry file - %s\n", strerror(errno));

            return 1;
        }

        /* Doing some struf with entry_file : */
        /* For example use fgets */
        while (fgets(buffer, BUFSIZ, entry_file) != NULL)
        {
            /* Use fprintf or fwrite to write some stuff into common_file*/
        }

        /* When you finish with the file, close it */
        fclose(entry_file);
    }
    closedir(dirp);

    return 0;
}
