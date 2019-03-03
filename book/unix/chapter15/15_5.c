#include "../apue.h"
#include "../error.c"
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
//popen
static pid_t *childpid=NULL;
static int maxfd;

FILE *popen(const char *cmdstring,const char *type){
  int i;
  int pfd[2];
  pid_t pid;
  FILE *fp;
  
  if((type))
}
