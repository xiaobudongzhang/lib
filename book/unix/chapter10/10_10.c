//打印信号屏蔽字

void pr_mask(const char *str){
  sigset_t newmask,sigset,pendmask;
  int errno_save;
  
  errno_save=errno;
  
  //sigemptyset(&newmask);
  //sigemptyset(&sigset);
  // sigaddset(&newmask,SIGINT);

  //if(sigprocmask(SIG_BLOCK,&newmask,&sigset)<0)
  //err_sys("sig_block err");


   if(sigprocmask(0,NULL,&sigset)<0)
     err_sys("sigprocmask err");
  
  printf("pr_mask--%s",str);
  /**sleep(16);
  if(sigpending(&pendmask)<0)
    err_sys("sigpending err");
  */
  
  if(sigismember(&sigset,SIGINT))
       printf("SIGINT");
  if(sigismember(&sigset,SIGQUIT))
       printf("SIGQUIT");
  if(sigismember(&sigset,SIGUSR1))
       printf("SIGUSR1");
  if(sigismember(&sigset,SIGALRM))
       printf("SIGALRM");

  printf("\n");
  errno=errno_save;

}
