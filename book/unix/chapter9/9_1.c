#include "../apue.h"
#include "../error.c"
#include <errno.h>
//孤儿进程组

static void sig_hup(int signo){

  printf("sighub rev,pid=%d\n",getpid());

}

static void pr_ids(char *name){

  printf("%s:pid=%d,ppid=%d,pgrp=%d,tpgrp=%d\n",name,getpid(),getppid(),getpgrp(),tcgetpgrp(STDIN_FILENO));
  fflush(stdout);
}

int main(void){
  char c;
  pid_t pid;
  
  pr_ids("parent");
  
  if((pid=fork())<0){
    err_sys("fork err");
  }else if(pid>0){
    sleep(2);
    exit(0);
  }else{
    pr_ids("child");
    signal(SIGHUP,sig_hup);
    kill(getpid(),SIGTSTP);//stop self
    pr_ids("child con");
    if(read(STDIN_FILENO,&c,1)!=1){
      printf("read err from tty,errno=%d\n",errno);
    }
    exit(0);
  }

}
