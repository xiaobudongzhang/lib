#include "../apue.h"
#include "../error.c"
#include <pwd.h>
//不可载入
static void my_alarm(int signo){
  
  struct passwd  *rootptr;
  
  printf("in signal handler\n");
  if((rootptr=getpwnam("root"))==NULL){
    err_sys("getpwnam err");
  }
  printf("user：%s\n",rootptr->pw_name);
  
  alarm(1);

}

int main(void){
  
  struct passwd *ptr;

  signal(SIGALRM,my_alarm);
  
  alarm(1);
  
  for(;;){
    if((ptr=getpwnam("byz"))==NULL)
      err_sys("get byz err");
    printf("user：%s\n",ptr->pw_name);
    if(strcmp(ptr->pw_name,"byz")!=0)
      printf("return err~pw_name=%s\n",ptr->pw_name);
  }
}
