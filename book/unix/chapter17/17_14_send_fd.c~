#include "../apue.h"
#include <sys/socket.h>
#include <fcntl.h>

#define CONTROLLEN CMSG_LEN(sizeof(long))

//send_fd

static struct cmsghdr *cmptr=NULL;

int send_fd(int fd,int fd_to_send){

  struct iovec iov[1];
  struct msghdr msg;
  char buf[2];
  
  iov[0].iov_base=buf;
  iov[0].iov_len=2;
  
  msg.msg_iov=iov;
  msg.msg_iovlen=1;
  msg.msg_name=NULL;
  msg.msg_namelen=0;
  
  if(fd_to_send<0){
    msg.msg_control=NULL;
    msg.msg_controllen=0;
    buf[1]=-fd_to_send;
    if(buf[1]==0)
      buf[1]=1;
  }else{
    if(cmptr==NULL&&(cmptr=malloc(CONTROLLEN))==NULL)
      return(-1);
    
    cmptr->cmsg_level=SOL_SOCKET;
    cmptr->cmsg_type=SCM_RIGHTS;
    cmptr->cmsg_len=CONTROLLEN;
    
    msg.msg_control=cmptr;
    msg.msg_controllen=CONTROLLEN;
    
    int f=    open("tmp41",O_WRONLY|O_CREAT|O_TRUNC);
    char bc[23];
    sprintf(bc,"len %d",msg.msg_controllen);
    write(f,bc,strlen(bc));
   *(int *)CMSG_DATA(cmptr)=fd_to_send;
    
    buf[1]=0;
  }
  
  char bc2[23]; 
  int f2=    open("tmp522",O_WRONLY|O_CREAT|O_TRUNC);
  //sprintf(bc2,"len %d",msg.msg_controllen);
  //write(f2,bc2,strlen(bc2));

  buf[0]=0;
  if(sendmsg(fd,&msg,0)!=2)
    return(-1);

  sprintf(bc2,"len %d",msg.msg_controllen);
  write(f2,bc2,strlen(bc2));
  return(0);
}
