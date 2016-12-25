#include <stdio.h>
void mik(int);

int main(void){
  int pooh=2,bah=5;
  
  printf("1:%d,%p\n",pooh,&pooh);
  printf("2:%d,%p\n",bah,&bah);
  
  mik(pooh);
  return(0);
}

void mik(int bah){
  int pooh=8;
  
  printf("3:%d,%p\n",pooh,&pooh);
  printf("4:%d,%p\n",bah,&bah);

} 
