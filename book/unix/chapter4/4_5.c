#include "../apue.h"
#include "../error.c"
#include <fcntl.h>
int main(void){

  if(open("tmpfile",O_RDWR|O_CREAT)<0){
      err_sys("open error");
  }

  if(unlink("tmpfile")<0){
     err_sys("unlink error");
  }

  printf("file unlinked\n");
  sleep(15);
  printf("done\n");
  exit(0);
}
