#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>

extern int errno;

int compareStrings(const void *stackA, const void *stackB)
{
  	const char *a=*(const char**)stackA;
  	const char *b=*(const char**)stackB;
  	return strcasecmp(a,b);
}

void ls3(char *name)
{
	DIR *dptr=opendir(name);
	struct dirent *content;
	errno=0;
	int i=0,size=100;
	char** arr = (char**) malloc(size);
	if (dptr == NULL)
	{
    	fprintf(stderr, "Cannot open directory:%s\n",name);
      	return;
   	}

	while((content=readdir(dptr))!=NULL)
	{
		if(content == NULL && errno != 0)
		{
        	perror("readdir system call failed");
        	exit(errno);
     	}
		else
		{
			if(content->d_name[0]=='.')
			{
				continue;
			}
			if(i%100==0)
			{
				arr=realloc(arr,size+100);
				size+=100;
			}
			arr[i]=content->d_name;
		}
		i++;
	}
	
	qsort(arr,i,sizeof(char*),compareStrings);
	
	for(int j=0;j<i;j++)
	{
		printf("%s\n",arr[j]);
	}

	free(arr);
	closedir(dptr);
}

int main(int argc, char const *argv[])
{
	if(argc==1)
	{
		ls3(".");
	}
	for(int i=1;i<argc;i++)
	{
		printf("\n--------------------------");
		printf("\nLS for : %s",argv[i]);
		printf("\n--------------------------\n");
		ls3(argv[i]);
	}
	return 0;
}
