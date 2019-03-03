#include <stdio.h>
#include <stdlib.h>

int main(void){
  char number[20];
  char *end;
  long value;
  
  
  while(fgets(number,30,stdin)&&number[0]!='\n'){
    value=strtol(number,&end,10);
    printf("value:%ld,stopped at %s(%d)\n",value,end,*end);
  }
  return(0);
}
