#include <stdio.h>
int main(void){
  char name1[11],name2[11];
  int count;
  
  printf("enter name:\n");
  count=scanf("%5s %10s",name1,name2);
  printf("read %d names %s and %s\n",count,name1,name2);
  return(0);
}
