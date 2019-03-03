#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sig_abrt(int);
//pos.1 abort
void abort3(void){
  sigset_t mask;
  struct sigaction action;
  
  //cant ignore SIGABRT
  printf("sig_ign\n");
  sigaction(SIGABRT,NULL,&action);
  if(action.sa_handler==SIG_IGN){
    action.sa_handler=SIG_DFL;
    sigaction(SIGABRT,&action,NULL);
  }

  if(action.sa_handler==SIG_DFL)
    fflush(NULL);
  
  //cant block SIGABRT
  printf("abr_bort\n");
  sigfillset(&mask);
  sigdelset(&mask,SIGABRT);//turn off SIGABRT  阻塞除SIGABRT外的信号
  sigprocmask(SIG_SETMASK,&mask,NULL);
  kill(getpid(),SIGABRT);

  //abrt action return
  printf("abr_last\n");
  fflush(NULL);
  action.sa_handler=SIG_DFL;
  sigaction(SIGABRT,&action,NULL);
  sigprocmask(SIG_SETMASK,&mask,NULL);
  kill(getpid(),SIGABRT);
  
  printf("should not reach here\n");
  exit(1);
}


int main(void){
  printf("abort before\n");
  
  signal(SIGABRT,sig_abrt);
  abort3();
  printf("abort after\n");
  //_exit(0);
  exit(0);
}

void sig_abrt(int signo){
  printf("in sig_abrt\n");
  //_exit(0);
}
