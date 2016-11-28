#include "../error.c"
#include <stddef.h>
#include <string.h>
#include <pwd.h>
//打印用户信息
struct passwd *getpwnam(const char *name){
  struct passwd *ptr;
  
  setpwent();
  while((ptr = getpwent()) !=NULL){
    if(strcmp(name,ptr->pw_name)==0)
      break;
  }

  endpwent();
  return (ptr);
}

int main(void){
  struct passwd *user;
  user=getpwnam("byz");
  
  printf("%s\n",user->pw_passwd);
  exit(0);
}
