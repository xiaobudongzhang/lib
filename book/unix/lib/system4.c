//信号处理的sys
int system4(const char *cmdstr){
  pid_t pid;
  int status;
  struct sigaction ignore,saveintr,savequit;
  sigset_t chldmask,savemask;
  
  if(cmdstr==NULL)
    return (1);
  //ignore SIGINT SIGQUIT
  ignore.sa_handler=SIG_IGN;
  sigemptyset(&ignore.sa_mask);
  ignore.sa_flags=0;
  if(sigaction(SIGINT,&ignore,&saveintr)<0)
    return(-1);
  if(sigaction(SIGQUIT,&ignore,&savequit)<0)
    return(-1);
  //block SIGCHLD
  sigemptyset(&chldmask);
  sigaddset(&chldmask,SIGCHLD);
  if(sigprocmask(SIG_BLOCK,&chldmask,&savemask)<0)
    return(-1);
  
  if((pid=fork())<0){
    status=-1;
  }else if(pid==0){
    //restore action & reset sinal  复原
    sigaction(SIGINT,&saveintr,NULL);
    sigaction(SIGQUIT,&savequit,NULL);
    sigprocmask(SIG_SETMASK,&savemask,NULL);
    
    execl("/bin/sh","shss","-c",cmdstr,(char *)0);
    _exit(127);
  }else{
    while(waitpid(pid,&status,0)<0){
      if(errno!=EINTR){
        status=-1;
        break;
      }
    }
  }
  //复原
  if(sigaction(SIGINT,&saveintr,NULL)<0)
    return(-1);
  if(sigaction(SIGQUIT,&savequit,NULL)<0)
    return(-1);
  if(sigprocmask(SIG_SETMASK,&savemask,NULL)<0)
    return(-1);

  return status;
}

