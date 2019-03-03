#include "../apue.h"
#include "../error.c"
#include "10_10.c"
//保护临界区不被信号中断
static void sig_int(int);

int main(void){
  
  sigset_t newmask,oldmask,waitmask;
  
  pr_mask("pro start:");

  if(signal(SIGINT,sig_int)==SIG_ERR)
    err_sys("sigint err");
  
  sigemptyset(&waitmask);
  sigaddset(&waitmask,SIGUSR1);
  sigemptyset(&newmask);
  sigaddset(&newmask,SIGINT);

  if(sigprocmask(SIG_BLOCK,&newmask,&oldmask)<0)
    err_sys("sig_block  err");

  pr_mask("in critical region:");
  
  if(sigsuspend(&waitmask)!=-1)
    err_sys("sigsupend err");
  pr_mask("after return sigsuspend:");
  
  if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
    err_sys("sigsetmask err");
  
  pr_mask("pro exit:");
  exit(0);
}

static void sig_int(int signo){

  pr_mask("in sig_int:");

}
