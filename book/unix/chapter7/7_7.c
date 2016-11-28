#include <stdio.h>
#ifndef LINE_MAX
#define LINE_MAX 8
#endif

//自动变量test  声明自动变量的函数已经返回后，不能再引用这些自动变量。 
FILE *open_data(void){
  FILE *fp;
  char databuf[BUFSIZ];

  if((fp=fopen("tmp","rb"))==NULL)
    return (NULL);
  
  if(setvbuf(fp,databuf,_IOLBF,BUFSIZ)!=0)
    return (NULL);
  
  return(fp);

}

void  testme(void){
  char databuf[BUFSIZ]="hi";
}

int main(void){
  
  FILE *fp=open_data();
  char line[LINE_MAX];

  testme();
  //char databuf[BUFSIZ]="hi";
  // printf("::%s\n",databuf);
  while (fgets(line, LINE_MAX, fp) != NULL) {
    fputs(line,stdout);
  }
  //printf(":%s\n",databuf);
  return(0);

}
