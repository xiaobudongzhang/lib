#include <stdio.h>
#define SIZE 4

int main(void){
  int no_data[SIZE];
  int i;
  
  //  no_data[SIZE]={1,3,4,5};

  for(i=0;i<SIZE;i++)
    printf("%2d%14d\n",i,no_data[i]);
  return 0;
}
