#include<unistd.h>
#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
#include<string.h>

extern int errno;
void do_ls(char*);
void show_stat_info(char*);
int compareStrings(const void *stackA, const void *stackB)
{
  	const char *a=*(const char**)stackA;
  	const char *b=*(const char**)stackB;
  	return strcasecmp(a,b);
}
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
	int i=0,size=100;
	char** arr = (char**) malloc(size);
	
	if(dp==NULL)
	{
		fprintf(stderr, "cannot open directory: %s\n",dir );
		return;
	}
	errno=0;
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
			if(i%100==0)
			{
				arr=realloc(arr,size+100);
				size+=100;
			}
			arr[i]=entry->d_name;
		}
		i++;
	}
	qsort(arr,i,sizeof(char*),compareStrings);
	for(int j=0;j<i;j++)
	{
		show_stat_info(arr[j]);
	}

	free(arr);
	
	closedir(dp);
}

void show_stat_info(char *fname)
{
	struct stat info;
	int rv=lstat(fname,&info);
	if(rv==-1)
	{
		perror("stat failed");
		exit(1);
	}
	struct stat buf;
   int mode = buf.st_mode; 
   char str[10];
   strcpy(str, "---------");
//owner  permissions
   if((mode & 0000400) == 0000400) str[0] = 'r';
   if((mode & 0000200) == 0000200) str[1] = 'w';
   if((mode & 0000100) == 0000100) str[2] = 'x';
//group permissions
   if((mode & 0000040) == 0000040) str[3] = 'r';
   if((mode & 0000020) == 0000020) str[4] = 'w';
   if((mode & 0000010) == 0000010) str[5] = 'x';
//others  permissions
   if((mode & 0000004) == 0000004) str[6] = 'r';
   if((mode & 0000002) == 0000002) str[7] = 'w';
   if((mode & 0000001) == 0000001) str[8] = 'x';
//special  permissions
   if((mode & 0004000) == 0004000) str[2] = 's';
   if((mode & 0002000) == 0002000) str[5] = 's';
   if((mode & 0001000) == 0001000) str[8] = 't';
   printf("%s\n", str);

	printf("mode: %o\n",info.st_mode );
	printf("link count: %ld\n",info.st_nlink );
	printf("user: %d\n",info.st_uid);
	printf("group: %d\n",info.st_gid);
	printf("size: %ld\n",info.st_size);
	printf("modtime: %ld\n",info.st_mtime);
	printf("name: %s\n",fname);
}
