#include "../apue.h"
#include "../error.c"
#include <linux/limits.h>

int main(void){
  char *ptr;
  int size;
  
  if(chdir("/var/github")<0)
    err_sys("chdir failed");
  
  
  ptr=malloc(PATH_MAX);

  if(getcwd(ptr,PATH_MAX)==NULL)
    err_sys("getcwd failed");

  printf("cwd =%s\n",ptr);
  exit(0);
}
