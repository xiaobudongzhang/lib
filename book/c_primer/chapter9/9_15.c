#include <stdio.h>
void change(int * u,int * v);

int main(void){
  //int change();
  int x=5,y=10;
  printf("Original x=%d and y=%d\n",x,y);
  change(&x,&y);
  printf("Now x=%d and y=%d\n",x,y);
  return(0);
}

void change(int *u,int *v){
  
  int temp;
  temp=*u;
  *u=*v;
  *v=temp;
}
