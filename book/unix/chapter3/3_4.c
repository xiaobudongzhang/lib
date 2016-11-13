#include "../apue.h"
#include "../error.c"
#include <fcntl.h>


int main(int argc,char *argv[]){

  int val;
  if(argc!=2)
    err_quit("less argc");
  
  if((val=fcntl(atoi(argv[1]),F_GETFL,0))<0)
    err_sys("fcntl err");

  switch(val&O_ACCMODE){
  case O_RDONLY:
    printf("read");
    break;
  case O_WRONLY:
    printf("write");
    break;
  case O_RDWR:
    printf("read write");
    break;
  default:
    err_dump("unkonwn access mode");
  }

  if(val&O_APPEND)
    printf(",append");
  if(val&O_NONBLOCK)
    printf(",nonblocking");

#if defined(O_SYNC)
  if(val&O_SYNC)
    printf(",sync writes");
#endif

#if !defined(_POSIX_C_SOURCE)&&defined(O_FSYNC)
  if(val&O_FSYNC)
    printf(",sync writes2");
#endif

  putchar('\n');
  exit(0);
}
