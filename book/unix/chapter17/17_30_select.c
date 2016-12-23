//#include "opend2.h"
#include "17_8_serve_listen.c"
#include "17_9_serve_accept.c"
#include <sys/time.h>
#include <sys/select.h>
#include "mutl_2.c"
#include "17_32_request2.c"

void loop(void){
  
  int i,n,maxfd,maxi,listenfd,clifd,nread;
  char buf[MAXLINE];
  uid_t uid;
  fd_set rset,allset;
  
  FD_ZERO(&allset);

  if((listenfd=serv_listen(CS_OPEN))<0){
    log_sys("server__listen error");
  }

  FD_SET(listenfd,&allset);
  maxfd=listenfd;
  maxi=-1;
  
  for(;;){
    rset=allset;
    if((n=select(maxfd+1,&rset,NULL,NULL,NULL))<1)//包含超时
      log_sys("select error");
    
    if(FD_ISSET(listenfd,&rset)){
      if((clifd=serv_accept(listenfd,&uid))<0)
	log_sys("serv_acceot2 error:%d",clifd);
      
      i=client_add(clifd,uid);  
      FD_SET(clifd,&allset);
      
      if(clifd>maxfd)
	maxfd=clifd;
      if(i>maxi)
	maxi=i;
      
      log_msg("new connection2:uid %d,fd %d,maxi %d",uid,clifd,maxi);
      //printf("new conn\n");
      continue;
    }

    for(i=0;i<=maxi;i++){//等于号不要忘
      log_msg("maxi48");
      if((clifd=client[i].fd)<0){
	continue;	
      } 
      
      if(FD_ISSET(clifd,&rset)){
	log_msg("isset");
	if((nread=read(clifd,buf,MAXLINE))<0){
	  log_sys("read eror on fd %d",clifd);
	}else if(nread==0){
	  log_msg("closed:uid %d,fd %d",client[i].uid,clifd);
	  
	  client_del(clifd);
	  FD_CLR(clifd,&allset);
	  close(clifd);
	}else{
	 log_msg("request start\n");
	request(buf,nread,clifd,client[i].uid);
      }
      
      }
    }

}
}
