#include <sys/resource.h>
#include <fcntl.h>
#include <syslog.h>

#define LOCKFILE "/var/run/daemon.pid"
#define LOCKMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

//后台进程
void daemonize(const char *cmd){
  
  int i,fd0,fd1,fd2;
  pid_t pid,pid2,seid;
  struct rlimit r1;
  struct sigaction sa;
  
  umask(0);
  
  if(getrlimit(RLIMIT_NOFILE,&r1)<0)
    err_quit("%s:cant get file limit",cmd);
  
  //to session
  if((pid=fork())<0)
    err_quit("%s :cant fork",cmd);
  else if(pid>0){
    printf("first \n");
    exit(0);
  }else{
    printf("firt ...\n");
    //exit(0);
  }
 
  
  //exit(0);
  seid=setsid();
  if(seid==-1)
    printf("err sesion\n");

  //printf("1 pid=%d,ppid=%d\n",getpid(),getppid());
  //ensure no tty
  sa.sa_handler=SIG_IGN;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags=0;
  if(sigaction(SIGHUP,&sa,NULL)<0)
    err_quit("%s:cant ignore sighub");
  
  
  if((pid2=fork())<0)
  { //exit(0);
    err_quit("%s:cant fork",cmd);
  } else if(pid2>0){
     printf("second parent pid=%d,ppid=%d\n",getpid(),getppid()); 
     exit(0);
  }else{
      printf("second child ....\n");
  }
  
  
  printf("2 pid=%d,ppid=%d\n",getpid(),getppid());
  //cd
  if(chdir("/")<0)
    err_quit("%s:cant change dir to /");
  
  //close all file 
  if(r1.rlim_max==RLIM_INFINITY)
    r1.rlim_max=1024;
  for(i=0;i<r1.rlim_max;i++)
      close(i);
      
  printf("dam done\n");
  //attach file desc 0,1,2 to /dev/null  跟close all file是不是重复了
  fd0=open("/dev/null",O_RDWR);
  fd1=dup(0);
  fd2=dup(0);
  //log err
  if(fd0!=0||fd1!=1||fd2!=2){
    syslog(LOG_ERR,"unexcepted file desc %d  %d  %d",fd0,fd1,fd2);
    exit(1);
  }
  
  printf("dam done\n");
}




//测试锁与唯一调用

int already_runing(void){
  int fd;
  char buf[16];
  
  fd=open(LOCKFILE,O_RDWR|O_CREAT,LOCKMODE);
  if(fd<0){
    printf("open err\n");
    syslog(LOG_ERR,"cantps open %s:%s",LOCKFILE,strerror(errno));
    exit(0);
  }
  printf("hi\n");
  if(lockfile(fd)<0){
    if(errno==EACCES||errno==EAGAIN){
      close(fd);
      return(1);
    }
    printf("lock err\n");
    syslog(LOG_ERR,"cantps lock %s:%s",LOCKFILE,strerror(errno));
    exit(1);
  }

  ftruncate(fd,0);
  sprintf(buf,"%ld",(long)getpid());
  write(fd,buf,strlen(buf)+1);
  return(0);
  
}


ssize_t readn(int fd,void *ptr,size_t n){
  size_t nleft;
  ssize_t nread;
  
  nleft=n;
  while(nleft>0){
    if((nread=read(fd,ptr,nleft))<0){

      if(nleft==1)
	return(-1);
      else
	break;
    }else if(nread==0){
      break;//EOF
    }
    
    nleft-=nread;
    ptr+=nread;

  }
  
  return(n-nleft);
}

ssize_t writen(int fd,const void *ptr,size_t n){
  
  size_t nleft;
  ssize_t nwritten;
  
  nleft=n;
  while(nleft>0){
    if((nwrite=write(fd,ptr,nleft))<0){
      if(nleft==n)
	return (-1);
      else 
	break;
    }else if(nwritten==0){
      break;
    }
    
    nleft-=nwritten;
    ptr+=nwritten;
  }
  return(n-nleft);
}

//popen
static pid_t *childpid=NULL;
static int maxfd;
 
FILE *popen2(const char *cmdstring,const char *type){
   11  int i;
   12  int pfd[2];
   13  pid_t pid;
   14  FILE *fp;

   if((type[0]!='r'&&type[0]!='w')||type[1]!=0){
     errno=EINVAL;
     return(NULL);
   }

   if(childpid==NULL){
     maxfd=sysconf(_SC_OPEN_MAX);
     if((childpid=calloc(maxfd,sizeof(pid_t)))==NULL)
       return(NULL);
   }

   if(pipe(pfd)<0)
     return(NULL);
   
   if((pid=fork())<0){
     return(NULL);
   }else if(pid==0){
     if(*type=='r'){
       close(pfd[0]);
       if(pfd[1]!=STDOUT_FILENO){
	 dup2(pfd[1],STDOUT_FILENO);
	 close(pfd[1]);
       }
     }else{
       close(pfd[1]);
       if(pfd[0]!=STDIN_FILENO){
	 dup2(pfd[0],STDIN_FILENO);
	 close(pfd[0]);
       }
     }
     
     for(i=0;i<maxfd;i++)
       if(childpid[i]>0)
	 close(i);
     execl("/bin/sh","sh","-c",cmdstring,(char*)0);
   }
   //parent
   if(*type=='r'){
            close(pfd[1]);
	    if((fp=fdopen(pfd[0],type))==NULL){
	      return(NULL);
	    }
   }else{
     close(pfd[0]);
     if((fp=fdopen(pfd[1],type))==NULL)
       return(NULL);
   }

   childpid[fileno(fp)]=pid;
   return(fp);
}
