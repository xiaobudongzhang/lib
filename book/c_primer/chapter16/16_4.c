#include <stdio.h>
#define XNAME(n) x##n

int main(void){
  int XNAME(1)=11;
  printf("%d\n",x1);
  return 0;
}
