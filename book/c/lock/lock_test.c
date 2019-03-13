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


  if (fcntl(fd, F_SETLK, &lock) < 0){
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
  if (argc != 2) {
    fprintf(stderr, "usage:%s filename\n");
    exit(1);
  }
  
  if ((fd = open(argv[1], O_RDWR|O_TRUNC, S_IRWXU)) < 1){
    printf("open err");
    exit(1);
  }
  write(fd, "hello", 5);
  
  struct stat buf;
  fstat(fd, &buf);
  printf("st_size:%ld\n", buf.st_size);
  
  
  //lseek(fd, -1, SEEK_END);
  //char *buf2;
  //read(fd, buf2, 1);
  //printf("end_char:%s\n", buf2);

  pid = lock_test(fd, F_WRLCK, 0, SEEK_END, 0);
  
  //lseek(fd, 0,SEEK_END); 
  //write(fd, "5", 1);
  //write(fd, "6", 1);
    //lock_test(fd, F_UNLCK, 0, SEEK_END, 0);
    //ite(fd, "7", 1);

  
  
  

  
  sleep(10000);
}
