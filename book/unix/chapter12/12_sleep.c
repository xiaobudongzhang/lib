#include "../apue.h"
#include "../lib/sleep3.c"

int main(void){
  sleep(3);
  printf("sleep1\n");
  sleep(4);
  printf("sleep2\n");
  sleep(5);
  printf("sleep3\n");
  exit(0);
}
