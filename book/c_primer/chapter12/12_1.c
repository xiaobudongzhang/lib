#include <stdio.h>
int main(void){
  int x=30;
  while(x++<33){
    int x=100;
    x++;
    printf("x in while value:%d\n",x);
  }
  
  printf("x:%d\n",x);
  return(0);
}
