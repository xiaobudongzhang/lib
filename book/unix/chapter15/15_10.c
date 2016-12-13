#include "../apue.h"
#include "../error.c"
//get sum 2
int main(void){
  int n,int1,int2;
  char line[4096];
  if(setvbuf(stdin,NULL,_IOLBF,0)!=0)
    err_sys("setvbuf err");
  if(setvbuf(stdout,NULL,_IOLBF,0)!=0)
    err_sys("setvbuf err");
    
  while(fgets(line,MAXLINE,stdin)!=NULL){
    
    if(sscanf(line,"%d%d",&int1,&int2)==2){
      
      if(printf("%d\n",int1+int2)==EOF)
      	err_sys("write err");
    }else{
      if(printf("invlid arg\n")==EOF)
	err_sys("write err");
    }
  }
  exit(0);
}
