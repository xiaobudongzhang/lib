static int pfd1[2],pfd2[2];

void TELL_WAIT(void){
  if(pipe(pfd1)<0||pipe(pfd2)<0)
    err_sys("pipe err");

}

void TELL_PARENT(pid_t pid){
  if(write(pfd2[1],'c',1)!=1)
    err_sys("tell parent err");

}

void WAIT_PARENT(void){
  char c;
  if(read(pfd1[0],&c,1)!=1)
    err_sys("wait parent err");
  if(c!='p')
    err_quit("wait parent err data");
}

void TELL_CHILD(pid_t pid){
  if(write(pfd[1],"p",1)!=1)
    err_sys("tell child err");
}

void WAIT_CHILD(void){
  char c;
  if(read(pfd2[0],&c,1)!=1)
    err_sys("wait child err");
  if(c!='c')
    err_quit("wait child err data");
}
