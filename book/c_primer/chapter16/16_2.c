#include <stdio.h>
#define SQUARE(X) X*X
#define PR(X) printf("result is %d\n",X);

int main(void){
  int x=4;
  int z;
  
  printf("++x");
  PR(SQUARE(++x));
  printf("after incre ,x is %x\n",x);
  return 0;
}
