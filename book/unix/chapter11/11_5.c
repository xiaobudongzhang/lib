#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

//互斥量
struct foo{
  int f_count;
  pthread_mutex_t f_lock;
};

struct foo *foo_alloc(void){
  struct foo *fp;
  
  if((fp=malloc(sizeof(struct foo)))!=NULL){
    fp->f_count=1;
    if(pthread_mutex_init(&fp->f_lock,NULL)!=0){
      free(fp);
      return(NULL);
    }
  }
  
  return(fp);
}

void foo_hold(struct foo *fp){
  
  pthread_mutex_lock(&fp->f_lock);
  fp->f_count++;
  pthread_mutex_unlock(&fp->f_lock);
}

void foo_rele(struct foo *fp){

  pthread_mutex_lock(&fp->f_lock);
  if(--fp->f_count==0){
    pthread_mutex_unlock(&fp->f_lock);
    pthread_mutex_destroy(&fp->f_lock);
    free(fp);
  }else{
    pthread_mutex_unlock(&fp->f_lock);
  }
}


int main(void){
  struct foo *fo;
  fo=foo_alloc();
  foo_hold(fo);
  foo_rele(fo);
  foo_rele(fo);

  printf("f_count=%d\n",fo->f_count);
  
  exit(0);
}
