#include "../apue.h"
#include "../error.c"
#include <sys/acct.h>
//打印进程会计记录
#ifdef HAS_SA_STAT
#define FMT "%-*.*s e = %6ld,chars = %7ld,stat = %3u:%c %c %c %c\n"
#else
#define FMT "%-*.*s  e = %6ld,chars = %7ld,%c %c %c %c\n"
#endif

#ifndef HAS_ACORE
#define ACORE 0
#endif

#ifndef HAS_AXSIG
#define AXSIG 0
#endif

static unsigned long compt2ulong(comp_t comptime){
  unsigned long val;
  int           exp;

  val=comptime & 0x1fff;
  exp=(comptime>>13)&7;
  
  while(exp-->0)
    val*=8;
  
  return (val);
}


int main(int argc,char *argv[]){
  struct acct acdata;
  FILE *fp;
  
  //  printf("test:%-*.*s\n",3,3,"sst");
  if(argc!=2)
    err_sys("usage:pracct filename");
  
  if((fp=fopen(argv[1],"r"))==NULL)
    err_sys("fopen err");

  while(fread(&acdata,sizeof(acdata),1,fp)==1){
    //printf("test:%s\n",acdata.ac_comm);
    
    printf(FMT,(int)sizeof(acdata.ac_comm),(int)sizeof(acdata.ac_comm),acdata.ac_comm,compt2ulong(acdata.ac_etime),compt2ulong(acdata.ac_io),
#ifdef HAS_SA_STAT
	   (unsigned char)acdata.ac_stat,
#endif
	   acdata.ac_flag&ACORE?'D':' ',
	   acdata.ac_flag&AXSIG?'X':' ',
	   acdata.ac_flag&AFORK?'F':' ',
	   acdata.ac_flag&ASU?'S':' '
);
    //break;
  }

  if(ferror(fp))
    err_sys("read err");
  exit(0);
}
