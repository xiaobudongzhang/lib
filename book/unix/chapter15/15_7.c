#include "../apue.h"
#include "../error.c"
#include <sys/wait.h>
#include "../lib/popen.c"

int main(void){
  char line[MAXLINE];
  FILE *fpin;
  
  if((fpin=popen2("./filter","r"))==NULL)
    err_sys("popen err");
  for(;;){
    fputs("prompt>",stdout);
    fflush(stdout);
    if(fgets(line,MAXLINE,fpin)==NULL)
      break;
    if(fputs(line,stdout)==EOF)
      err_sys("fputs err to pipe");
  }
  
  if(pclose(fpin)==-1)
    err_sys("pclose err");
  putchar('\n');
  exit(0);
    
}
