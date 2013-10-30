#include <stdio.h>

#define HELLO

void main(){
#ifdef HELLO
	printf("DEFINE HELLO\n");
#endif
#ifndef HELLO
	printf("HELLO NOT DEFINE\n");
#endif

	printf("hello world!\n");
	return;
}
