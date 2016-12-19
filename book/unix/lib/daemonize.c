#include <sys/resource.h>
#include <fcntl.h>
#include <syslog.h>
//后台进程
void daemonize(const char *cmd){
  
  int i,fd0,fd1,fd2;
  pid_t pid,pid2,seid;
  struct rlimit r1;
  struct sigaction sa;
  //open("./dae11", O_WRONLY|O_CREAT|O_TRUNC);
  //umask(0);
  
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
 
  //open("./dae28", O_WRONLY|O_CREAT|O_TRUNC);
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
  
  
  printf("22 pid=%d,ppid=%d\n",getpid(),getppid());
  //cd
  /*if(chdir("/")<0)
    err_quit("%s:cant change dir to /");*/
  //open("./dae58", O_WRONLY|O_CREAT|O_TRUNC);
  //close all file 
  if(r1.rlim_max==RLIM_INFINITY)
    r1.rlim_max=1024;
  for(i=0;i<r1.rlim_max;i++)
     close(i);
  //open("./dae64", O_WRONLY|O_CREAT|O_TRUNC);
  printf("dam done\n");
  //attach file desc 0,1,2 to /dev/null  跟close all file是不是重复了
  fd0=open("/dev/null",O_RDWR);
  fd1=dup(0);
  fd2=dup(0);
  //open("./dae70", O_WRONLY|O_CREAT|O_TRUNC); 
  //log err
  if(fd0!=0||fd1!=1||fd2!=2){
    syslog(LOG_ERR,"unexcepted file desc %d  %d  %d",fd0,fd1,fd2);
    open("./dae74", O_WRONLY|O_CREAT|O_TRUNC); 
    exit(1);
  }
  

  open("./dae78", O_WRONLY|O_CREAT|O_TRUNC);
  printf("dam done22\n");
}


