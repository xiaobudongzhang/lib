#include "../apue.h"
#include "../error.c"

int main(void){
  printf("real uid=%d,euid=%d\n",getuid(),geteuid());
  exit(0);
}
