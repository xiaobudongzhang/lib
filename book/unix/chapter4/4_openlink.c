#include "../apue.h"
#include "../error.c"
#include <fcntl.h>

void main(void){
	if(open("4_2.c",O_CREAT|O_EXCL)<0){
		err_sys("open err");
	}
	
	exit(0);
}
