#include "../apue.h"
#include "../error.c"
#include <dirent.h>


int main(int argc,char *argv[]){
	
	DIR *dp;
	struct dirent *dirp;
	
	if(argc!=2){
		err_sys("less name");
	}
	
	if((dp=opendir(argv[1]))==NULL){
		err_sys("cant't open %s",argv[1]);
	}

	while((dirp=readdir(dp))!=NULL){
		printf("%s\n",dirp->d_name);
	
	}

	closedir(dp);
	exit(0);
	
}
