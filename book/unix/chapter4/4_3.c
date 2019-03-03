#include "../apue.h"
#include "../error.c"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>



#define RWRWRW          (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main(void){

  umask(0);
  if(open("foo",O_WRONLY|O_CREAT|O_TRUNC,RWRWRW)<0){
    err_sys("create error for foo");
  }

  umask(S_IRGRP);
  if(open("bar",O_WRONLY|O_CREAT|O_TRUNC,RWRWRW)<0){
    err_sys("create error for bar");
  }

  exit(0);
}
