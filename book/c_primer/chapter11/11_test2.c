#include <stdio.h>
int main(void){
  char *test="abc0def";
  
  while(*test){
    putchar(*test++);
  }
  
  if(1){
    printf("hi\n");
  }
  return(0);
}
