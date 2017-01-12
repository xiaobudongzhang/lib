#include <stdio.h>
#include <string.h>
#include <stdbool.h>

enum specnum {red,orange,yellow};
const char * colors[]={
  "red","orange","yellow"
};
#define LEN 30

int main(void){
  char choice[10];
  enum specnum color;
  bool color_is_found=false;
  
  puts("enter color");
  while(fgets(choice,6,stdin)!=NULL&&choice[0]!='\n'){
    
    
    for(color=red;color<=yellow;color++){
      if(choice[strlen(choice)-1]=='\n'){
	choice[strlen(choice)-1]='\0';
      }
      
      if(strcmp(choice,colors[color])==0){
	color_is_found=true;
	break;
      }
    }
    
    if(color_is_found)
      switch(color){
      case red:puts("red");break;
      case orange:puts("orange");break;
      default:puts("default");
      }
    color_is_found=false;
    puts("next color");
  }
  
  puts("goodbye");
  return 0;
}
