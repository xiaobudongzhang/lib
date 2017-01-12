#include <stdio.h>
//test struct ->
int main(void){
  struct test{
    char name[10];
  };

  struct test a={
    "byz"
  };

  a.name;
  //a->name
  return 0;
}
