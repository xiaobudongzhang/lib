#include "../apue.h"
#include "../error.c"
//超时case
static void sig_alrm(int);

int main(void){

  int n;
  char line[MAXLINE];
  
  if(signal(SIGALRM,sig_alrm)==SIG_ERR)
    err_sys("sig alrm err");

  alarm(5);
  sleep(8);
  
  if((n=read(STDIN_FILENO,line,MAXLINE))<0)
    err_sys("read err");
  
  alarm(0);
  
  write(STDIN_FILENO,line,n);
  exit(0);
}

static void sig_alrm(int signo){
  printf("sig_alrm\n");

}
