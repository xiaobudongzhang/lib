#include "../apue.h"
#include "../error.c"
//竞争实例

static void chartime(char *);

int main(void){
  pid_t pid;
  
  //  TELL_WAIT();

  if((pid=fork())<0){
    err_sys("fork err");
  }else if(pid==0){
    chartime("output from child\n");
  }else{
	sleep(5);
    chartime("output from parent\n");
  }
  exit(0);
}

static void chartime(char *str){

  char *ptr;
  int c;
  
  setbuf(stdout,NULL);//no buffer
  for(ptr=str;(c=*ptr++)!=0;)
    putc(c,stdout);
}
