#include <stdio.h>
#include <stdlib.h>
#define CNTL_Z '\032'
#define SLEN 50

int main(void){
  char file[SLEN];
  char ch;
  FILE *fp;
  long count,last;
  
  gets(file);
  if((fp=fopen(file,"rb"))==NULL){
    exit(1);
  }
  
  fseek(fp,0L,SEEK_END);
  last=ftell(fp);
  for(count=1L;count<=last;count++){
    fseek(fp,-count,SEEK_END);
    ch=getc(fp);
    putchar(ch);
  }
  
  putchar('\n');
  fclose(fp);
  return(0);
}
