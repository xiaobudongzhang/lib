#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include "../lib/lockfile.c"
#define LOCKFILE "/var/run/daemon.pid"
#define LOCKMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

//测试锁与唯一调用

int already_runing(void){
  int fd;
  char buf[16];
  
  fd=open(LOCKFILE,O_RDWR|O_CREAT,LOCKMODE);
  if(fd<0){
    printf("open err\n");
    syslog(LOG_ERR,"cantps open %s:%s",LOCKFILE,strerror(errno));
    exit(0);
  }
  printf("hi\n");
  if(lockfile(fd)<0){
    if(errno==EACCES||errno==EAGAIN){
      close(fd);
      return(1);
    }
    printf("lock err\n");
    syslog(LOG_ERR,"cantps lock %s:%s",LOCKFILE,strerror(errno));
    exit(1);
  }

  ftruncate(fd,0);
  sprintf(buf,"%ld",(long)getpid());
  write(fd,buf,strlen(buf)+1);
  return(0);
  
}

int main(void){
  already_runing(); 
  already_runing(); 
  already_runing(); 
  already_runing(); 
  already_runing(); 
  already_runing();
  already_runing();
  already_runing();
  exit(0);
}
