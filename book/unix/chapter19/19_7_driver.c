#include "../apue.h"
#include<sys/types.h>
#include<sys/socket.h>
#include <stdio.h>

int s_pipe(int fd[2]) 
{
  return( socketpair(AF_UNIX, SOCK_STREAM, 0, fd) );
}


void  do_driver(char *driver){//@todo byz
  pid_t child;
  int pipe[2];
  int saveout=dup(STDOUT_FILENO);

  if(s_pipe(pipe)<0)
    err_sys("cant create stream pipe");
  
  if((child=fork())<0){
    err_sys("fork error");
  }else if(child==0){
    close(pipe[1]);
    
    printf("in child\n");
    if(dup2(pipe[0],STDIN_FILENO)!=STDIN_FILENO)
      err_sys("dup2 err in stdin");
    
    if(dup2(pipe[0],STDOUT_FILENO)!=STDOUT_FILENO)
      err_sys("dup2 err in stdout");
    
    
        if(pipe[0]!=STDIN_FILENO&&pipe[0]!=STDOUT_FILENO)
    {
      // open("ttt33", O_WRONLY| O_CREAT|O_TRUNC);
      //	printf("in   \n");
	close(pipe[0]);
    }

    open("ttt", O_WRONLY| O_CREAT|O_TRUNC);
    printf("%s driver\n",driver);
    if(execlp(driver,driver,(char *)0)<0)
      {
	err_sys("execlp err");
	open("ttt42", O_WRONLY| O_CREAT|O_TRUNC);
      }else{
      //char *c="hello";
      //write(pipe[0],c,strlen(c));
    }
   err_sys("execlp error for:%s",driver);
  }

  printf("in parent\n");

  close(pipe[0]);
  if(dup2(pipe[1],STDIN_FILENO)!=STDIN_FILENO)
     err_sys("dup2 err in stdin");
  if(dup2(pipe[1],STDOUT_FILENO)!=STDOUT_FILENO)
    err_sys("dup2 err in stdout");
  
  //int saveout=dup(STDOUT_FILENO);
  //dup2(saveout,pipe[1]);
  //fflush(stdout);
  char *buf[1024];
  int n;
  int dd=open("tmp", O_WRONLY);
  while ((n = read(pipe[1], buf, BUFFSIZE)) > 0)
      if (write(saveout      , buf, n) != n)
    err_sys("write error");
  
  if(pipe[1]!=STDIN_FILENO&&pipe[1]!=STDOUT_FILENO)
    {
      //open("ttt58", O_WRONLY| O_CREAT|O_TRUNC);
      close(pipe[1]);
    
    }
}
