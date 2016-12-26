#include <stdio.h>
#include <string.h>
#define WORDS "koast"
#define SIZE 40

int main(void){
  char *orig=WORDS;
  char copy[SIZE]="Be the best that you can be";
  char *ps;
  
  puts(orig);
  puts(copy);
  ps=strcpy(copy+7,orig);
  puts(copy);
  puts(ps);
  return(0);
}
