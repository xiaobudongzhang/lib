#include <stdio.h>
#include <string.h>
#define SIZE 81
#define LIM 100
#define STOP "quit"
int main(void){
  char input[LIM][SIZE];
  int ct=0;
  
  char *ptt="32";
  
  char *c;
  printf("%p,%d\n",c,*c);

  printf("enter:\n");
  while(ct<LIM&&
	gets(input[ct])!=NULL&&
	strcmp(input[ct],STOP)!=0
	){
    printf("input[ct]:%c\n",input[ct]);
    printf("\n");
    ct++;
  }
  printf("%d string entered\n",ct);
  
  //ar *c;
  //intf("%p,%c\n",*c);
  return(0);
}
