#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include "../error.c"
//模拟system
int system2(const char *cmdstr){
  pid_t pid;
  int status;
  
  if(cmdstr==NULL)
    return (1);

  if((pid=fork())<0){
    status=-1;
  }else if(pid==0){
    execl("/bin/sh","shss","-c",cmdstr,(char *)0);
    _exit(127);
  }else{
    while(waitpid(pid,&status,0)<0){
      if(errno!=EINTR){
	status=-1;
	break;
      }
    }
  }

  return status;
}



int main(void){
  int status;
  
  if((status=system2("ls"))<0){
    err_sys("sys err");
  }
  return (0);
}
