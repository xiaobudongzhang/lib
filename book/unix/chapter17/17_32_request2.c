//#include "opend2.h"
#include "17_14_send_fd.c"
#include "17_24_cli_args2.c"
#include <fcntl.h>
#include "send_err.c"

void request(char *buf,int nread,int clifd,uid_t uid){
  int newfd;
  if(buf[nread-1]!=0){//不是null结尾的话
    sprintf(errmsg,"request not null terminated:%*.*s\n",nread,nread,buf);
    send_err(clifd,-1,errmsg);
    return;
  }
 
  log_msg("request :%s,from uid %d",buf,uid);
  if(buf_args(buf,cli_args)<0){
      send_err(clifd,-1,errmsg);
      log_msg(errmsg);
    return;
  }
  log_msg("request 21");
  if((newfd=open(pathname,oflag))<0){
    sprintf(errmsg,"cant open  %s:%s\n",pathname,strerror(errno));
    send_err(clifd,-1,errmsg);
    log_msg(errmsg);
    return;
  }
  log_msg("request 28 newfd %d",newfd);
  if(send_fd(clifd,newfd)<0)
    log_sys("send_fd error");
  log_msg("request 31");
  log_msg("sent fd %d over fd %d for %s",newfd,clifd,pathname);
  close(newfd);
}

