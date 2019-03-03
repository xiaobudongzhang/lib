#include "../apue.h"
#include "../error.c"

static void my_exit1(void);
static void my_exit2(void);

int main(void){

  if(atexit(my_exit2)!=0)
    err_sys("cant reg exit2");

  if(atexit(my_exit1)!=0)
    err_sys("cant reg exit1");

  if(atexit(my_exit1)!=0)
    err_sys("cant reg exit1");

  printf("main is done\n");
  return (0);
}

static void my_exit1(void){
  printf("first exit\n");
}
static void my_exit2(void){
  printf("second exit\n");
}
