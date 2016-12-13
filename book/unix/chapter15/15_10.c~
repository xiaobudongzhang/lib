#include "../apue.h"
#include "../error.c"
//get sum
int main(void){
  int n,int1,int2;
  char line[4096];
  FILE *fp;
  char buf[4096];
  while((n=read(STDIN_FILENO,line,4096))>0){
     line[n]=0;
    
    if(sscanf(line,"%d%d",&int1,&int2)==2){
      sprintf(line,"%d\n",int1+int2); 
     if(write(STDOUT_FILENO,line,n)!=n)
	err_sys("write err");
    }else{
      if(write(STDOUT_FILENO,"invlid arg\n",13)!=13)
	err_sys("write err");
    }
  }
  exit(0);
}
