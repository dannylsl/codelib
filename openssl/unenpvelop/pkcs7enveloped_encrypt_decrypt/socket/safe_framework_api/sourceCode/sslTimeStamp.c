//#include "sslTimeStamp.h"

char * add_timeStamp(char *str){
	
	char timestr[TIMELEN];
	char *ret;
	time_t curtime;

	memset(timestr, 0,TIMELEN); 
	time(&curtime);

	sprintf(timestr,"#%ld",curtime);
	ret = (char*)malloc(strlen(timestr) + strlen(str));

	sprintf(ret,"%s%s",str,timestr);

	return ret;
}

/**
 * functionName: get_timeStamp
 * @Param	: received content by using SSL_read()  
 * Brief	: get the timeStamp from the received content
 * @return  
 *	Format : time_t(long)
 *  timestamp		
 */
time_t get_timeStamp(char*str){

	time_t timestamp;
	char timestr[TIMELEN];				
	char *p = strrchr(str,'#');

	memset(timestr, 0, TIMELEN);
//	printf("%s\n",p+1);
	strcpy(timestr,p+1);
//	printf("%s\n",timestr);
		
	timestamp = (time_t)atol(timestr);
	return timestamp;
}

/**
 * function Name: remove_timeStamp
 * @Param: received content by using SSL_read()
 * Breif : remove timeStamp from content and reover content to raw data
 * @return
 *	Format : char *
 *	raw data
 */
char * remove_timeStamp(char *str){
				
	char *ret;
	int strlength,stamplen;

	strlength = strlen(str);
	stamplen = strlen(strrchr(str,'#'));

	ret = (char*)malloc(strlength - stamplen + 1);
	memset(ret,0,strlength - stamplen + 1);

	strncpy(ret,str,(strlength - stamplen));
		
	return ret;
}


