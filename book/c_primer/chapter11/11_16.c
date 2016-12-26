#include <stdio.h>
#define ANSWER "Grant"
int main(void){
  char try[40];
  
  puts("Who is ?");
  gets(try);
  while(*try!=*ANSWER){
    puts("no,thats wrong。");
    gets(try);
  }
  puts("ok!");
  return(0);
}
