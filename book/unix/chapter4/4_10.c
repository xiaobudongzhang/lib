#include "../apue.h"
#include "../error.c"
#include <sys/sysmacros.h>
//打印st_dev(设备号)
int main(int argc,char *argv[]){
  int i;
  struct stat buf;
  
  for(i=1;i<argc;i++){
    printf("%s:",argv[i]);
    if(stat(argv[i],&buf)){
      err_ret("stat error");
      continue;
    }
    
    printf("dev=%d/%d",major(buf.st_dev),minor(buf.st_dev));
    if(S_ISCHR(buf.st_mode)||S_ISBLK(buf.st_mode)){
      printf("(%s) rdev = %d/%d",
	     (S_ISCHR(buf.st_mode))?"char":"block",
	     major(buf.st_dev),minor(buf.st_rdev)
	     );
    }
    printf("\n");
  }
  exit(0);

}
