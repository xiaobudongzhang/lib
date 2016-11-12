#include "../apue.h"
#include "../error.c"
#include <errno.h>
#include <linux/limits.h>

#ifdef PATH_MAX
static int pathmax= PATH_MAX;
#else 
static int pathmax = 0;
#endif

#define SUSV3 200112L

static long posix_version = 0;

#define PATH_MAX_GUESS 1024

char * path_alloc(int *sizep){
  char *ptr;
  int size;
  printf("::%d\n",sizep);
  if(posix_version==0){
    posix_version=sysconf(_SC_VERSION);
  }
  if(pathmax==0){
    errno=0;
    if((pathmax=pathconf("/",_PC_PATH_MAX))<0){
      if(errno == 0)
	pathmax = PATH_MAX_GUESS;
      else
	err_sys("pathconf err");
    }else{
      pathmax++;
    }
  }

  if(posix_version<SUSV3)
    size=pathmax+1;
  else
    size = pathmax;
  
  if((ptr=malloc(size))==NULL)
    err_sys("malloc err");

  printf("size=%d\n",size);

  if(sizep != NULL)
    sizep=&size;
  printf("ptr=%p\n",&ptr);
  printf("ptr=%d\n",ptr);
  return(ptr);

}


void main(void){
  int *psize;

  scanf("%d",&psize);
  
  //printf("::::%d",psize);
  path_alloc(psize);
  exit(0);
}





