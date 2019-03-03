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
#define QLEN 5

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif
//socket server 
int initserver(int type,const struct sockaddr *addr,socklen_t alen,int qlen){
  int fdt;
  int err;
  printf("init server\n");  
  if((fdt=socket(addr->sa_family,type,0))<0)
  {
      //return(-1);
      printf("init server2\n");
      return(-1);
  }
  open("tmp29", O_WRONLY|O_CREAT|O_TRUNC);
  printf("init server3\n");
 

  char abuf[INET_ADDRSTRLEN];
  const char *addr2;
  struct sockaddr_in *sinp;
  sinp=(struct sockaddr_in *)addr;
  //if(addr->sa_family==AF_INET){
 addr2=inet_ntop(AF_INET,&sinp->sin_addr,abuf,INET_ADDRSTRLEN);
  printf(" address %s ",addr2?addr2:"unknown");
  printf(" port %d ",ntohs(sinp->sin_port));
  //}

  if(bind(fdt,addr,alen)<0){
    printf("init server5\n");
    printf("%d\n",errno);
    printf("%s\n",strerror(errno));
    err=errno;
    goto errout;
  }
  open("tmp50", O_WRONLY|O_CREAT|O_TRUNC);
  printf("init server4\n");
  if(type==SOCK_STREAM||type==SOCK_SEQPACKET){
    if(listen(fdt,qlen)<0){
      open("tmp54", O_WRONLY|O_CREAT|O_TRUNC);
      err=errno;
      goto errout;
    }
  }
  open("tmp59", O_WRONLY|O_CREAT|O_TRUNC);
  printf("init server\n");
  return(fdt);
  
 errout:
  close(fdt);
  errno=err;
  return(-1);
}

void serve(int sockfd){
  int clfd;
  FILE *fp;
  char buf[BUFLEN];
  
  for(;;){
    open("tmp75", O_WRONLY|O_CREAT|O_TRUNC);
    printf("in serve\n");
    clfd=accept(sockfd,NULL,NULL);
    if(clfd<0){
      open("tmp79", O_WRONLY|O_CREAT|O_TRUNC);
      syslog(LOG_ERR,"ruptimed:accept error:%s",strerror(errno));
      exit(1);
    }
    printf("in serve2\n");
    open("tmp84", O_WRONLY|O_CREAT|O_TRUNC);
    if((fp=popen("/usr/bin/uptime","r"))==NULL){
      
      sprintf(buf,"error:%s\n",strerror(errno));
      send(clfd,buf,strlen(buf),0);
      printf("in serve send");
    }else{
      printf("innn\n");
      while(fgets(buf,BUFLEN,fp)!=NULL){
	send(clfd,buf,strlen(buf),0);
	pclose(fp);
      }
      close(clfd);
    }
  }
  printf("in serve3\n");
}


int main(int argc,char *argv[]){
  struct addrinfo *ailist,*aip;
  struct addrinfo hint;
  int sockfd,err,n;
  char *host;
  
  if(argc!=1)
    ;//err_quit("usage :ruptimed");

#ifdef _SC_HOST_NAME_MAX
  n=sysconf(_SC_HOST_NAME_MAX);
  if(n<0) n=256;
#endif
  n=HOST_NAME_MAX;
  host=malloc(n);
  if(host==NULL)
    err_sys("gethostname error");
  if(gethostname(host,n)<0)
    err_sys("gethostname error");
  
  
  daemonize("ruptimed");
  open("./tmp", O_WRONLY|O_CREAT|O_TRUNC);
  printf("hi\n");
  
  //memset(&hint, 0, sizeof hint);
  hint.ai_flags=AI_PASSIVE;
  hint.ai_family=0;
  hint.ai_socktype=SOCK_STREAM;
  hint.ai_protocol=0;
  hint.ai_addrlen=0;
  hint.ai_canonname=NULL;
  hint.ai_addr=NULL;
  hint.ai_next=NULL;
  
  printf("host %s\n",host);
  
  
  if((err=getaddrinfo(argv[1],argv[2],&hint,&ailist))!=0){
    printf("in log err\n");
    syslog(LOG_ERR,"ruptimed:getaddrinfo error:%s",gai_strerror(err));
    exit(1);
  }
  printf("start server\n");
  open("tmp141", O_WRONLY|O_CREAT|O_TRUNC);
  for(aip=ailist;aip!=NULL;aip=aip->ai_next){
    printf("in for to ss\n");
    //printf("%d\n",aip->ai_addrlen);
    if((sockfd=initserver(SOCK_STREAM,aip->ai_addr,aip->ai_addrlen,QLEN))>=0){
      open("tmp152", O_WRONLY|O_CREAT|O_TRUNC);
      serve(sockfd);
      exit(0);
    }
  }

  exit(1);
}
