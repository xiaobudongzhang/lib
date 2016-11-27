#include "../apue.h"
#include "../error.c"
#include <sys/wait.h>
//调用两次fork 避免僵死进程
int main(void){
  pid_t pid;
  
  if((pid=fork())<0){
    err_sys("fork err");
  }else if(pid==0){
    if((pid=fork())<0){
      err_sys("fork 2 error");
    }else if(pid>0){
      printf("first_pid=%d\n",getpid());
      //sleep(3);
      exit(0);
    }
    sleep(2);
    printf("second child,parent id=%d,pid=%d\n",getpid(),getppid());
    exit(0);
  }

  if(waitpid(pid,NULL,0)!=pid)
    err_sys("waitpid err");
  printf("last_pid=%d\n",pid);
  exit(0);
 
}
