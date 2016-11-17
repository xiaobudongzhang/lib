#include "../error.c"
#include "../apue.h"
#include <fcntl.h>

int main(int argc,char * argv[])
{
  if(argc!=2){
    err_quit("argc need 2");
  }
  if(access(argv[1],R_OK)){
    err_ret("no access");
  }else{
    printf("read access ok!\n");
  }
  

  if(open(argv[1],O_RDONLY)<0){
    err_ret("no open");
  }else{
    printf("open ok\n");
  }

  exit(0);
  
}
