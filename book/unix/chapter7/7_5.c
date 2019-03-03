#include "../apue.h"
#include "../error.c"
#include <setjmp.h>
//test jmp
jmp_buf jmpbuffer;
void do_line(char *);
int main(void){
  char line[MAXLINE];
  
  if(setjmp(jmpbuffer)!=0)
    printf("ereeee");
  while(fgets(line,MAXLINE,stdin)!=NULL){
    do_line(line);
  }
}

void do_line(char *line){
  char *s="q";

  if (line[strlen(line)-1] == '\n')
    line[strlen(line)-1] = '\0';

  if(strcmp(line,s)==0){
    printf("jmp\n");
    longjmp(jmpbuffer,1);
  }else{
    printf("%s\n",line);
  }



}
