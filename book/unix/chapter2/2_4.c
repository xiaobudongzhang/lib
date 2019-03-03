#include "../apue.h"
#include "../error.c"
#include <errno.h>
#include <bits/local_lim.h>


#ifdef OPEN_MAX
static long openmax=OPEN_MAX;
#else
static long openmax=0;
#endif

#define OPEN_MAX_GUESS 256

long open_max(void){
  
  if(openmax==0){
    errno=0;
    if((openmax=sysconf(_SC_OPEN_MAX))<0){
      if(errno==0)
	openmax=OPEN_MAX_GUESS;
      else
	err_sys("sysconf err");
    }
  }

  return(openmax);
}


void main(void){
  
  int max=open_max();
  printf("max:%d",max);
  exit(0);
}
