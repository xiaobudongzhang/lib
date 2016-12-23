#include "../apue.h"
#include "../error.c"
#include <termios.h>

int main(void){
  struct termios term;
  
  if(tcgetattr(STDIN_FILENO,&term)<0)
    err_sys("tcgetattr err");
  
  switch(term.c_cflag&CSIZE){
    case CS5:
      printf("5 bits\n");
      break;
    case CS6:
      printf("6 bits\n");
      break;
  case CS7:
    printf("7bits\n");
    break;
  case CS8:
    printf("8 bits\n");
    break;
  default:
    printf("unknown bits\n");
  }
  
  term.c_cflag&=~CSIZE;
  term.c_cflag|=CS8;
  
  if(tcsetattr(STDIN_FILENO,TCSANOW,&term)<0)
    err_sys("tcsetattr err");
  
  exit(0);
}
