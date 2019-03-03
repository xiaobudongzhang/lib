#include <stdio.h>

int main(void){
  char *mesg="Hello w";
  char *copy;
  
  copy=mesg;
  printf("%s\n",copy);
  printf("mesg=%s,&mesg=%p,value=%p\n",
	 mesg,&mesg,mesg);
  printf("copy=%s,&copy=%p,copy=%p\n",
          copy,&copy,copy);
  return(0);
}
