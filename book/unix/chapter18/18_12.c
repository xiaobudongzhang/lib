#include "../apue.h"
#include "../error.c"
#include <termios.h>
#ifndef TIOCGWINSZ
#include <sys/ioctl.h>
#endif
#include "../lib/signal3.c"

static void pr_winsize(int fd){
  struct winsize size;
  
  if(ioctl(fd,TIOCGWINSZ,(char *)&size)<0)
    err_sys("tiocgeins error");
  printf("%d rows ,%d columns\n",size.ws_row,size.ws_col);
}

static void sig_winch(int signo){
  printf("sigwinch receive\n");
  pr_winsize(STDIN_FILENO);
}

int main(void){
  if(isatty(STDIN_FILENO)==0)
    exit(1);
  if(signal3(SIGWINCH,sig_winch)==SIG_ERR)
    err_sys("signal error");
  pr_winsize(STDIN_FILENO);
  for(;;)
    pause();
}
