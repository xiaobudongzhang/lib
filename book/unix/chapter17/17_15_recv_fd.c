#include "../apue.h"
#include <sys/socket.h>

#define CONTROLLEN CMSG_LEN(sizeof(long))

static struct cmsghdr *cmptr=NULL;

//recv_fd

int  recv_fd(int fd,ssize_t(*userfunc)(int,const void *,size_t)){
  //printf("%d contr2\n",CONTROLLEN);
  int newfd,nr,status;
  char *ptr;
  char buf[MAXLINE];
  struct iovec iov[1];
  struct msghdr msg;
  
  status=-1;
  for(;;){
    iov[0].iov_base=buf;
    iov[0].iov_len=sizeof(buf);
    msg.msg_iov=iov;
    msg.msg_iovlen=1;
    msg.msg_name=NULL;
    msg.msg_namelen=0;
    
    if(cmptr==NULL&&(cmptr=malloc(CONTROLLEN))==NULL)
      return(-1);
    
    msg.msg_control=cmptr;
    msg.msg_controllen=CONTROLLEN;
   
    //printf("%d contr32\n",msg.msg_controllen);
    if((nr=recvmsg(fd,&msg,0))<0){
      printf("recv error:%d\n",nr);
      err_ret("resvmsg err");
      return(-1);
    }else if(nr==0){
      printf("recv error 0\n");
      err_ret("connection closed by server");
      return(-1);
    }

    //    printf("%d %d contr42\n",CONTROLLEN,msg.msg_controllen);
    
       for(ptr=buf;ptr<&buf[nr];){


	 if(*ptr++==0){//最后一个字节 null
	   //倒数第二个  status
	  
       if(ptr!=&buf[nr-1])
	  err_dump("message format err");
	
	status=*ptr&0xFF;
	if(status==0){
	  if(msg.msg_controllen!=CONTROLLEN)
	    {
	      //	      printf("%d contr54\n",msg.msg_controllen);
	      err_dump("status=0 but no fd");
	    }
	  newfd=*(int *)CMSG_DATA(cmptr);
	}else{
	  newfd=-status;
	}
      
	nr-=2;
      }
    }

   if(nr>0&&(*userfunc)(STDERR_FILENO,buf,nr)!=nr)
    return(-1);
   
    if(status>=0)
      return(newfd);
  }

}
