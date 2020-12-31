#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>

extern int errno;
int c=0,siz=200;
char** rec;

int search(char *tt)
{
	for(int l=0;l<c;l++)
	{
		if(rec[l]==tt)
		{
			return 1;
		}
	}
	return 0;
}


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

void ls4(char *name,char *parent)//do ls
{
	if(name!=parent)
	{
		char *t1=(char*)malloc(strlen(name)+strlen(parent)+2);
		t1=strcpy(t1,parent);
		t1=strcat(t1,"/");
		t1=strcat(t1,name);
		name=t1;
	}
	DIR *dptr=opendir(name);
	struct dirent *content;
	errno=0;
	
	if (dptr == NULL)
	{
      	return;
   	}

   	if(name != parent)
   	{
   		printf("\n\n%s/ : \n\n",name);
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
			if(!search(name))
			{
				if(c%200==0)
				{
					rec=realloc(rec,siz+200);
					siz+=200;
				}
				ls3(name);
				rec[c++]=name;			
			}
			ls4(content->d_name,name);
		}
	}
	closedir(dptr);
}

int main(int argc, char const *argv[])
{
	rec=(char**)malloc(siz);
	if(argc==1)
	{
		ls4(".",".");
	}
	for(int i=1;i<argc;i++)
	{
		DIR *dptr=opendir(argv[i]);
		if(dptr==NULL)
		{
			fprintf(stderr, "Cannot open directory:%s\n",argv[i]);
			continue;
		}
		printf("\n--------------------------");
		printf("\nLS for : %s",argv[i]);
		printf("\n--------------------------\n");
		ls4(argv[i],argv[i]);
	}
	free(rec);
	return 0;
}
