#include "../apue.h"
#include "../error.c"
#include <sys/wait.h>
//解释器文件实例
int main(void){

  pid_t pid;
  if((pid=fork())<0){
    err_sys("fork err");
  }else if(pid==0){
    if(execlp("echo2","test","myarg1","arg2",(char*)0)<0){
      err_sys("exec error");
    }
  }
  
  if(waitpid(pid,NULL,0)<0){
    err_sys("wait error");
  }
  
  exit(0);

}
