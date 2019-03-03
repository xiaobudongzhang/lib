#include "../apue.h"
#include <pthread.h>
#include "../error.c"

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;
//pthread_atfork case
void prepare(void){
  printf("preare locks...\n");
  pthread_mutex_lock(&lock1);
  pthread_mutex_lock(&lock2);
}

void parent(void){
  printf("parent unlocking locks..\n");
  pthread_mutex_unlock(&lock1);
  pthread_mutex_unlock(&lock2);
}

void child(void){
  printf("child unlocking locks...\n");
  pthread_mutex_unlock(&lock1);
  pthread_mutex_unlock(&lock2);
}

void *thr_fn(void *arg){
  printf("thread started ...\n");
  printf("pid=%d,xcid=%d\n",getpid(),pthread_self());
  pause();
  return(0);
}

int main(void){
  int err;
  pid_t pid;
  pthread_t tid;

  if((err=pthread_atfork(prepare,parent,child))!=0)
    err_exit(err,"cant install fork");

  //err=pthread_create(&tid,NULL,thr_fn,0);
  if(err!=0)
    err_exit(err,"cant create thread");
  sleep(2);
  printf("parent about to fork\n");
  
  pthread_t child,parent;
  if((pid=fork())<0)
    err_quit("fork failed");
  else if(pid==0)
    {
      sleep(10);
      printf("child return from fork\n");
      child=pthread_self();
      //子进程的线程是复制父进程里的副本 所以进程id相同  但不是同一线程
      if(pthread_equal(child,parent)!=0){
	printf("equal!!!!!\n");
      }else{
	printf("not equal\n");
      }
      printf("parent child pid=%d,xcid=%d\n",getpid(),child);
    }
  else
    {
      printf("parent return from fork\n");
      parent=pthread_self();
      printf("parent pid=%d,xcid=%d\n",getpid(),parent);
    }

  //printf("parent pid=%d,xcid=%d\n",getpid(),pthread_self());
  exit(0);
}
