#include<stdlib.h>
#include<stdio.h>

#define pLen 20
#define lineLen 512

void fmore(FILE *);
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
		fmore(fp);
		fclose(fp);
	}
	return 0;
}

void fmore(FILE *fp)
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
				break;
			}
			else if (rv==1)
			{
				lines-=pLen;
			}
			else if(rv==2)
			{
				lines-=1;
			}
			else if(rv==3)
			{
				break;
			}
			
		}
	}
}

int get_input()
{
	int c;
	c=getchar();
	if(c=='q')
	{
		return 0;
	}
	if(c==' ')
	{
		//printf("aksjdsajk");
		return 1;
	}
	if(c=='\n')
	{
		return 2;
	}
	return 3;
}
