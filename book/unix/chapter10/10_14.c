#include "../apue.h"
#include "../error.c"
#include <setjmp.h>
#include <time.h>
#include "10_10.c"

//信号屏蔽字与sigsetjmp siglongjmp
static void sig_usr1(int),sig_alrm(int);
Sigfunc *signal3(int signo,Sigfunc *func);

static sigjmp_buf jmpbuf;
static volatile sig_atomic_t canjump;
static int xyz;
int main(void){
  if(signal3(SIGUSR1,sig_usr1)==SIG_ERR)
    err_sys("sig usr1 err");
  if(signal3(SIGALRM,sig_alrm)==SIG_ERR)
    err_sys("sig alrm err");
  
  pr_mask("starting main:");
  
  xyz=sigsetjmp(jmpbuf,1);
  printf("xyz=%d\n",xyz);
  if(xyz){
    pr_mask("ending main:");
    exit(0);
  }

  canjump=1;
  for(;;)
    pause();
}

static void sig_usr1(int signo){
  
  time_t starttime;
  
  if(canjump==0)
    return;

  pr_mask("starting sig_usr1:");
  alarm(3);
  starttime=time(NULL);
  
  for(;;)
    if(time(NULL)>starttime+5)
      break;

  pr_mask("finish usr1:");
  
  canjump=0;
  siglongjmp(jmpbuf,1);

}

static void sig_alrm(int signo){
  pr_mask("in sig_alrm:");
  return;
}
Sigfunc *signal3(int signo,Sigfunc *func){

  struct sigaction act,oact;

  act.sa_handler = func;
  sigemptyset(&act.sa_mask);
  act.sa_flags=0;

  if(signo==SIGALRM){
#ifdef SA_INTERRUPT
    act.sa_flags|=SA_INTERRUPT;
#endif
  }else{
#ifdef SA_RESTART
    act.sa_flags|=SA_RESTART;
#endif
  }

  if(sigaction(signo,&act,&oact)<0)
    return (SIG_ERR);

  return (oact.sa_handler);
}
