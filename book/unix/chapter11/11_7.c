#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
//两个互斥量   深坑 链表根本没实现
#define NHASH 29
#define HASH(fp) (((unsigned long)fp)%NHASH)
struct foo *fh[NHASH];

pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER;

struct foo{
  int f_count;
  pthread_mutex_t f_lock;
  struct foo *f_next;
  int f_id;
};

struct foo *foo_alloc(int id){
  struct foo *fp;
  int idx;

  if((fp=malloc(sizeof(struct foo)))!=NULL){
    fp->f_count=1;
    fp->f_id=id;

    if(pthread_mutex_init(&fp->f_lock,NULL)!=0){
      free(fp);
      return(NULL);
    }

    idx=HASH(id);
    pthread_mutex_lock(&hashlock);
    //fp->f_next=fh[idx];
    fh[idx]=fp;

    //printf("f_id=%d\n",fp->f_id);
    pthread_mutex_lock(&fp->f_lock);
    pthread_mutex_unlock(&hashlock);
    
    pthread_mutex_unlock(&fp->f_lock);    
  }

  return(fp);
}

void foo_hold(struct foo *fp){
  
  pthread_mutex_lock(&fp->f_lock);
  fp->f_count++;
  pthread_mutex_unlock(&fp->f_lock);
}

struct foo *foo_find(int id){
  struct foo *fp;
  int idx;
  //printf("foo_find\n");
  idx=HASH(id);
  printf("foo_find idx=%d\n",idx);
  pthread_mutex_lock(&hashlock);
  for(fp=fh[idx];fp!=NULL;fp=fp->f_next){
    printf("foo_find id=%d,fp_count=%d\n",id,fp->f_count);
    if(fp->f_id==id){
      printf("last find id=%d\n",id);
      foo_hold(fp);
      break;
    }
  }
  
  pthread_mutex_unlock(&hashlock);
  return(fp);
}

void foo_rele(struct foo *fp){
  struct foo *tfp;
  int idx;
  
  pthread_mutex_lock(&hashlock);
  if(--fp->f_count==0){
    printf("f_count=1\n");
    
    
    idx=HASH(fp->f_id);
    tfp=fh[idx];
    if(tfp==fp){
      fh[idx]==fp->f_next;
    }else{
      while(tfp->f_next!=fp)
	tfp=tfp->f_next;
      tfp->f_next = fp->f_next;
    }
    
    pthread_mutex_unlock(&fp->f_lock);
    pthread_mutex_destroy(&fp->f_lock);
    free(fp);
  }else{
    fp->f_count--;
    pthread_mutex_unlock(&fp->f_lock);
  }
}


int main(void){
  struct foo *fo;
  struct foo *fo2;
  struct foo *fo_find;
  int a=12;
  
  fo=foo_alloc(a);  
  printf("f_count=%d,f_id=%d\n",fo->f_count,fo->f_id);
  
  foo_hold(fo);
  printf("f_count=%d,f_id=%d\n",fo->f_count,fo->f_id);
  

  foo_rele(fo);
  printf("f_count=%d,f_id=%d\n",fo->f_count,fo->f_id);
  
  fo_find=foo_find(1);
  printf("foo_find f_count=%d,f_id=%d\n",fo_find->f_count,fo_find->f_id);

  printf("----\n");
  int b=13;
  fo2=foo_alloc(b);
  printf("f_count=%d,f_id=%d\n",fo2->f_count,fo2->f_id);

  exit(0);
}
