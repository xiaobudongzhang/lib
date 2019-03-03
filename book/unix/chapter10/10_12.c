#include "../apue.h"
#include "../error.c"

//signal 实现

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



static void sig_int(int);
  


int main(void){
  if(signal3(SIGINT,sig_int)==SIG_ERR){
    printf("sig err");
  }
  sleep(10);
  return(0);
}


static void sig_int(int signo){
  printf("sig_int\n");
  
}

