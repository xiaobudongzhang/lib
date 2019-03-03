#include "../apue.h"
#include "../error.c"
//exec函数case
char *env_init[]={"USER=unknown","PATH=/tmp",NULL};

int main(void){
  pid_t  pid;
  
  if((pid=fork())<0){
    err_sys("fork err");
  }else if(pid==0){
    if(execle("./echoall","echoall","myarg1","MY_ARG2",(char *)0,env_init)<0)
      err_sys("execel error");
  }

  if(waitpid(pid,NULL,0)<0)
    err_sys("wait err");

  if((pid=fork())<0){
    err_sys("fork err");
  }else if(pid==0){
    if(execlp("echoall","echoall","only 1 arg",(char *)0)<0)
      err_sys("execlp err");
  }

  exit(0);
}
