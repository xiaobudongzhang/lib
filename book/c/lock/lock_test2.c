#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

pid_t lock_test(int fd, int type, off_t offset, int whence, off_t len)
{
  struct flock lock;

  lock.l_type = type;/* F_RDLCK or F_WRLCK */
  lock.l_start = offset;/* byte offset, relative to l_whence */
  lock.l_whence = whence;/* SEEK_SET, SEEK_CUR, SEEK_END */
  lock.l_len = len;/* #bytes (0 means to EOF) */

  

  printf("l_type:%d\n", lock.l_type);
  printf("l_start:%d\n", lock.l_start);
  printf("l_whence:%d\n", lock.l_whence);
  printf("l_len:%d\n", lock.l_len);


  if (fcntl(fd, F_GETLK, &lock) < 0){
    printf("fcntl error");
    exit(1);
  }


  printf("--------\n");

  printf("l_type:%d\n", lock.l_type);
  printf("l_start:%d\n", lock.l_start);
  printf("l_whence:%d\n", lock.l_whence);
  printf("l_len:%d\n", lock.l_len);

  if (lock.l_type == F_UNLCK) {
	return(0);
  }
  /* false, region isn't locked by another proc */
  return(lock.l_pid);/* true, return pid of lock owner */
}


int main(int argc, char *argv[]){
	
  int fd;
  pid_t pid;
  int cres;
  if (argc != 3) {
    fprintf(stderr, "usage:%s filename\n");
    exit(1);
  }
  
  if ((fd = open(argv[1], O_RDWR|O_CREAT, S_IRWXU)) < 1){
    printf("open err");
    exit(1);
  }
  int start;
  start = atoi(argv[2]);
  pid = lock_test(fd, F_WRLCK, start, SEEK_SET,  1);
  
  printf("pid:%d\n", pid);
  
  
  //sleep(10000);
  //lseek(fd, 7, SEEK_SET);
  //char *buf;
  //read(fd, buf, 1);
  //printf("buf:%s\n", buf);
}
