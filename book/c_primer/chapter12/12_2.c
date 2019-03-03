#include <stdio.h>


int main(void){
  int n=10;
  
  int x=1;
  int x2=x*2;
  
  for(int n=1;n<3;n++){
    printf("loop  index n=%d\n",n);
    int n=30;
    printf("loop n=%d\n",n);
    n++;
    printf("loop222 n=%d\n",n);
  }
  printf("n:%d\n",n);
  return(0);
}
