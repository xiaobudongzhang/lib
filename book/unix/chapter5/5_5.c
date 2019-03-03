#include "../apue.h"
#include "../error.c"
//temnam 使用
int main(int argc,char *argv[]){
  if(argc!=3)
    err_quit("usage:a.out <dir> <prefix>");
  printf("%s\n",tempnam(argv[1][0]!=' '?argv[1]:NULL,
			argv[2][0]!=' '?argv[2]:NULL));
  exit(0);
}
