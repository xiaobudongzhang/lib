#include "../apue.h"
#include "../error.c"

static void sig_quit(int);

int main(void){

  sigset_t newmask,oldmask,pendmask;
  
  if(signal(SIGQUIT,sig_quit)==SIG_ERR)
    err_sys("cant catch qigquit");
  
  sigemptyset(&newmask);
  sigaddset(&newmask,SIGQUIT);

  if(sigprocmask(SIG_BLOCK,&newmask,&oldmask)<0)
    err_sys("sig_block err");

  sleep(5);
  
  if(sigpending(&pendmask)<0)
    err_sys("sigpending err");
  if(sigismember(&pendmask,SIGQUIT))
    printf("\nsigquit pending\n");
  
  if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
    err_sys("sig_setmask err");
  
  printf("sigquit unblocked\n");

  sleep(5);
  exit(0);
}


static void sig_quit(int signo){
  
  printf("caught sigquit\n");
  if(signal(SIGQUIT,SIG_DFL)==SIG_ERR)
    err_sys("cant reset sigquit");

}
