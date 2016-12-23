//#include "opend2.h"
#include "17_8_serve_listen.c"
#include "17_9_serve_accept.c"
#include <poll.h>
#include <stropts.h>
#include "mutl_2.c"
#include "17_32_request2.c"

void loop(void){
  int i,maxi,listenfd,clifd,nread;
  char buf[MAXLINE];
  uid_t uid;
  struct pollfd *pollfd;
  int open_max=10;
  log_msg("msg15");
  if((pollfd=malloc(open_max*sizeof(struct pollfd)))==NULL)
    err_sys("malloc error");
  //init
    for (i = 0; i < open_max; i++) {
      pollfd[i].fd = -1;
      pollfd[i].events = POLLIN;
      pollfd[i].revents = 0;
    }

     if((listenfd=serv_listen(CS_OPEN))<0)
        log_sys("serv_listen error");
     client_add(listenfd,0);
     pollfd[0].fd=listenfd;//0分配给了监听listen 其他分配给accept
     pollfd[0].events=POLLIN;
     maxi=0;
     
     for(;;){
       
       if(poll(pollfd,maxi+1,-1)<0)
       {
	   log_msg("poll_err");
	   log_sys("poll error");
       }
       
       if(pollfd[0].revents&POLLIN){	   
	 
	 if((clifd=serv_accept(listenfd,&uid))<0)
            log_sys("serv_accept error:%d",clifd);
	 
	 i=client_add(clifd,uid);

	 pollfd[i].fd=clifd;
	 pollfd[i].events=POLLIN;
	 if(i>maxi)
	   maxi=i;
	 
	 log_msg("new connection:uid%d,fd %d",uid,clifd);
       }
       
       
       for(i=1;i<=maxi;i++){
	 if((clifd=client[i].fd)<0)
	   continue;
	 if(pollfd[i].revents&POLLHUP){//挂起
	   goto hungup;
	 }else if(pollfd[i].revents&POLLIN){

	   if((nread=read(clifd,buf,MAXLINE))<0){
	     log_sys("read error on fd %d",clifd);
	   }else if(nread==0){
	   hungup:
	     log_msg("closed:uid %d,fd %d",client[i].uid,clifd);
	     client_del(clifd);
	     pollfd[i].fd=-1;
	     close(clifd);
	   }else{
	     printf("request\n");
	     request(buf,nread,clifd,client[i].uid);
	   }
	 }
       }
     }
}
