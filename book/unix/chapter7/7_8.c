#include "../apue.h"
#include "../error.c"

#if defined(BSD)
#include <sys/time.h>
#define FMT "%10ld"
#else
#define FMT "%10ld"
#endif
#include <sys/resource.h>

#define doit(name) pr_limits(#name,name)

static void pr_limits(char *,int);

int main(void){
#ifdef RLIMIT_AS
  doit(RLIMIT_AS);
#endif

  doit(RLIMIT_CORE);
  doit(RLIMIT_CPU);
  doit(RLIMIT_DATA);
  doit(RLIMIT_FSIZE);
  doit(RLIMIT_STACK);
  doit(RLIMIT_NOFILE);
    exit(0);
}

static void pr_limits(char *name,int resource){
  struct rlimit limit;
  
  if(getrlimit(resource,&limit)<0)
    err_sys("getrlimit err:%s",name);

  printf("%-14s ",name);

  if(limit.rlim_cur==RLIM_INFINITY){
    printf("infinite   ");
  }else{
    printf(FMT,limit.rlim_cur);
  }

  if(limit.rlim_max==RLIM_INFINITY)
    printf("ini\n");
  else
    printf(FMT,limit.rlim_max);
  
  putchar((int)'\n');
}
