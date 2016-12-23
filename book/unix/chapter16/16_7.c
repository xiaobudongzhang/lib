#include "../apue.h"
#include "../error.c"
#include "../lib/daemonize.c" 
#include <netdb.h>
#include <errno.h>
#include <syslog.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>

#define BUFLEN 128
#define TIMEOUT 10

void sigalrm(int signo){
  printf("in sigalrm\n");
}
//socket server 
void print_uptime(int sockfd,struct addrinfo *aip){
  int n;
  char buf[BUFLEN];

  printf("in pr_uptime\n");

  buf[0]=0;
  
  char abuf[INET_ADDRSTRLEN];
  const char *addr2;
  struct sockaddr_in *sinp;
  sinp=(struct sockaddr_in *)aip->ai_addr;
  addr2=inet_ntop(AF_INET,&sinp->sin_addr,abuf,INET_ADDRSTRLEN);
  printf(" address %s ",addr2?addr2:"unknown");
  printf(" port %d ",ntohs(sinp->sin_port));

  if(sendto(sockfd,buf,1,0,aip->ai_addr,aip->ai_addrlen)<0)
    err_sys("sendto error");

  printf("in pr_uptime28\n");
  alarm(TIMEOUT);
  if((n=recvfrom(sockfd,buf,BUFLEN,0,NULL,NULL))<0){
    if(errno!=EINTR)
       alarm(0);
    printf("err recv\n");
    err_sys("recv error");
  }
  printf("in pr_uptime35\n");
  write(STDOUT_FILENO,buf,n);
  printf("in pr_uptime38\n");
}


int main(int argc,char *argv[]){
  struct addrinfo *ailist,*aip;
  struct addrinfo hint;
  int sockfd,err,n;
  char *host;
  struct sigaction sa;

  //if(argc!=2)
  //err_quit("usage :ruptimed");

  sa.sa_handler=sigalrm;
  sa.sa_flags=0;
  sigemptyset(&sa.sa_mask);
  if(sigaction(SIGALRM,&sa,NULL)<0)
    err_sys("sigaction error");
  //memset(&hint, 0, sizeof hint);
  hint.ai_flags=0;
  hint.ai_family=0;
  hint.ai_socktype=SOCK_DGRAM;
  hint.ai_protocol=0;
  hint.ai_addrlen=0;
  hint.ai_canonname=NULL;
  hint.ai_addr=NULL;
  hint.ai_next=NULL;
  
  // printf("host %s\n",host);
  
  
  if((err=getaddrinfo(argv[1],argv[2],&hint,&ailist))!=0){
    printf("in log err\n");
    syslog(LOG_ERR,"ruptimed:getaddrinfo error:%s",gai_strerror(err));
    exit(1);
  }
  printf("start server\n");
  
  for(aip=ailist;aip!=NULL;aip=aip->ai_next){
    printf("in for to ss\n");
    //printf("%d\n",aip->ai_addrlen);
    if((sockfd=socket(aip->ai_family,SOCK_DGRAM,0))<0){
      err=errno;
    }else{
      print_uptime(sockfd,aip);
      exit(0);
    }
  }
  fprintf(stderr,"cant concat %s:%s\n",argv[1],strerror(err));
  exit(1);
}
