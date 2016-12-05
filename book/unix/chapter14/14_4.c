#include "../apue.h"
#include "../error.c"
#include <fcntl.h>
//父子进程同步
static volatile sig_atomic_t sigflag;
static sigset_t newmask,oldmask,zeromask;
#define LOCKMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

Sigfunc *signal3(int signo,Sigfunc *func);

int
lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
  struct flock lock;

  lock.l_type = type;/* F_RDLCK, F_WRLCK, F_UNLCK */
  lock.l_start = offset;/* byte offset, relative to l_whence */
  lock.l_whence = whence;/* SEEK_SET, SEEK_CUR, SEEK_END */
  lock.l_len = len;/* #bytes (0 means to EOF) */

  return( fcntl(fd, cmd, &lock) );
}



static void sig_usr(int signo){
  printf("sig_usr\n");
  sigflag=1;
  return;
}

static void lockabyte(const char *name,int fd,off_t offset){
  printf("in lockabyte\n");
  if(read_lock(fd,offset,SEEK_SET,1)<0)
    err_sys("%s:writew_lock err",name);
  
  printf("%s:got the lock,byte %ld\n",name,offset);
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


int main(void){
  int fd;
  pid_t pid;

  if((fd=open("templock",O_RDWR|O_CREAT|O_TRUNC))<0)
    err_sys("create err");

  if(write(fd,"abcdef",6)!=6)
    err_sys("write err");

  //TELL_WAIT();

  if((pid=fork())<0){
    err_sys("fork err");
  }else if(pid==0){
    printf("child pid\n");
    lockabyte("child",fd,0);
    //WAIT_PARENT();
    //TELL_PARENT(getpid());
    //WAIT_PARENT();
    //lockabyte("child",fd,1);
    printf("child err\n");
    //chartime("output from child\n");
  }else{
    printf("parent pid\n");
    //sleep(5);
    //chartime("output from parent\n");
    lockabyte("parent",fd,2);
    // TELL_CHILD(pid);
    //   WAIT_CHILD();
    //lockabyte("child",fd,0);
    printf("parent err\n");
  }
  exit(0);
}


