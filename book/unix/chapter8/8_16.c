#include "../apue.h"
#include "../error.c"
//会计数据
int main(void){
  pid_t pid;
  
  printf("0pid=%d,0ppid=%d\n",getpid(),getppid());
  if((pid=fork())<0)
    err_sys("fork err");

  else if(pid>0){//self
    sleep(2);
    exit(2);
  }else{
    printf("1pid=%d,1ppid=%d\n",getpid(),getppid());
  }

  if((pid=fork())<0)
    err_sys("fork2 err");
  else if(pid!=0){
    sleep(4);
    abort();//with core
  }else{
  
  printf("2pid=%d,2ppid=%d\n",getpid(),getppid());
  }

  if((pid=fork())<0)
    err_sys("fork3 err");
  else if(pid!=0)
  {
    //ecl("/bin/dd","dd","if=/var/log/yum.log","of=/dev/null",NULL);
    //eep(4);
    exit(7);
  }else{
    printf("3pid=%d,3ppid=%d\n",getpid(),getppid());
  }

  if((pid=fork())<0)
    err_sys("fork4 err");
  else if(pid!=0){
    sleep(8);
    exit(0);
  }else{
    printf("4id=%d,4pid=%d\n",getpid(),getppid());
  }

  printf("vpid=%d,vppid=%d\n",getpid(),getppid());
  sleep(6);
  kill(getpid(),SIGKILL);
  exit(6);
}
