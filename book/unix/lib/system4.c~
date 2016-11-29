int system3(const char *cmdstr){
  pid_t pid;
  int status;

  if(cmdstr==NULL)
    return (1);

  if((pid=fork())<0){
    status=-1;
  }else if(pid==0){
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

  return status;
}

