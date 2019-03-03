#include "../apue.h"
#include "../error.c"
#include <sys/wait.h>

static void sig_cld(int);

int main(){
  pid_t pid;
  
  if(signal(SIGCLD,sig_cld)==SIG_ERR)
    perror("sig err");

  if((pid=fork())<0){
    perror("fork err");
  }else if(pid==0){
    sleep(2);
    _exit(0);
  }
  pause();
  exit(0);
}

static void sig_cld(int signo){

  pid_t pid;
  int status;
  
  printf("sigcld rev\n");
  if(signal(SIGCLD,sig_cld)==SIG_ERR)
    perror("sig err");
  if((pid=wait(&status))<0)
    perror("wait err");

  printf("pid=%d\n",pid);

}
