#include <stdio.h>
#define ANSWER "Grant"
int main(void){
  char try[40];
  
  puts("Who is ?");
  gets(try);
  while(strcmp(try,ANSWER)){
    puts("no,thats wrong2。");
    gets(try);
  }
  puts("ok!");
  return(0);
}
