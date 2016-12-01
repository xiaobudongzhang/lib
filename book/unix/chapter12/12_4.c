#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
extern char **environ;
//pthread_once_t   0 函数执行 1等待 2函数不执行
pthread_mutex_t env_mutex;
static pthread_once_t init_done =  PTHREAD_ONCE_INIT;

static void thread_init(void){
  printf("thread_init\n");
  pthread_mutexattr_t attr;
  pthread_mutexattr_init(&attr);
  pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE);
  pthread_mutex_init(&env_mutex,&attr);
  pthread_mutexattr_destroy(&attr);
}

int getenv2(const char *name,char *buf,int buflen){

  int i,len,olen;
  
  pthread_once(&init_done,thread_init);
  len=strlen(name);
  pthread_mutex_lock(&env_mutex);
  for(i=0;environ[i]!=NULL;i++){
    if((strncmp(name,environ[i],len))==0&&(environ[i][len]=='=')){
      printf("---%s\n",environ[i]);
	olen=strlen(&environ[i][len+1]);
	printf("---%d\n",buflen);
	if(olen>=buflen){
	  	  pthread_mutex_unlock(&env_mutex);
	  return(ENOSPC);
	}
	strcpy(buf,&environ[i][len+1]);
	pthread_mutex_unlock(&env_mutex);
	return(0);
      }
  }
  pthread_mutex_unlock(&env_mutex);
    return(0);
}
pthread_t tid1, tid2;


void *thread_fun1(void *arg){
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  char name[]="PATH";
  char buf[800];
  getenv2(name,buf,200);
  printf("value=%s\n",buf);

}

int main(void){

  
  int err;

  err = pthread_create(&tid1, NULL, thread_fun1, NULL);
  if(err != 0)
  {
      printf("create new thread 1 failed\n");
      return ;
  }
  err = pthread_create(&tid2, NULL, thread_fun1, NULL);
  if(err != 0)
  {
      printf("create new thread 1 failed\n");
      return ;
  }

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  exit(0);
}
