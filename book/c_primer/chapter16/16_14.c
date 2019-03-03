#include <stdio.h>
#include <stdlib.h>
void sign_off(void);

int main(void){
  int n;
  
  atexit(sign_off);

  puts("main");
  return(0);
}

void sign_off(void){
  puts("call sign_off");
}
