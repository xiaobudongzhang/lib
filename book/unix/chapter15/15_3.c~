#include "../apue.h"
#include <sys/wait.h>
#include "../error.c"

#define DEF_PAGER "/bin/more"
#define MAXLINE 4096
int main(int argc,char *argv[]){
  int n;
  int fd[2];
  pid_t pid;
  char *pager,*argv0;
  char line[MAXLINE];
  FILE *fp;
  
  if(argc!=2)
    err_sys("Usage:");
  
  if((fp=fopen(argv[1],"rb"))==NULL)
    err_sys("cant open %s",argv[1]);
  if(pipe(fd)<0)
    err_sys("pipe err");
  
  if((pid=fork())<0){
    err_sys("fork err");
  }else if(pid>0){
    close(fd[0]);
    
    while(fgets(line,MAXLINE,fp)!=NULL){
      n=strlen(line);
      if(write(fd[1],line,n)!=n)
	err_sys("write err");
    }
    if(ferror(fp))
      err_sys("fgets err");
    close(fd[1]);
    if(waitpid(pid,NULL,0)<0)
      err_sys("wait pid err");
    exit(0);
  }else{
    close(fd[1]);
    if(fd[0]!=STDIN_FILENO){
      if(dup2(fd[0],STDIN_FILENO)!=STDIN_FILENO)
	err_sys("dup2 errr");
      close(fd[0]);
    }

    if((pager=getenv("PAGER"))==NULL)
      {      pager=DEF_PAGER;
	printf("page %s\n",pager);
      }
    else
      printf("pager\n");

    if((argv0=strrchr(pager,'/'))!=NULL)
      argv0++;
      else
	argv0=pager;
    
  
    if(execl(pager,argv0,(char *)0)<0)
       err_sys("execl err for %s",pager);
  }
  exit(0);
}
