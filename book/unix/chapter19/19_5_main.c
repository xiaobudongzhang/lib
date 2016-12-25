#include "../apue.h"
#include "../error.c"
#include "./19_2.c"
#include "19_6_loop.c"
#include "19_4_pty_fork.c"
#include "../lib/signal_intr.c"
#include "tty_x.c"
#include "./19_7_driver.c"

#ifdef LINUX
#define OPTSTR "+d:einv"
#else
#define OPTSTR "d:einv"
#endif

static void set_noecho(int);
void do_driver(char *);
void loop(int,int);

int main(int argc,char *argv[]){
  
  int fdm,c,ignoreof,interactive,noecho,verbose;
  pid_t pid;
  char *driver;
  char slave_name[20];
  struct termios orig_termios;
  struct winsize size;
  
  interactive=isatty(STDIN_FILENO);
  ignoreof=0;
  noecho=0;
  verbose=0;
  driver=NULL;
  
  opterr=0;
  while((c=getopt(argc,argv,OPTSTR))!=EOF){
    switch(c){
    case 'd':
      //printf("in d\n");
      driver=optarg;
      break;
    case 'e':
      noecho=1;
      break;
    case 'i':
      //printf("in i\n");
     ignoreof=1;
      break;
    case 'n':
      interactive=0;
      break;
    case 'v':
      verbose=1;
      break;
    case '?':
      err_quit("option :-%c",optopt);
    }
  }
  //printf("%d,%d\n",optind,argc);
  //The variable optind is the index of the next element to be processed in argv

  if(optind>=argc)
    err_quit("usage:pty[-d driver -einv] program [arg ...]"  );
  
  if(interactive){
    //printf("in interactive\n");
    if(tcgetattr(STDIN_FILENO,&orig_termios)<0)
      err_sys("tcgetattr err on stdin");
    if(ioctl(STDIN_FILENO,TIOCGWINSZ,(char *)&size)<0)
      err_sys("tiocwins error");
    pid=pty_fork(&fdm,slave_name,sizeof(slave_name),&orig_termios,&size);
  }else{
    pid=pty_fork(&fdm,slave_name,sizeof(slave_name),NULL,NULL);
  }
  
  if(pid<0){
    err_sys("fork err");
  }else if(pid==0){
    if(noecho)
      set_noecho(STDIN_FILENO);
    printf("%d,argv:%s\n",optind,argv[optind]);
    if(execvp(argv[optind],&argv[optind])<0)
      err_sys("cant execute:%s",argv[optind]);
  }

  if(verbose){
    fprintf(stderr,"version:slave name=%s\n",slave_name);
    if(driver!=NULL)
      fprintf(stderr,"version:driver =%s\n",driver);
  }
  
  if(interactive&&driver==NULL){
    if(tty_raw(STDIN_FILENO)<0)
      err_sys("tty_raw error");
    if(atexit(tty_aexit)<0)
      err_sys("aexit error");
  }

  if(driver)
       do_driver(driver);
  
  loop(fdm,ignoreof);
  exit(0);
}


static void set_noecho(int fd){
  struct termios stermios;
  
  if(tcgetattr(fd,&stermios)<0)
    err_sys("tcgetattr error");
  
  stermios.c_lflag&=~(ECHO|ECHOE|ECHOK|ECHONL);
  
  stermios.c_oflag&=~(ONLCR);
  if(tcsetattr(fd,TCSANOW,&stermios)<0)
    err_sys("tcsetattr error");
}
