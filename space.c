#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    DIR* dirp;
    struct dirent* dp;
    struct stat statusInfo;
    int statResult;
    
    printf("space ");
    scanf("%s", dirname);

    dirp = opendir (dirname);
    
    while(dp = readdir(dirp))
    {      
        if (!strcmp (dp->d_name, "."))
            continue;
      
        if (!strcmp (dp->d_name, ".."))    
            continue;
      
        printf("%s  --  ", dent->d_name);
        if (!stat(dent->d_name, &statusInfo))
        {
            printf("%u bytes\n", (unsigned int)statusInfo.st_size);
        }
        else
        {
            printf("(stat() failed for this file)\n");
        }
    }
    closedir(dirp);

    return 0;
}
