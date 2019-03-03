//#include "opend.h"
#include <fcntl.h>

#define MAXARGC 50
#define WHITE "\t\n "//空格很重要 坑

//buf_args

int buf_args(char *buf,int (*optfunc)(int,char **)){
  char *ptr,*argv[MAXARGC];
  int argc;
  
  if(strtok(buf,WHITE) == NULL)
    return(-1);


  argv[argc=0]=buf;
  //printf("buf:%s\n",argv);

  while((ptr=strtok(NULL,WHITE))!=NULL){
    if(++argc>=MAXARGC-1)
      return(-1);
    //printf("ptr %s\n",ptr);
    argv[argc]=ptr;
  }
  
  argv[++argc]=NULL;
  
  //write(STDOUT_FILENO,argv,strlen(argv));
  return((*optfunc)(argc,argv));
}

int cli_args(int argc,char **argv){

  printf("argc:%d\n",argc);
  if(argc!=3||strcmp(argv[0],CL_OPEN)!=0){
    strcpy(errmsg,"usage:<pathname><oflag>\n");
    return(-1);
  }

  pathname=argv[1];
  oflag=atoi(argv[2]);
  return(0);
}
