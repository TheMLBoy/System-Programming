#include<stdio.h>
#include<stdlib.h>
#define LINELEN 512
void do_more(FILE *);
int main(int argc, char *argv[]){
	if(argc==1)
	{
		printf("This is help page\n");
		exit(0);
	}
	FILE *fp;
	int i=0;
	while(++i<argc)
	{
		fp=fopen(argv[i],"r");
		if(fp==NULL)
		{
			perror("can't open file");
			exit(1);
		}
		do_more(fp);
		fclose(fp);
	}
}
void do_more(FILE *fp)
{
	char buffer[LINELEN];
	while(fgets(buffer,LINELEN,fp)){
		fputs(buffer,stdout);
	}
}