#include "../apue.h"
#include "../error.c"
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
pthread_mutex_t mutex,mutex2;

struct to_info{
 
  void (*to_fn)(void *);//function
  void *to_arg;
  struct timespec to_wait;

};

//使用递归互斥量
int makethread(void *(*fn)(void *),void *arg){

  int err;
  pthread_t tid;
  pthread_attr_t attr;

  err=pthread_attr_init(&attr);

  if(err!=0)
    return(err);

  err = pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
  //if(err==0)
  //err=pthread_create(&tid,&attr,fn,arg);
  //sleep(1);

  struct to_info *tp;
  tp = (struct to_info *)arg;
  printf("sleepbefore2\n");
  printf("%d\n",tp->to_wait.tv_sec);
  nanosleep(&tp->to_wait,NULL);
  
  if(err==0)
        err=pthread_create(&tid,&attr,fn,arg);
   sleep(1);

  pthread_attr_destroy(&attr);
  return(err);
}


/**struct to_info{

  void (*to_fn)(void *);//function
  void *to_arg;
  struct timespec to_wait;

};
*/
#define SECTONSEC 1000000000 
#define USECTONSEC 1000


void * timeout_helper(void *arg){
  struct to_info *tip;
  
  printf("in timeout_helper\n");
  tip = (struct to_info *)arg;
  
  //printf("sleepbefore\n");
  
  printf("%d\n",tip->to_wait.tv_sec);
  //nanosleep(&tip->to_wait,NULL);
  //  sleep(19);
  //printf("sleepafter\n");
  
  FILE *fp;
  fp=fopen("tmp2","wb+");
  int tx=444;
  char buf[]="sss";
  if(fp!=NULL){
    fwrite(buf,sizeof(buf),0,fp);
  }



  (*tip->to_fn)(tip->to_arg);
  return(0);
}

void timeout(const struct timespec *when,void(*func)(void *),void *arg){
  struct timespec now;
  struct timeval tv;
  struct to_info *tip;
  int err;
  //printf("pre pre timeout\n");
  gettimeofday(&tv,NULL);
  now.tv_sec=tv.tv_sec;
  now.tv_nsec=tv.tv_usec*USECTONSEC;
  //timeout?
  if((when->tv_sec > now.tv_sec)||(when->tv_sec==now.tv_sec&&when->tv_nsec>now.tv_nsec)){
    tip=malloc(sizeof(struct to_info));
    
    //printf("pre timeout\n");
    if(tip!=NULL){
      tip->to_fn=func;
      tip->to_arg=arg;
      tip->to_wait.tv_sec=when->tv_sec-now.tv_sec;
      
      //printf("when->tv_sec%d,now.tv_sec=%d\n",when->tv_sec,now.tv_sec);
      if(when->tv_nsec>=now.tv_nsec){
	tip->to_wait.tv_nsec=when->tv_nsec-now.tv_nsec;
      }else{
	tip->to_wait.tv_sec--;
	tip->to_wait.tv_nsec=SECTONSEC-now.tv_nsec+when->tv_nsec;
      }
      //printf("tip%d\n", tip->to_wait.tv_sec);
      err=makethread(timeout_helper,(void*)tip);
      if(err==0)
	return;
    }
  }

}

pthread_mutexattr_t attr;
//pthread_mutex_t mutex;

void retry(void *arg){
  printf("retry %d\n",arg);
  //  sleep(3);
  //pause();
  printf("retry end\n");
  int lock;
  //不要用同一变量  否则死锁
  //pthread_mutex_unlock(&mutex);
  pthread_mutex_lock(&mutex2);
  
  printf("retry --%d\n",lock);
  FILE *fp;
  fp=fopen("tmp","wb+");
  if(fp!=NULL){
    fwrite(arg,sizeof(arg),0,fp);
  }
  pthread_mutex_unlock(&mutex2);
  
  printf("retry eeeee\n");
}

int main(void){
  int err,condition,arg;
  struct timespec when;
  struct timeval tv;
  
  if((err=pthread_mutexattr_init(&attr))!=0)
    err_exit(err,"pthread_mutexattr_init failed");
  if((err=pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE))!=0)
    err_exit(err,"cant set recursive");
  
  if((err=pthread_mutex_init(&mutex,&attr))!=0)
    err_exit(err,"cant create recusive");
  
  condition=1;
  pthread_mutex_lock(&mutex);
  
  //pthread_mutex_lock(&mutex);
  if(condition){
    //printf("condition\n");
    
    struct timespec now;
    gettimeofday(&tv,NULL);
    when.tv_sec=tv.tv_sec+5;//二十秒
    
    arg=11;
    timeout(&when,retry,(void *)(unsigned long)arg);
  }
  
  //pthread_mutex_unlock(&mutex);
  pthread_mutex_unlock(&mutex);
  exit(0);
}
