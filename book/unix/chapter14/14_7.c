#include "../apue.h"
#include <stropts.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "../error.c"
//#include "/usr/src/debug/glibc-2.17-c758a686/bits/stropts.h"
//#define __SID           ('S' << 8)
//#define I_CANPUT    (__SID |34)
//判断是否是流设备  神坑I_CANPUT@todo  the author say it is out of date ,so see third section
int isastream(int fd){
  return(ioctl(fd,I_CANPUT,0)!=-1);
}


int main(int argc,char *argv[]){
  int i,fd;
  for(i=1;i<argc;i++){
    if((fd=open(argv[i],O_RDONLY))<0){
      err_ret("%s:cant open",argv[i]);
      continue;
    }

    if(isastream(fd)==0)
      err_ret("%s:not a stream",argv[i]);
    else
      err_msg("%s:stream device",argv[i]);
  }
  exit(0);
}
