#include "../apue.h"
#include "../error.c"

void pr_stdio(const char * ,FILE *);

int main(void){
  FILE *fp;
  fputs("enter\n",stdout);
  if(getchar()==EOF)
    err_sys("getchar error");
  fputs("one line to error\n",stderr);
  
  // setvbuf(stdin,NULL,_IOFBF,1024);
  pr_stdio("stdin",stdin);
  pr_stdio("stdout",stdout);
  pr_stdio("stderr",stderr);
  
  if((fp=fopen("/etc/virc","rb"))==NULL)
    err_sys("fopen err");
  if(getc(fp)==EOF)
    err_sys("getc error");
  pr_stdio("/etc/virc",fp);
  exit(0);
}

void pr_stdio(const char *name,FILE *fp){
  printf("stream =%s ,",name);
  
  if(fp->_IO_file_flags&_IO_UNBUFFERED)
    printf("unbuffered");
  else if(fp->_IO_file_flags&_IO_LINE_BUF)
    printf("line buffer");
  else
    printf("full buffer");
  
  printf(",buffer size =%d \n",fp->_IO_buf_end-fp->_IO_buf_base);
}
