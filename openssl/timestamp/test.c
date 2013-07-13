#include <stdio.h>
#include <time.h> 
#include <sys/time.h>
#include "sslTimeStamp.h"

void main ()
{
	char str[] = "Hello World!";
	char *deltStr = add_timeStamp(str); 
	char *recover;

	printf("source:%s\ndelt:%s\n",str,deltStr);
	printf("timeStamp:%ld\n",get_timeStamp(deltStr));
	recover = remove_timeStamp(deltStr);
	printf("Recover:%s\n",recover);

	exit(0);
}
