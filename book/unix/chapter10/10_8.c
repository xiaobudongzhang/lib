#include "../apue.h"
#include "../error.c"
#include <setjmp.h>

static void sig_alrm(int);
static jmp_buf env_alrm;

int main(void){
  
  int n;
  char line[MAXLINE];
  
  if(signal(SIGALRM,sig_alrm)==SIG_ERR)
    err_sys("signal sigalm error");
  
  if(setjmp(env_alrm)!=0)
    err_quit("read timeout");
  
  alarm(2);
  sleep(6);
  if((n=read(STDIN_FILENO,line,MAXLINE))<0)
    err_sys("read err");
  
  alarm(0);
  
  write(STDOUT_FILENO,line,n);
  exit(0);
  
}


static void sig_alrm(int signo){
  printf("sig_alrm\n");
  longjmp(env_alrm,1);
}

