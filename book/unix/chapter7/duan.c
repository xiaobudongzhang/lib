#include  "../apue.h"
//判断大端小端模式
int IsBigEndian()  
{  
  int a = 0x1238;  
  //printf("%p\n",*(&a));
  char b =  *(char *)&a;   
  if( b == 0x12)  
    {  
      return 1;  
    }  
  return 0;  
}

int main(void){

  printf("%d\n", IsBigEndian());
  exit(0);
}
