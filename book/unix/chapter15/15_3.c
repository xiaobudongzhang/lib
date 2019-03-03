#include "../apue.h"
#include <sys/wait.h>
#include "../error.c"

#define PAGER "${PAGER:-/bin/more}"
#define MAXLINE 4096
int main(int argc,char *argv[]){
  int n;
  int fd[2];
  pid_t pid;
  char *pager,*argv0;
  char line[MAXLINE];
  FILE *fpin,*fpout;
  
  if(argc!=2)
    err_sys("Usage:");
  
  if((fpin=fopen(argv[1],"rb"))==NULL)
    err_sys("cant open %s",argv[1]);

  
  if((fpout=popen(PAGER,"w"))==NULL)
    err_sys("popen err");
  
  while(fgets(line,MAXLINE,fpin)!=NULL){
    if(fputs(line,fpout)==EOF)
      err_sys("fputs err to pip");
  }

  if(ferror(fpin))
    err_sys("fgets err");
  if(pclose(fpout)==-1)
    err_sys("pclose err");
    
 
  exit(0);
}
