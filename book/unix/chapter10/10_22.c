#include "../apue.h"
#include "../error.c"
#include "../lib/signal3.c"
//作业控制信号   先做自己的事，然后继续停止,如果继续则继续监听重复
#define BUFFSIZE 1024

static void sig_tstp(int);

int main(void){
  
  int n;
  char buf[BUFFSIZE];
  
  //only catch SIGTSTP with job_control shell
  if(signal3(SIGTSTP,SIG_IGN)==SIG_DFL)
  {
    printf("sig\n");
    signal3(SIGTSTP,sig_tstp);
  }
  
  while((n=read(STDIN_FILENO,buf,BUFFSIZE))>0)
    if(write(STDOUT_FILENO,buf,n)!=n)
      err_sys("write err");

  if(n<0)
    err_sys("read err");

  printf("\nexit\n");
  exit(0);
}

static void sig_tstp(int signo){
  printf("\nin sig_tstp\n");
  
  sigset_t mask;
  
  //停止前的操作
  sigemptyset(&mask);
  sigaddset(&mask,SIGTSTP);
  sigprocmask(SIG_UNBLOCK,&mask,NULL);
  
  signal3(SIGTSTP,SIG_DFL);
  kill(getpid(),SIGTSTP);

  printf("mid sig_tstp\n");
  signal3(SIGTSTP,sig_tstp);
  printf("sig_tstp end\n");
  //停止后操作
}
