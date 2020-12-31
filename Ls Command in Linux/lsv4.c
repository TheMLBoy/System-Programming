
//Reading multiple directories
//showing them in coloumnary format
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
		printf("Inside Current Directory\n");
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

void do_ls(char* dir){
	struct dirent* entry;
	DIR* dp=opendir(dir);
	if(dp==NULL)
	{
		printf("Can't Open this Directory!!:\n");
		return;
	}
	errno=0;
	int count=0;
	while((entry = readdir(dp)) !=NULL)
	{
		if(entry==NULL && errno!=0)
		{
			perror("readdir failed");
			exit(errno);
		}
		printf("%-10s	",entry->d_name);
		
	}
	printf("\n");
	closedir(dp);
}	
