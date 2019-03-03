#include <stdio.h>

int main(void){

#if defined(BSD)
printf("in bsd\n");
#endif
	return(0);
}
