#include <stdio.h>

#define MAX 81

int main(void){
  char name[MAX];
  char * ptr;
  
  ptr=gets(name);
  printf("input:%s\n",name);
  return(0);
}
