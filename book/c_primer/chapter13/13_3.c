#include <stdio.h>
#include <stdlib.h>

#define MAX 40
int main(void){
  FILE *fp;
  fp=fopen("./test","r");
  char words[MAX];

  while(fscanf(fp,"%s",words)==1)
	printf(words);
	
  fclose(fp);
  
}
