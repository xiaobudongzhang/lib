#include "../apue.h"
#include <pthread.h>
#include "../error.c"
#include "../lib/function.c"
#include <sys/resource.h>
#include "../lib/lockfile.c"

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
  struct sigaction sa;

  daemonize("ls");
  if(already_runing()){
    syslog(LOG_ERR,"daemon already running");
    exit(1);
  }
  
  sa.sa_handler=SIG_DFL;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags=0;
  if(sigaction(SIGHUP,&sa,NULL)<0){
    err_quit("%s:cant restore SIGHUP default");
  }
  sigfillset(&mask);
  if((err=pthread_sigmask(SIG_BLOCK,&mask,&oldmask))!=0){
    err_exit(err,"sigblock err");
  }

  err=pthread_create(&tid,NULL,thr_fn,0);
  if(err!=0)
    err_exit(err,"create fail");
  pause();
  exit(0);
}
