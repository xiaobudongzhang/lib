#include <stdio.h>
#define SIZE 10
int sum(int * start,int * end);

int main(void){
  int marbles[SIZE]={20,10,5,39,4,16,19,26,31,20};
  long answer;
  
  
  printf("%p\n",marbles);
  
  int *tmp=marbles;
  int *tmp2=++tmp;
  printf("%p,%lu\n",tmp,tmp2);

  answer=sum(marbles,marbles+SIZE);
  printf("The total num is %ld\n",answer);
  printf("size of is %zd bytes \n",sizeof marbles);
  return(0);
}

int sum(int * start,int * end){
  int i;
  int total=0;
  
  while(start<end){
    total+=*start;
    start++;
  }
  return total;
}
