#include <stdio.h>
#include <stdlib.h>
int main(void){
  double *ptd;
  int max;
  int number;
  int i=0;

  puts("What ?");
  scanf("%d",&max);
  ptd=(double*)malloc(max * sizeof(double));
  
  if(ptd==NULL){
    fputs("malloc fail!",stdout);
    exit(EXIT_FAILURE);
  }

  
  while(i<max&&scanf("%lf",&ptd[i])==1)
    {
      
      ++i;
    }
  number=i;

  
  for(i=0;i<number;i++){
    printf("%7.2f",ptd[i]);
    
    if(i%7==6)
      printf("\n");
  }

  if(i%7==0)
    printf("\n");
  
  free(ptd);
  return(0);
}
