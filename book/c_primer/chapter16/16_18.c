#include <stdio.h>
#include <stdarg.h>
double sum(int,...);

int main(void){
  double s,t;
  
  s=sum(3,1.1,2.5,13.3);
  t=sum(2,1.1,2.3);
  printf("s:%g\n",s);
  printf("t:%g\n",t);
  
  struct film{
  
    struct f{
      int name2;
      };
    int a;
  };
  return 0;
}

double sum(int lim,...){
  va_list ap;
  double tot=0;
  int i;
  va_start(ap,lim);
  for(i=0;i<lim;i++)
    tot+=va_arg(ap,double);
  va_end(ap);
  return tot;
}
