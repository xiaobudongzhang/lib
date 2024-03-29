#include "../apue.h"
//#include "../error.c"
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

#define QLEN 10

//serve_listen

int serv_listen(const char *name){
  int fd,len,err,rval;
  struct sockaddr_un un;
  
  if(strlen(name)>=sizeof(un.sun_path)){
    errno=ENAMETOOLONG;
    return(-1);
  }
  
  if((fd=socket(AF_UNIX,SOCK_STREAM,0))<0)
    return(-2);
  
  unlink(name);
  
  memset(&un,0,sizeof(un));
  un.sun_family=AF_UNIX;
  strcpy(un.sun_path,name);
  len=offsetof(struct sockaddr_un,sun_path)+strlen(name);
  
  if(bind(fd,(struct sockaddr *)&un,len)<0){
    rval=-3;
    goto errout;
  }
  
  if(listen(fd,QLEN)<0){
    //log_msg("test36");
    rval=-4;
    goto errout;
  }
  return(fd);
 errout:
  err=errno;
  close(fd);
  errno=err;
  return(rval);
}


