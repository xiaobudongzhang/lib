#include "../apue.h"
#include <errno.h>
#include <fcntl.h>
#include <termios.h>

int ptym_open(char *pts_name,int pts_namesz){
  char *ptr;
  int fdm,err;
  
  if((fdm=posix_openpt(O_RDWR))<0)
    return(-1);
  if(grantpt(fdm)<0)
    goto errout;
  if(unlockpt(fdm)<0)
    goto errout;
  if((ptr=ptsname(fdm))==NULL)
    goto errout;

  strncpy(pts_name,ptr,pts_namesz);
  pts_name[pts_namesz-1]='\0';
  return(fdm);
  
 errout:
  err=errno;
  close(fd);
  errno=err;
  return(-1);
}

int ptys_open(char *pts_name){
  int fds;
  
  if((fds=open(pts_name,O_RDWR)<0)
     return(-1);
     return(fds);
}

pid_t pty_fork(int *ptrfdm,char *slave_name,int slave_namez,const struct termios *slave_termios,const struct winsize *slave_winsize){
    int fdm,fds;
    pid_t pid;
    char pts_name[20];
    
    if((fdm=ptym_open(pts_name,sizeof(pts_name)))<0)
      err_sys("cant open master pty：%s,error %d",pts_name,fdm);
    
    if(slave_name!=NULL){
      strncpy(slave_name,pts_name,slave_namesz);
      slave_name[slave_namesz-1]='\0';
    }

    if((pid=(fork()))<0){
      return(-1);
    }else if(pid==0){
      if(setsid()<0)
	err_sys("setsid error");
      
      if((fds=ptys_open(pts_name))<0)
	err_sys("cant open slave pty");
      close(fdm);
      
      if(slave_termios!=NULL){
	if(tcsetattr(fds,TCSANOW,slave_termios)<0)
	  err_sys("tcsetattr error on slave pty");
      }

      
      if(slave_winsize!=NULL){
	if(ioctl(fds,TIOCSWINSZ,slave_winsize)<0)
	  err_sys("tiocswinsz error on slave pty");
      }
      
      if(dup2(fds,STDIN_FILENO)!=STDIN_FILENO)
	err_sys("dup2 error to stdin");
      if(dup2(fds,STDOUT_FILENO)!=STDIN_FILENO)
        err_sys("dup2 error to stdOUT");
      if(dup2(fds,STDERR_FILENO)!=STDIN_FILENO)
        close(fds);
      
      return(0);
    }else{
      *ptrfdm=fdm;
      return(pid);
    }
}


