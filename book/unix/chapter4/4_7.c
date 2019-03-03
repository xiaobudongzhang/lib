#include "../apue.h"
#include "../error.c"
//#include "../chapter2/2_2.c"
#include <limits.h>
#include <dirent.h>
//遍历获取目录下文件类型的数量
typedef int Myfunc(const char *,const struct stat * ,int);
static Myfunc myfunc;
static int myftw(char *,Myfunc *);
static dopath(Myfunc *);

static long nreg,ndir,nblk,nchr,nfifo,nslink,nsock,ntot;
#include <linux/limits.h>
//分配文件内存  简单的分配最大值内存
#ifdef PATH_MAX
static int pathmax= PATH_MAX;
#else
static int pathmax = 0;
#endif

#define SUSV3 200112L

static long posix_version = 0;

#define PATH_MAX_GUESS 1024

char * path_alloc(int *sizep){
  char *ptr;
  int size;
  //printf("::%d\n",sizep);
  if(posix_version==0){
    posix_version=sysconf(_SC_VERSION);
  }
  if(pathmax==0){
    errno=0;
    if((pathmax=pathconf("/",_PC_PATH_MAX))<0){
      if(errno == 0)
        pathmax = PATH_MAX_GUESS;
      else
        err_sys("pathconf err");
    }else{
      pathmax++;
    }
  }

  if(posix_version<SUSV3)
    size=pathmax+1;
  else
    size = pathmax;

  if((ptr=malloc(size))==NULL)
    err_sys("malloc err");

  //printf("size=%d\n",size);

  if(sizep != NULL)
    *sizep=size;
  //printf("sizep:%d\n",sizep);
  //printf("ptr=%p\n",&ptr);
  //printf("ptr=%s\n",ptr);
  return(ptr);

}

int main(int argc,char *argv[]){
  int ret;
  if(argc!=2){
    err_quit("usage:need more arg");
  }
  ret= myftw(argv[1],myfunc);
  ntot=nreg+ndir+nblk+nchr+nfifo+nslink+nsock;
  //printf("num::%d,%d\n",nreg,nto/printf("num::%d,%d\n",nreg,ntott);
  if(ntot==0)
    ntot=1;
  //printf("num::%d,%d\n",nreg,ntot);
  printf("file percent:%5.4f%%\n",((float)nreg/ntot)*100);
  exit(ret);
}



#define FTW_F 1 //file
#define FTW_D 2 //dir
#define FTW_DNR 3 //dir & can't read
#define FTW_NS 4 //file & cant stat

static char *fullpath;

static int myftw(char *pathname,Myfunc *func){
  int len;
  fullpath=path_alloc(&len);
  
  strncpy(fullpath,pathname,len);
  fullpath[len-1]=0;
  printf("myftw fullath:%s\n",fullpath);//return;
  return (dopath(func));


}


static int dopath(Myfunc *func){
  struct stat statbuf;
  struct dirent *dirp;
  DIR *dp;
  int ret;
  char *ptr;
  
  if(lstat(fullpath,&statbuf)<0)
    return (func(fullpath,&statbuf,FTW_NS));
  
  if(S_ISDIR(statbuf.st_mode)==0)//not  dir
    return(func(fullpath,&statbuf,FTW_F));
  if((ret=func(fullpath,&statbuf,FTW_D))!=0){
    return (ret);
  }

  ptr=fullpath+strlen(fullpath);
  *ptr++='/';
  *ptr=0;
  //printf("fullpath:%s\n",fullpath);
  if((dp=opendir(fullpath))==NULL)
    return (func(fullpath,&statbuf,FTW_DNR));

  while((dirp=readdir(dp))!=NULL){
    if(strcmp(dirp->d_name,".")==0||strcmp(dirp->d_name,"..")==0)
      continue;
    printf("d_name:%s\n",dirp->d_name);
    strcpy(ptr,dirp->d_name);
    //return;
    if((ret=dopath(func))!=0)
      break;
  }

  ptr[-1]=0;
  if(closedir(dp)<0)
    err_ret("close fail%s",fullpath);

  return (ret);
}

static int myfunc(const char *pathname,const struct stat *statptr,int type){
  switch(type){
  case FTW_F:
    switch(statptr->st_mode&S_IFMT){
    case S_IFREG:nreg++;break;
    case S_IFBLK:nblk++;break;
    case S_IFCHR:nchr++;break;
    case S_IFIFO:nfifo++;break;
    case S_IFLNK:nslink++;break;
    case S_IFSOCK:nsock++;break;
    case S_IFDIR:
      err_dump("s_ifdir err :%s",pathname);
      ;
      
    }
    break;
  case FTW_D:
    ndir++;
    break;
    
  case FTW_DNR:
    err_ret("cant read dir %s",pathname);

  case FTW_NS:
    err_ret("stat err %s",pathname);
    break;
  default:
    err_dump("unknow type %d for pathname %s",type,pathname);
  }
  return(0);
}

