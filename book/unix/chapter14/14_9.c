#include "../apue.h"
#include <fcntl.h>
#include <stropts.h>
//#include <sys/conf.h>
#include "../error.c"
//流文件
int main(int argc,char *argv[]){
  int fd,i,nmods;
  struct str_list list;
  
  if(argc!=2){
    err_quit("usage:%s<pathname>",argv[0]);
  }
  
  if((fd=open(argv[1],O_RDONLY))<0)
    err_sys("cant open %s",argv[1]);
  
  if((nmods=ioctl(fd,I_LIST,(void *)0))<0)
    {}   //    err_sys("i_list err");
  else{
    printf("ok:%s",argv[1]);
  }
  exit(0);
}
