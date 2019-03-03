#include <stdio.h>
#include <string.h>
#define SIZE 81
#define LIM 5
#define HALT " "
void stsrt(char *strings[],int num);

int main(void){
  char input[LIM][SIZE];
  char *ptstr[LIM];
  int ct=0;
  int k;
  
  while(ct<LIM&&fgets(input[ct],SIZE,stdin)!=NULL){
    ptstr[ct]=input[ct];
    ct++;
  }
  
  stsrt(ptstr,ct);
  printf("after sort\n");
  for(k=0;k<ct;k++){
    fputs(ptstr[k],stdout);
  }
  return(0);
}

void stsrt(char *strings[],int num){
  char *temp;
  int top,seek;
  
  for(top=0;top<num-1;top++)
    for(seek=top+1;seek<num;seek++)
      if(strcmp(strings[top],strings[seek])>0){
      
	temp=strings[top];
	strings[top]=strings[seek];
	strings[seek]=temp;
      }

}
