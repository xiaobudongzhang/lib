#include "../apue.h"
#include "../error.c"
#include <fcntl.h>

void set_f1(int fd,int flags){
	int val;
	
	if((val=fcntl(fd,F_GETFL,0))<0){
		err_sys("fcntl error");
	}

	val |=flags;

	if(fcntl(fd,F_SETFL,val)<0){
		err_sys("fcntl set error");
	}
}
