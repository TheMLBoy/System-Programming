/* 

*  Video Lecture 11

*  morev4.c: handle io rediretion....reverse video featureread and print one page then pause for a few special commands ('q', ' ' , '\n')

 */



#include <stdio.h>

#include <stdlib.h>



#define  PAGELEN  20

#define  LINELEN  512



int number_of_lines(FILE *fc)

{

   int count_lines = 0;

   char chr;

   chr = getc(fc);

   while (chr != EOF)

   {

      if (chr == '\n')

      {

         count_lines = count_lines + 1;

      }

      chr = getc(fc);

    }

   return count_lines;

}



void do_more(FILE *fp)

{

   int line_count = 0,lines=0;

   int rv;

   char buffer[LINELEN];

   FILE* fp_tty = fopen("/dev//tty", "r");

   int total_lines = number_of_lines(fp);

   rewind(fp);

   while (fgets(buffer, LINELEN, fp)){

      fputs(buffer, stdout);

      line_count++;

   lines++;

      if (line_count == PAGELEN){

         rv = get_input(fp_tty,(float)((float)lines/(float)total_lines));     

         if (rv == 0){//user pressed q

            printf("\033[1A \033[1B \033[2K \033[1G");

            break;//

         }

         else if (rv == 1){//user pressed space bar

            printf("\033[1A \033[1B \033[2K \033[1G");

            line_count -= PAGELEN;

         }

         else if (rv == 2){//user pressed return/enter

            printf("\033[1A \033[2K \033[1G");

            line_count -= 1; //show one more line

            }

         else if (rv == 3){ //invalid character

            printf("\033[1A \033[1B \033[2K \033[1G");

            break; 

         }

      }

  }

}



int get_input(FILE* cmdstream,double percent)

{

   int c;      

   printf("\033[7m --more--(%3.2f%%) \033[m",percent*100);

     c = getc(cmdstream);

      if(c == 'q')

    return 0;

      if ( c == ' ' )         

    return 1;

      if ( c == '\n' )  

    return 2;  

      return 3;

   return 0;

}



int main(int argc , char *argv[])

{

   int i=0;

   if (argc == 1){

      do_more(stdin);

   }

   FILE * fp;

   while(++i < argc){

      fp = fopen(argv[i] , "r");

      if (fp == NULL){

         perror("Can't open file");

         exit (1);

      }

      do_more(fp);

      fclose(fp);

   }  

   return 0;

}
