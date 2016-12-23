#include "open.h"
#include "../error.c"
#include <errno.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include "./17_10_cli_conn.c"
//csopen2
int csopen2(char *name,int oflag){
  pid_t pid;
  int len;
  char buf[10];
  struct iovec iov[3];
  static int csfd=-1;
  
  
  if(csfd<0){
    if((csfd=cli_conn(CS_OPEN))<0)
      {
	printf("csfd %d:",csfd);
	err_sys("cli_conn err");
      }
  }

  sprintf(buf," %d",oflag);
  iov[0].iov_base=CL_OPEN " ";
  iov[0].iov_len=strlen(CL_OPEN)+1;
  iov[1].iov_base=name;
  iov[1].iov_len=strlen(name);
  iov[2].iov_base=buf;
  iov[2].iov_len=strlen(buf)+1;
  
  len=iov[0].iov_len+iov[1].iov_len+iov[2].iov_len;
  if(writev(csfd,&iov[0],3)!=len)
    err_sys("write error");

  return(recv_fd(csfd,write));
}
