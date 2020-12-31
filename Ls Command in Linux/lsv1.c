
//Reading multiple directories
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<errno.h>

extern int errno;
void do_ls(char*);
int main(int argc,char* argv[]){
	if(argc==1)
	{
		do_ls(".");
		return 0;
	}
	int i=0;
	while(++i<argc)
	{
	printf("Inside Directory of %s:\n",argv[i]);
	do_ls(argv[i]);
	}
	return 0;
}
//testing multiple commits
void do_ls(char* dir){
	struct dirent* entry;
	DIR* dp=opendir(dir);
	if(dp==NULL)
	{
		printf("Can't Open this Directory!!:\n");
		return;
	}
	errno=0;
	while((entry = readdir(dp)) !=NULL)
	{
		if(entry==NULL && errno!=0)
		{
			perror("readdir failed");
			exit(errno);
		}
		printf("%s\n	",entry->d_name);
		
	}
	closedir(dp);
}	
