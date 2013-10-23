#include <stdlib.h>
#include <stdio.h>
#include <time.h> 

void main ()
{
	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	printf ( "\007The current date/time is: %s", asctime (timeinfo) );

	printf("year=%d month=%d day=%d hour=%d min=%d sec=%d\n",timeinfo->tm_year+1900,timeinfo->tm_mon,timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
	exit(0);
}
