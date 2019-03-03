#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define LIMIT 80
void ToUpper(char *);

int main(void){
  char line[LIMIT]="aabbccddefdg";
  

  char test[2][3]={{'a','b','c'},{'d','e','f'}};
  printf("%c\n",test[1][0]);
  
  ToUpper(line);
  puts(line);
  return(0);
}

void ToUpper(char *str){
  printf("%c\n",*str);
  /*while(*str)
 {
   *str=toupper(*str);
   str++;
   }*/
}
