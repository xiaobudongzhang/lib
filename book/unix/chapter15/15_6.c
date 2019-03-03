#include "../apue.h"
#include <ctype.h>
#include "../error.c"

int main(void){
  int c;
  while((c=getchar())!=EOF){
    if(isupper(c))

      c=tolower(c);

    if(putchar(c)==EOF)
      ; //err_sys("output err");
      
    if(c=='\n')
      fflush(stdout);
  }
  exit(0);
}
