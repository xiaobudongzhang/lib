#include <stdio.h>
#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS 100

struct book{
  char title[MAXTITL];
  char author[MAXAUTL];
  float value;
};

int main(void){
  struct book lib[MAXBKS];
  int count=0;
  int index;
  
  printf("enter:\n");
  
  while(count<MAXBKS&&gets(lib[count].title)!=NULL&&lib[count].title[0]!='\0'){
    printf("enter author:\n");
    gets(lib[count].author);
    printf("enter value:\n");
    scanf("%f",&lib[count].value);
    while(getchar()!='\n')
      continue;
    count++;
    if(count<MAXBKS)
      printf("enter next title\n");
  }
  
  if(count>0){
    printf("val:\n");
    for(index=0;index<count;index++)
      printf("%s by %s:$%.2f\n",lib[index].title,lib[index].author,lib[index].value);
  }

  return(0);
}
