#include "../apue.h"
#include "../error.c"
#include <sys/shm.h>


#define ARRAY_SIZE 40000
#define MALLOC_SIZE 100000
#define SHM_SIZE 100000
#define SHM_MODE 0600

//打印各种不同类型的数据存放位置

char array[ARRAY_SIZE];

int main(void){
  int shmid;
  char *ptr,*shmptr;
  
  printf("array[] from %lx to %lx\n",(unsigned long)&array[0],(unsigned long)&array[ARRAY_SIZE]);
  printf("stack around %lx\n",(unsigned long)&shmid);
  
  if((ptr=malloc(MALLOC_SIZE))==NULL)
    err_sys("malloc error");
  printf("malloced from %lx to %lx\n",(unsigned long)ptr,(unsigned long)ptr+MALLOC_SIZE);
  
  if((shmid=shmget(IPC_PRIVATE,SHM_SIZE,SHM_MODE))<0)
    err_sys("shmget_error");
  if((shmptr=shmat(shmid,0,0))==(void *)-1)
    err_sys("shmat error");
  
  printf("shared memory attached from %lx to %lx\n",(unsigned long)shmptr,(unsigned long)shmptr+SHM_SIZE);
  
  if(shmctl(shmid,IPC_RMID,0)<0)
    err_sys("shmctl err");
  exit(0);
}
