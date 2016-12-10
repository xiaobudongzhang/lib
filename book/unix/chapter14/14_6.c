#include "../apue.h"
#include "../error.c"
#include <fcntl.h>
//测试是否是记录锁
static volatile sig_atomic_t sigflag;
static sigset_t newmask,oldmask,zeromask;
#define LOCKMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) 

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
  printf("in sig_usr pid=%d\n",getpid());
  sigflag=1;
  return;
}

static void lockabyte(const char *name,int fd,off_t offset){
  printf("in lockabyte\n");
  if(writew_lock(fd,offset,SEEK_SET,1)<0)
    err_sys("%s:writew_lock err",name);
  
  printf("%s:got the lock,byte %ld\n",name,offset);
}

void TELL_WAIT(void){
  printf("in tell_wait\n");
  if(signal(SIGUSR1,sig_usr)==SIG_ERR)
    err_sys("sig usr1 err");
  if(signal(SIGUSR2,sig_usr)==SIG_ERR)
    err_sys("sig usr2 err");
  sigemptyset(&zeromask);
  sigemptyset(&newmask);
  sigaddset(&newmask,SIGUSR1);
  sigaddset(&newmask,SIGUSR2);
  
  if(sigprocmask(SIG_BLOCK,&newmask,&oldmask)<0)
    err_sys("sig_block err");

  
}

void TELL_PARENT(pid_t pid){
  printf("in tell_parent\n");
  kill(pid,SIGUSR2);
}

void WAIT_PARENT(void){
  printf("in wait_parent\n");
  while(sigflag==0)
       sigsuspend(&zeromask);
  sigflag=0;
  printf("wait pp\n");
  if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
    err_sys("sig_setmask err");
}

void TELL_CHILD(pid_t pid){
  printf("in tell_child\n");
  kill(pid,SIGUSR1);
}

void WAIT_CHILD(void){
  printf("in wait_child\n");
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
void set_f1(int fd,int flags){
  int val;

  if((val=fcntl(fd,F_GETFL,0))<0){
    err_sys("fcntl error");
  }

  val |=flags;

  if(fcntl(fd,F_SETFL,val)<0){
    err_sys("fcntl set error");
  }
}

int main(int argc,char *argv[]){
  int fd;
  pid_t pid;
  char buf[5];
  struct stat statbuf;
  
  if(argc!=2){
    fprintf(stderr,"usage:%s filename\n",argv[0]);
    exit(1);
  }
    
  if((fd=open(argv[1],O_RDWR|O_CREAT|O_TRUNC,FILE_MODE))<0)
    err_sys("create err");

  if(write(fd,"abcdef",6)!=6)
    err_sys("write err");

  if(fstat(fd,&statbuf)<0)
    err_sys("fstat error");
  //设置记录锁
  if(fchmod(fd,(statbuf.st_mode&~S_IXGRP)|S_ISGID)<0)
    err_sys("fchmod err");
  TELL_WAIT();

  if((pid=fork())<0){
    err_sys("fork err");
  }else if(pid==0){
    printf("child begin pid=%d\n",getpid());
    WAIT_PARENT();
    //set_f1(fd,O_NONBLOCK);
    if(read_lock(fd,0,SEEK_SET,0)!=-1)
      err_sys("child:read lock suss");
    printf("read_lock locked,err:%d\n",errno);
    int len;
    if(lseek(fd,0,SEEK_SET)==-1)
      err_sys("lseek err");
    if((len=read(fd,buf,3))==-1)
	{err_ret("read fail");
	  //	  exit(0);
	}
      else{
	err_ret("read ok ,length=%d,buf=%5.5s\n",len,buf);
	//exit(0);
      }
    //TELL_PARENT(getpid());
    printf("child end\n");
  }else{
    sleep(5);
    printf("parent begin\n");
    if(write_lock(fd,0,SEEK_SET,0)<0)
      err_sys("write_lock err");
    //sleep(100);
    TELL_CHILD(pid);
    // WAIT_CHILD();
     if(waitpid(pid,NULL,0)<0)
       err_sys("waitpid err");
    printf("parent end\n");
  }
  exit(0);
}


