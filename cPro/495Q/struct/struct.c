#include <stdio.h>
#include <string.h>

struct boy{
	char name[10];	
	int age;
}boy;

typedef struct girl{
	char name[10];
	int age;
}girl;

int main(int argc, char *argv[]){
	struct boy danny;	
	girl oathy;

	strcpy(danny.name, "danny");
	strcpy(oathy.name, "oathy");

	danny.age = 10;
	oathy.age = 10;

	printf("Boy'name is %s, %d years old\n", danny.name, danny.age);
	printf("Girl'name is %s, %d years old\n", oathy.name, oathy.age);

	return 0;
}
