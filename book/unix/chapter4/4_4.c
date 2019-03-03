#include "../apue.h"
#include "../error.c"

int main(void){
	struct stat statbuf;
	
	if(stat("foo",&statbuf)<0){
		err_sys("stat err");
	}	
	
	if(chmod("foo",(statbuf.st_mode   | S_IXUSR)|S_ISGID)<0){
		err_sys("chmod err for foo");
	}

	if(chmod("bar",S_IRUSR)<0){
		err_sys("chmod err for bar");
	}
}
