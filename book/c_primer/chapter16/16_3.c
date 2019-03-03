#include <stdio.h>
#define P(x) printf("the sq of" #x "is %d\n",((x)*(x)))

int main(void){
  int y=5;
  
  P(y);
  P(2+4);
  return(0);
}
