#include "../apue.h"
#include "../error.c"
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
static jmp_buf env_alrm;

//模拟sleep
unsigned int sleep2(unsigned int);
static void sig_int(int);

int main(void){
  unsigned int unslept;
  
  if(signal(SIGINT,sig_int)==SIG_ERR){
    err_sys("sign2l sigint err");
  }

  unslept=sleep2(1);
  printf("sleep2 return %u\n",unslept);
  exit(0);
}

static void sig_int(int signo){
  int i,j;
  volatile int k;
  
  printf("\nsig_int starting\n");
  for(i=0;i<60;i++)
    for(j=0;j<40000;j++)
      {
	k+=i+j;
	printf("i=%d\n",i);
	//	printf("j=%d\n",j);
      }
  
  printf("sig_int finished\n");


}

static void sig_alrm(int signo){
  printf("sig_alrm\n");
  
  longjmp(env_alrm,1);

}

unsigned int sleep2(unsigned int nsecs){

  if(signal(SIGALRM,sig_alrm)==SIG_ERR)
    return (nsecs);

  if(setjmp(env_alrm)==0){
    printf("setjmp\n");
    alarm(nsecs);
    pause();
    
  }

  printf("setjmpafter\n");

  return (alarm(0));
}
