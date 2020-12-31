#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>


extern int errno;
void do_ls(char*);
int main(int argc, char* argv[])
{
    if(argc==1)
    {
        do_ls(".");
    }
    else{

        int i=0;
        while(++i<argc)
        {
            printf("directory listing of %s: \n ", argv[i]);
            do_ls(argv[i]);
        }
    }
    return 0;

}
void do_ls(char* dir)
{
    struct dirent *entry;
    DIR * dp=opendir(dir);
    if(dp==NULL)
    {
        fprintf(stderr, "cannot open directory: %s\n",dir );
        return;
    }
    errno=0;
    struct stat buf;
 
    while((entry = readdir(dp)) != NULL)
    {
        if(entry ==NULL && errno != 0)
        {
            perror("readdir failed");
            exit(errno);
        }
        else
        {
            if(entry->d_name[0]=='.')
            {
                continue;
            }
            //printf("%s\n",entry->d_name);
            if (lstat(entry->d_name, &buf)<0)
            {
                perror("Error in stat");
                exit(1);
            }
            if ((buf.st_mode &  0170000) == 0010000)
            {
                printf("\033[0;31m");
                printf("%s\n", entry->d_name);
                printf("\033[0m");
            }
            else if ((buf.st_mode &  0170000) == 0020000)
            {
                printf("\033[0;32m");
                printf("%s\n", entry->d_name);
                printf("\033[0m");
            }
            else if ((buf.st_mode &  0170000) == 0040000)
            {
                printf("\033[0;33m");
                printf("%s\n", entry->d_name);
                printf("\033[0m");
            }
            else if ((buf.st_mode &  0170000) == 0060000)
            {
                printf("\033[0;34m");
                printf("%s\n", entry->d_name);
                printf("\033[0m");
            }
            else if ((buf.st_mode &  0170000) == 0100000)
            {
                printf("\033[0;35m");
                printf("%s\n", entry->d_name);
                printf("\033[0m");
            } 
            else if ((buf.st_mode &  0170000) == 0120000)
            {
                printf("\033[0;36m");
                printf("%s\n", entry->d_name);
                printf("\033[0m");
            }
            else if ((buf.st_mode &  0170000) == 0140000)
            {
                printf("\033[1;31m");
                printf("%s\n", entry->d_name);
                printf("\033[0m");
            }
            else
            { 
                printf("Unknwon mode\n");
            }
        }
    }   
    closedir(dp);
}
