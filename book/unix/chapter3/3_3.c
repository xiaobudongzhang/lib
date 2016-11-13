#include "../apue.h"
#include "../error.c"

#define BUFFSIZE 8

int main(void){
  int n;
  char buf[BUFFSIZE];

  while((n=read(STDIN_FILENO,buf,BUFFSIZE))>0)
    if(write(STDOUT_FILENO,buf,n)!=n)
      err_sys("write err");

  if(n<0){
    err_sys("read err");
  }

  exit(0);
}
