#include "../apue.h"
#include "../error.c"
#include <fcntl.h>
#include <sys/mman.h>
//mmap 复制
int main(int argc,char *argv[]){
  int fdin,fdout;
  void *src,*dst;
  struct stat statbuf;
  
  printf("%d\n",argc);
  if(argc!=3)
    err_quit("usage:%s",argv[0]);
  
  if((fdin=open(argv[1],O_RDONLY))<0)
    err_sys("cant open %s",argv[1]);
  
  if((fdout=open(argv[2],O_RDWR|O_CREAT|O_TRUNC))<0)
    err_sys("cant open %s 2",argv[2]);
  
  if(fstat(fdin,&statbuf)<0)
    err_sys("fstat err");
  
  if(lseek(fdout,statbuf.st_size-1,SEEK_SET)==-1)
    err_sys("fstat err");
  
  if(write(fdout,"",1)!=1)
    err_sys("write err");
  
  if((src=mmap(0,statbuf.st_size,PROT_READ,MAP_SHARED,fdin,0))==MAP_FAILED)
    err_sys("mmap err for input");
  
  if((dst=mmap(0,statbuf.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fdout,0))==MAP_FAILED)
    err_sys("mmap err for output");

  memcpy(dst,src,statbuf.st_size);
  exit(0);
}
