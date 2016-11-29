#include "../apue.h"
#include "../error.c"
#include "10_10.c"
//测试信号屏蔽字打印
void sig_int(int);
int main(void){

  
 
  signal(SIGINT,sig_int);
 
  sleep(10);

  
  return (0);
}

void sig_int(int signo){
  pr_mask("test sigint");
  printf("\nsig_int\n");
  return;
}
