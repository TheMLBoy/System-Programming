#include<sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>


#define pLen 20
#define lineLen 512

void fmore(FILE* ,char* f);
int get_input();
int main(int argc, char *argv[])
{
	int i=0;
	if(argc==1)
	{
		printf("Help page");
		exit(0);
	}
	FILE *fp;
	while(++i<argc)
	{
		fp=fopen(argv[i],"r");
		if(fp==NULL)
		{
			perror("can't");
			exit(1);
		}
		fmore(fp,argv[i]);
		fclose(fp);
	}
	return 0;
}

void fmore(FILE* fp ,char* f)
{
	int lines=0;
	int rv=0;
	char buffer[lineLen];
	while(fgets(buffer,lineLen,fp))
	{
		fputs(buffer,stdout);
		lines++;
		if(lines==pLen)
		{
			rv=get_input();
			if(rv==0)
			{
				printf("\033[1A \033[2K \033[1G");
				break;
			}
			else if (rv==1)
			{
				printf("\033[1A \033[2K \033[1G");
				lines-=pLen;
			}
			else if(rv==2)
			{
				printf("\033[1A \033[2K \033[1G");
				lines-=1;
			}
			 else if (rv == 4)
    	     {
        	    printf("\033[1A \033[2K \033[1G");
            	int pid=fork(); 
            	if(pid==0)
            	{
               		char *path ="/bin/vim";
               		execl(path,path,f,NULL);
            	}
            	else
            	{
               		wait(NULL);
               		lines-=pLen;
            	}
         }
        
			else if(rv==3)
			{
				printf("\033[1A \033[2K \033[1G");
				break;
			}
			
		}
	}
}

int get_input()
{
	int c;
	printf("\033[7m --more--(%%) \033[m");
	c=getchar();
	if(c=='q')
	{
		return 0;
	}
	if(c==' ')
	{
	  	return 1;
	}
	if(c=='\n')
	{
		return 2;
	}
	 if(c=='v')
      return 4;
    
	return 3;
}
