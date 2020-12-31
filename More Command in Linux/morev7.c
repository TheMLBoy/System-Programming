#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include<sys/wait.h>
#include <unistd.h>
#include <termios.h>
#define PAGELEN 20
#define LINELEN 512
int getsize();
int get_input(FILE *);
void do_more(FILE *);
int main(int argc, char *argv[]){
	int i=0;

	if(argc==1)
	{
		do_more(stdin);
	}
	FILE *fp;
	
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
int total_number_of_lines()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_row;
     

}
void do_more(FILE *fp)
{
	int LENGTH_OF_PAGE=total_number_of_lines();
	int no_of_lines=0;
	int rv;
	char buffer[LINELEN];
	FILE * fp_tty=fopen("/dev//tty","r");
	while(fgets(buffer,LINELEN,fp)){
		fputs(buffer,stdout);
		no_of_lines++;
		if(no_of_lines==LENGTH_OF_PAGE)
		{
			rv=get_input(fp_tty);
			if(rv==0)
			{
				printf("\033[1A \033[2K \033[1G");
				break;
			}
			else if(rv==1)
			{
				printf("\033[1A \033[2K \033[1G");
				no_of_lines-=PAGELEN;
			}
			else if(rv==2)
			{
				printf("\033[1A \033[2K \033[1G");
				no_of_lines-=1;
			}
			else if(rv==3)
			{
			    printf("\033[1A \033[2K \033[1G");
				break;
			}
			         
        
		}
	}
}
int get_input(FILE * cmdstream)
{
	int c;
	printf("\033[7m --more--(%%) \033[m");
	c=getc(cmdstream);
	if(c=='q')
	{
		return 0;
	}
	if(c==' '){
		return 1;
	}
	if(c=='\n')
	{
		return 2;
	}

	return 3;
return 0;
}
