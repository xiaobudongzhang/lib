#include "../apue.h"
#include "../error.c"

int main(void){
  char buf[8];
  //printf("%d::\n",MAXLINE);
  while(fgets(buf,8,stdin)!=NULL){
    if(fputs(buf,stdout)==EOF)
      err_sys("output error");
    
    if(ferror(stdin))
      err_sys("input error");
    exit(0);
  }

}
