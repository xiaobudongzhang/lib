#include "../apue.h"
#include "../error.c"
#include <sys/wait.h>
//打印进程status
void pr_exit(int status){
  if(WIFEXITED(status))
    printf("exit,status=%d\n",WEXITSTATUS(status));

  else if(WIFSIGNALED(status))
    printf("abort,sig number=%d%s\n",WTERMSIG(status),
#ifdef WCOREDUMP
	   WCOREDUMP(status)?"core file":"")
#else
      "");
#endif
 else if(WIFSTOPPED(status))
   printf("child stop,sig number=%d\n",WSTOPSIG(status));

}


int main(void){
  pid_t pid;
  int status;
  
  if((pid=fork())<0)
    err_sys("fork err");
  else if(pid==0){
    sleep(5);
   exit(7);
    //sleep(5);
  }
 
  if(wait(&status)!=pid)
    err_sys("wait err");
  pr_exit(status);
  //
  if((pid=fork())<0){
    err_sys("fork err2");
  }
  else if(pid==0)
  {
    abort();
  }
  
  if(wait(&status)!=pid)
    err_sys("wait error");
  pr_exit(status);
  
  exit(0);
}
