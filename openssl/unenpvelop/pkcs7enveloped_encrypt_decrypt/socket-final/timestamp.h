/**
 * FileName : sslTimestamp.h
 * Author	: danny lee
 * Date		: 2013-07-04
 * Brief	: This file define function about timeStamp function to avoid the Resend attack
 */
#include <stdio.h>
#include <string.h>
#include <time.h>

#ifndef __TIMESTAMP_H
#define __TIMESTAMP_H

#define TIMELEN	50

extern char* add_timeStamp(char * str,char *timestamp);
extern time_t get_timeStamp(char * str); 
extern char* remove_timeStamp(char *str);

/**
 * functionName: add_timeStamp
 * @Param	: char * str  Content to send before SSL_write()
 * Brief	: Add timeStamp to the end of the content (char * str) with a prefix flag '#'
 * @return  
 *	Format : char *
 *  str+'#'+timestamp		
 */
char * add_timeStamp(char *str,char *timestamp){
	
	char timestr[TIMELEN];
	char *ret;
	time_t curtime;

	memset(timestr, 0,TIMELEN); 
	//time(&curtime);

	//sprintf(timestr,"#%ld",curtime);
        strcpy(timestr,timestamp);
	ret = (char*)malloc(strlen(timestr) + strlen(str));

	//sprintf(ret,"%s%s",str,timestr);
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

#endif

