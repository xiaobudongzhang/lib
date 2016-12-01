#include "../apue.h"
#include <pthread.h>
#include "../error.c"

int quitflag;
sigset_t mask;

pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t wait=PTHREAD_COND_INITIALIZER;

void *thr_fn(void *arg){
  int err,signo;
  
  printf("xcid=%d\n",pthread_self());
  for(;;){
    err=sigwait(&mask,&signo);
    if(err!=0)
      err_exit(err,"sigwait failed");
    switch(signo){
    case SIGINT:
      printf("\ninter\n");
      break;
    case SIGQUIT:
      pthread_mutex_lock(&lock);
      quitflag=1;
      printf("sigquit\n");
      pthread_mutex_unlock(&lock);
      pthread_cond_signal(&wait);
      return(0);
    default:
      printf("unexcepected%d\n",signo);
      exit(1);
    }
  }
}


int main(void){
  int err;
  sigset_t oldmask;
  pthread_t tid;
  
  sigemptyset(&mask);
  sigaddset(&mask,SIGINT);
  sigaddset(&mask,SIGQUIT);
  
  if((err=pthread_sigmask(SIG_BLOCK,&mask,&oldmask))!=0){
    err_exit(err,"sigblock err");
  }

  err=pthread_create(&tid,NULL,thr_fn,0);
  if(err!=0)
    err_exit(err,"create fail");
  
  pthread_mutex_lock(&lock);
  printf("testxcid=%d\n",pthread_self());
  while(quitflag==0){
    printf("ddd\n");
    pthread_cond_wait(&wait,&lock);
  }
  pthread_mutex_unlock(&lock); 
  quitflag=0;

  printf("pxcid=%d\n",pthread_self());
  if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
    err_sys("sig_setmask err");
  exit(0);
}
