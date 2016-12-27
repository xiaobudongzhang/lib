#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 5
int main(void){
  char line[MAXLINE];
  int a=0;
 FILE *fp=fopen("test","a+");
  while(fgets(line,MAXLINE,stdin)!=NULL&&line[0]!='\n'){
    ++a;
    fopen(line,"a");
  
    fputs(line,stdout);
  }
  return(0);
}
