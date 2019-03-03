#include "../apue.h"
#include "../error.c"
#include <fcntl.h>
#include <sys/types.h>   
#include <sys/stat.h>

char buf1[]="abcdefghi";
char buf2[]="ABCDEFGHIJ";

int main(void){

  int fd;
  
  if((fd=open("file.hole",O_WRONLY|O_CREAT|O_TRUNC))<0){
    err_sys("create err");
  }

  if(write(fd,buf1,10)!=10){
    err_sys("write err");
  }

  if(lseek(fd,16384,SEEK_SET)==-1){
    err_sys("lseek err");
  }
  
  if(write(fd,buf2,10)){
    err_sys("buf2 write err");
  }
  
  exit(0);
}
