#include <stdio.h>
#define DEF "i am def"
int main(void){
  char str1[]="123456789";
  const char *str2="A to string";
  
  puts("I am to puts");
  puts(DEF);
  puts(str1);
  puts(str2);
  puts(&str1[3]);
  puts(str2+2);
  printf("strlen:%d,sizeof:%d\n",strlen(str1),sizeof(str1));
  
  
}
