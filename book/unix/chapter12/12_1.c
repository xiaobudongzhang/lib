#include "../apue.h"
#include "../error.c"
#include <pthread.h>
//分离线程
int makethread(void *(*fn)(void *),void *arg){

  int err;
  pthread_t tid;
  pthread_attr_t attr;
  
  err=pthread_attr_init(&attr);
  
  if(err!=0)
    return(err);
  
  printf("start\n");
  err = pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
  if(err==0)
    err=pthread_create(&tid,&attr,fn,arg);
  sleep(1);
  //防止函数还没调用就结束创建
  printf("pthread end\n");
  pthread_attr_destroy(&attr);
  return(err);
}

pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER;

void *thr_fn1(void *arg){
  printf("thr_fn start\n"); 
  //struct foo foo={1,2,3,4};
  pthread_cond_t qready=PTHREAD_COND_INITIALIZER;
  pthread_mutex_lock(&hashlock);
  sleep(3);//为什么一有第二个sleep就停止了   我猜测是因为sleep时 没有使用空间  所以创建函数就把地址清空 创建结束
  pthread_cond_wait(&qready,&hashlock);
  pthread_mutex_unlock(&hashlock);
  printf("thr_fn start end\n");
  return;
  int i,j,z;
  for(i=0;i<30;i++)
    for(j=0;j<100000;j++)
      {
	z=i+j;
	printf("i=%d,j=%d,z=%d\n",i,j,z);
      }
 
  //sleep(10);
  
  FILE *fp;
  fp=fopen("tmp","wb+");
  if(fp!=NULL){
        fwrite(arg,sizeof(arg),0,fp);
  }else{
    printf("thr err\n");
  }

  printf("thr_fn1\n");
  //pthread_exit((void*)&foo);
 
  
  pthread_exit(0);
}


int main(void){

  int errno;
  errno=makethread(thr_fn1,NULL);
  printf("errno=%d\n",errno);
  //sleep(20);
  exit(0);
}
