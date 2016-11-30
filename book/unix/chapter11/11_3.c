#include "../apue.h"
#include "../error.c"
#include <pthread.h>
//pthread_exit 参数使用错误

struct foo{
  int a,b,c,d;
};

void printfoo(const char *s,const struct foo *fp){

  printf(s);
  printf("struct at 0x%x\n",(unsigned*)fp);
  printf("foo.a=%d\n",fp->a);
  printf("foo.b=%d\n",fp->b);
  printf("foo.c=%d\n",fp->c);
  printf("foo.d=%d\n",fp->d);
}
void *thr_fn1(void *arg){
  
  struct foo foo={1,2,3,4};
  printfoo("thread 1:\n",&foo);
  pthread_exit((void*)&foo);
}

void *thr_fn2(void *arg){
  
  printf("thread 2 id is %d\n",pthread_self());
  pthread_exit((void*)0);
}

int main(void){

  int err;
  pthread_t tid1,tid2;
  struct foo *fp;
  
  
  err=pthread_create(&tid1,NULL,thr_fn1,NULL);
  if(err!=0)
    err_quit("cant create thread 1:%s\n",strerror(err));  
  err=pthread_join(tid1,(void *)&fp);
  sleep(3);
  

  if(err!=0)
    err_quit("cant join with thread 1:%s\n",strerror(err));
  sleep(1);
  
  sleep(3);
  printf("start second pthread\n");
  err=pthread_create(&tid2,NULL,thr_fn2,NULL);
  if(err!=0)
     err_quit("cant create thread 2:%s\n",strerror(err));
  sleep(1);
 
  printfoo("parent:\n",fp);
  exit(0);
}
