static void sig_alrm(int signo){
  printf("sig_alrm\n");

  // longjmp(env_alrm,1);

}

unsigned int sleep3(unsigned int nsecs){

  struct sigaction newact,oldact;
  sigset_t newmask,oldmask,suspmask;
  unsigned int unslept;
  //保存handler
  newact.sa_handler=sig_alrm;
  sigemptyset(&newact.sa_mask);
  newact.sa_flags=0;
  sigaction(SIGALRM,&newact,&oldact);
  //block SIGALRM
  sigemptyset(&newmask);
  sigaddset(&newmask,SIGALRM);
  sigprocmask(SIG_BLOCK,&newmask,&oldmask);


    alarm(nsecs);

  suspmask=oldmask;
  sigdelset(&suspmask,SIGALRM);
  sigsuspend(&suspmask);

  

    
  unslept=alarm(0);
  sigaction(SIGALRM,&oldact,NULL);
  sigprocmask(SIG_SETMASK,&oldmask,NULL);

  return(unslept);
}

