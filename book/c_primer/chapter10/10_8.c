#include <stdio.h>
#define SIZE 4

int main(void){
  short dates[SIZE];
  short *pti;
  short index;
  double bills[SIZE];
  double *ptf;
  pti =&dates[0];
  ptf=bills;
  
  dates[0]=11;
  printf("name:%p,%p,%d\n",pti,ptf,*(&dates[0]));
  printf("%23s %10s\n","short","double");
  for(index=0;index<SIZE;index++)
    printf("pointers +%d: %10p 10%p\n",index,pti+index,ptf+index);
  return(0);
}
