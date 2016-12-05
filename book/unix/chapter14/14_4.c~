#include "../apue.h"
#include "../error.c"
//父子进程同步
static volatile sig_atomic_t sigflag;
static sigset_t newmask,oldmask,zeromask;
Sigfunc *signal3(int signo,Sigfunc *func);



static void sig_usr(int  signo){
  sigflag=1;
}

void TELL_WAIT(void){
  
  if(signal3(SIGUSR1,sig_usr)==SIG_ERR)
    err_sys("sig usr1 err");
  if(signal3(SIGUSR2,sig_usr)==SIG_ERR)
    err_sys("sig usr2 err");
  sigemptyset(&zeromask);
  sigemptyset(&newmask);
  sigaddset(&newmask,SIGUSR1);
  sigaddset(&newmask,SIGUSR2);
  
  if(sigprocmask(SIG_BLOCK,&newmask,&oldmask)<0)
    err_sys("sig_block err");

  
}

void TELL_PARENT(pid_t pid){
  kill(pid,SIGUSR2);
}

void WAIT_PARENT(void){
  while(sigflag==0)
       sigsuspend(&zeromask);
  sigflag=0;
  printf("wait pp\n");
  if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
    err_sys("sig_setmask err");
}

void TELL_CHILD(pid_t pid){
  kill(pid,SIGUSR1);
}

void WAIT_CHILD(void){
  while(sigflag==0)
    sigsuspend(&zeromask);
  sigflag=0;

  if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
    err_sys("sig_setmask err");
}

Sigfunc *signal3(int signo,Sigfunc *func){
  //printf("signal3\n");
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
  
  //printf("sig_flag=%o\n", act.sa_flags);
  if(sigaction(signo,&act,&oact)<0)
    return (SIG_ERR);

  return (oact.sa_handler);
}
static void chartime(char *);

int main(void){
  pid_t pid;

    TELL_WAIT();

  if((pid=fork())<0){
    err_sys("fork err");
  }else if(pid==0){
    WAIT_PARENT();
    //TELL_PARENT(getpid());
    chartime("output from child\n");
  }else{
    sleep(5);
    chartime("output from parent\n");
    TELL_CHILD(pid);
    // WAIT_CHILD();
  }
  exit(0);
}

static void chartime(char *str){

  char *ptr;
  int c;

  setbuf(stdout,NULL);//no buffer
  for(ptr=str;(c=*ptr++)!=0;)
    putc(c,stdout);
}
