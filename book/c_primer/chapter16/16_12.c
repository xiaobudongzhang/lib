#include <stdio.h>
void me(void);
#pragma c9x on

int main(void){

  printf("__FILE__:%s\n",__FILE__);
  printf("__DATE__:%s\n",__DATE__);
  printf("__TIME__:%s\n",__TIME__);
  //printf("version\n",__STDC_VERSION__);
  printf("line:%d\n",__LINE__);
  printf("function:%s\n",__func__);
  
  return 0;
}
