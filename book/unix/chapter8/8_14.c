#include "../apue.h"
#include "../error.c"

int main(int argc,char *argv[]){
  int status;
  FILE *fp;
  
  
  if(argc<2)
    err_quit("less argc");

  printf("uid=%d,euid=%d\n",getuid(),geteuid());
  

  if((fp=fopen("/etc/securetty","rb"))==NULL){
      err_sys("fopen err");
  }
 
//if((status=system(argv[1]))<0)
//  err_sys("system err");

  exit(0);
}
