#include "../apue.h"
#include "../lib/sleep3.c"
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

int main(void){
  sleep3(5);
  return(0);
}

