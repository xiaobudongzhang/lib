#include "../apue.h"
#include "../error.c"

static void sig_pipe(int);
//协同进程
int main(void){
  int n,fd1[2],fd2[2];
  pid_t pid;
  char line[MAXLINE];
  
  if(signal(SIGPIPE,sig_pipe)==SIG_ERR)
    err_sys("signal err");
  
  if(pipe(fd1)<0||pipe(fd2)<0)
    err_sys("pipe err");
  
  if((pid=fork())<0){
    err_sys("pipe err");
  }else if(pid>0){
    close(fd1[0]);
    close(fd2[1]);
    //printf("parent start\n");
    while(fgets(line,MAXLINE,stdin)!=NULL){
     
      n=strlen(line);
      //printf("fgets:%s\n",line);
      if(write(fd1[1],line,n)!=n)
	err_sys("write err to pipe");
      //printf("parent write end \n");
      if((n=read(fd2[0],line,MAXLINE))<0)
	err_sys("read err from pipe");
      
      //printf("parent read end\n");
      if(n==0){
	err_msg("child closed pipe");
	break;
      }
    
      line[n]=0;
      if(fputs(line,stdout)==EOF)
	err_sys("fputs err");

      //printf("line---%s\n",line);
      //printf("fputs end\n");
    }
    if(ferror(stdin))
      err_sys("fgets err on stdin");
    //printf("parent end\n");
      exit(0);
      
  }else{
    //sleep(3);
    //printf("child start\n");
    close(fd1[1]);
    close(fd2[0]);
    if(fd1[0]!=STDIN_FILENO){
      if(dup2(fd1[0],STDIN_FILENO)!=STDIN_FILENO)
	err_sys("dup2 err");
      //printf("STDIN_FILENO\n");
      close(fd1[0]);
    }

    if(fd2[1]!=STDOUT_FILENO){
      if(dup2(fd2[1],STDOUT_FILENO)!=STDOUT_FILENO)
	err_sys("dup2 err 2");
      //printf("STDOUT_FILENO\n");
      close(fd2[1]);
    }
   
    //printf("child mid\n");
    //if(execl("/bin/awk","awk","-f","t",(char *)0)<0)
    if(execl("./add2",(char *)0)<0)  
    err_sys("execl err");
    //printf("child end");
  }
  exit(0);
}
static void sig_pipe(int signo){
  printf("sigpipe caught\n");
  exit(1);
}
