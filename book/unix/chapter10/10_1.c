#include "../apue.h"
#include "../error.c"

static void sig_usr(int);

int main(void){
  
  if(signal(SIGUSR1,sig_usr)==SIG_ERR){
    err_sys("cant catch usr1");
  }
  if(signal(SIGUSR2,sig_usr)==SIG_ERR){
    err_sys("usr2");
  }

  for(;;)
    pause();

}


static void sig_usr(int signo){
  //sleep(10);//若有另一个信号则会覆盖
  if(signo==SIGUSR1)
    printf("rev sigusr1\n");
  else if(signo==SIGUSR2)
    printf("rev sigusr2\n");
  else
    err_dump("rev signal %d\n",signo);

}
