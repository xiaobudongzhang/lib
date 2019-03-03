#include <stdio.h>

int main(void){
  unsigned char val=2;
  printf("%#X,%#X,%d\n",val,~val,sizeof(int));
  return(0);
}
