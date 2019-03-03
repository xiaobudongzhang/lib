#include "../apue.h"
#include "../error.c"

int main(int argc,char *argv[]){
  int i;
  struct stat buf;
  char *ptr;
  
  for(i=1;i<argc;i++){
    printf("%s:",argv[i]);
    if(lstat(argv[i],&buf)<0){
      err_ret("lstat error");
      continue;
    }
    
    if(S_ISREG(buf.st_mode)){
      ptr="regular";
    }else if(S_ISDIR(buf.st_mode)){
      ptr="dir";
    }else{
      ptr="*****";
    }

    printf("%s\n",ptr);
  }
}
