#include "../apue.h"
#include <errno.h>
#include <fcntl.h>
#include "../error.c"
//异步io
char buf[500000000];

void set_f1(int fd,int flags){
  int val;

  if((val=fcntl(fd,F_GETFL,0))<0){
    err_sys("fcntl error");
  }

  val |=flags;

  if(fcntl(fd,F_SETFL,val)<0){
    err_sys("fcntl set error");
  }
}

int main(void){
  int ntowrite,nwrite;
  char *ptr;
  
  ntowrite =read(STDIN_FILENO,buf,sizeof(buf));
  fprintf(stderr,"read %d bytes \n",ntowrite);
  
  set_f1(STDOUT_FILENO,O_NONBLOCK);
  
  ptr=buf;
  while(ntowrite>0){
    errno=0;
    nwrite=write(STDOUT_FILENO,ptr,ntowrite);
    fprintf(stderr,"nwrite =%d,errno=%d\n",nwrite,errno);
    
    if(nwrite>0){
      ptr+=nwrite;
      ntowrite-=nwrite;
    }
  }
  exit(0);
}


