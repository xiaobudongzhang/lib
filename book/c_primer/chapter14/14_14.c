#include <stdio.h>
#include <stdlib.h>
#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS 3
//fwite and fread about struct case
struct book {
  char title[MAXTITL];
  char author[MAXAUTL];
  float value;
};

int main(void){
  struct book lib[MAXBKS];
  int count=0;
  int index,filecount;
  FILE *pbooks;
  int size=sizeof(struct book);
  
  if((pbooks=fopen("book.dat","a+b"))==NULL){
    fputs("cant open\n",stderr);
    exit(1);
  }
  
  rewind(pbooks);
  while(count<MAXBKS&&fread(&lib[count],size,1,pbooks)==1){
    if(count==0)
      puts("content:");
    printf("%s by %s:$%.2\n",lib[count].title,lib[count].author,lib[count].value);
    count++;
  }

  filecount=count;
  if(count==MAXBKS){
    fputs("book.dat is full",stderr);
    exit(2);
  }

  puts("enter content:");
  while(count<MAXBKS&&fgets(lib[count].title,sizeof(lib[count].title),stdin)!=NULL&&lib[count].title[0]!='\n'){
    puts("author:");
    fgets(lib[count].author,sizeof(lib[count].author),stdin);
    puts("value:");
    scanf("%f",&lib[count].value);
    count++;
    while(getchar()!='\n')
      continue;
    if(count<MAXBKS)
      puts("enter tile");
  }
  
  if(count>0){
    puts("here is books");
    for(index=0;index<count;index++)
      printf("%s by %s:$%.2f\n",lib[index].title,lib[index].author,lib[index].value);
    fwrite(&lib[filecount],size,count-filecount,pbooks);
  }

  puts("bye\n");
  fclose(pbooks);
  return 0;
}
