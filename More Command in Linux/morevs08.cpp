#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>


#define pLen 20
#define lineLen 512
float pr=0;
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
void position(FILE *fp, int val){
      fseek(fp,0,SEEK_SET);
        char buffer[lineLen];
        FILE* tty = fopen("/dev//tty" , "r");
      for(int i=0;i<val;i++)
      {fgets(buffer, lineLen, fp);}
      return;
}
int string_tosearch(char s[512], FILE *fp, int p){
      int saved = ftell(fp);
      fseek(fp,0,SEEK_SET);
      char buffer[lineLen];
      int count=0;
      FILE* tty = fopen("/dev//tty" , "r");
      while(fgets(buffer, lineLen, fp)){
      if((strstr(buffer,s) != NULL )&&( count <= p+2 && count >= p)){   
      printf("\033[1A \033[2K \033[1G");  
      position(fp,p);
      return 0;}
      else if(strstr(buffer,s) != NULL && count > p+2){
        printf("\033[1A \033[2K \033[1G");
      printf("..skipping\n");
      position(fp,count-2);
      return count-p-2;}
      count++;
      }
      printf("\033[1A \033[2K \033[1G");
      printf("\033[7m Sequence not found \033[m\n");
      fseek(fp, saved, SEEK_SET);
      return 1; 
}

void fmore(FILE *fp )
{
	int lines=0;
	int rv=0;
	char buffer[lineLen];
	char* searchk[100],pre1[100],pre2[100];
	while(fgets(buffer,lineLen,fp))
	{
		fputs(buffer,stdout);
		lines++;
		pr++;
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
			else if(rv == 4){

      			printf("\033[2K \033[1G");
      			printf("/");      
      			char inps[lineLen];
      			scanf("%[^\n]%*c", inps);     
      			int val = string_tosearch(inps,fp,pr);
      			if(val==1){ exit(0);}
       			 				lines-=pLen;
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
	 if(c=='/')
      return 4;
    
	return 3;
}
