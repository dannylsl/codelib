#include <stdio.h>

#define HELLO1

void main(){
#ifdef HELLO
	printf("DEFINE HELLO\n");
#endif
	printf("hello world!\n");
	return;
}
