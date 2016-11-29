#include "../apue.h"
#include "../error.c"


Sigfunc *signal3(int signo,Sigfunc *func);



volatile sig_atomic_t quitflag;

static void sig_int(int signo){
  
  printf("in sig_int\n");
  if(signo==SIGINT)
    printf("\ninterrrupt\n");
  else if(signo==SIGQUIT)
    {  
      printf("quit\n");
      quitflag=1;
    }
}


int main(void){
  
  sigset_t newmask,oldmask,zeromask;
  
   if(signal3(SIGINT,sig_int)==SIG_ERR)
     err_sys("sig int err");
   if(signal3(SIGQUIT,sig_int)==SIG_ERR)
    err_sys("sig quit err");
  
  sigemptyset(&zeromask);
  sigemptyset(&newmask);
  sigaddset(&newmask,SIGQUIT);
  //sleep(5);
  if(sigprocmask(SIG_BLOCK,&newmask,&oldmask)<0)
    err_sys("sig_block err");

  
  while(quitflag==0){
    printf("quit flag=%d\n",quitflag);
    sigsuspend(&zeromask);
    printf("quit flag end\n");
  }
  
  //sleep(5);
  quitflag=0;

  //printf("end\n");
  
  //if(signal(SIGQUIT,sig_int)==SIG_ERR)
  //     err_sys("sig int err");

  if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
     err_sys("sig_setmask err");
  
  //printf("end2\n");
  

  exit(0);
}

Sigfunc *signal3(int signo,Sigfunc *func){
  printf("signal3\n");
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
    printf("restart\n");
    act.sa_flags|=SA_RESTART;
#endif
  }
  
     printf("sig_flag=%x\n", act.sa_flags);
  if(sigaction(signo,&act,&oact)<0)
    return (SIG_ERR);

  return (oact.sa_handler);
}
