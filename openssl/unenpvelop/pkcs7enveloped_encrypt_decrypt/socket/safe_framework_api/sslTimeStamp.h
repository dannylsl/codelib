/**
 * \file sslTimeStamp.h
 * \brief
 *		time stamp operation	
 */
#ifndef __SSLTIMESTAMP_H
#define __SSLTIMESTAMP_H

#include <stdio.h>
#include <string.h>
#include <time.h>

#define TIMELEN	50

/**
 * \fn add_timeStamp(char * str)
 * \param char * str  Content to send before SSL_write()
 * \brief Add timeStamp to the end of the content (char * str) with a prefix flag '#'
 * \return 
 *	Format : char *
 *  str+'#'+timestamp		
 */
extern char* add_timeStamp(char * str);

/**
 * \fn get_timeStamp(char * str)
 * \param received content by using SSL_read()  
 * \brief get the timeStamp from the received content
 * \return  
 *	Format : time_t(long)
 *  timestamp		
 */
extern time_t get_timeStamp(char * str); 

/**
 * \fn remove_timeStamp(char *str)
 * \param received content by using SSL_read()
 * \brief remove timeStamp from content and reover content to raw data
 * \return
 *	Format : char *
 *	raw data
 */
extern char* remove_timeStamp(char *str);

#endif
