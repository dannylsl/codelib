/**
 * \file sockfile.h
 * \brief
 *		Socket Operation Data&file send with info
 */
#ifndef __SOCKFILE_H
#define  __SOCKFILE_H

#include  <sys/stat.h>

#define BUFSIZE		1024
#define INFOSIZE	64

/**
 * \fn infoInit(char *info,const char ch,int len)
 * \param char* info		[ char array to initialize	]
 * \param const char ch	[ initialize info with ch	]
 * \param int len			[ initial length of info	]
 * \brief 
 *		initialize info with ch letter by letter
 * \return null
 */
extern void infoInit(char *info,const char ch,int len);

/**
 * \fn infoDeal(const char* filename,char * Info)
 * \param	const char* filename	[ the name of the file which is to create Info ]
 * \param char* Info				[ store the fileInfo 	]
 * \brief 
 *		use filename to create fileInfo and store it in [Param]Info \n
 *		The fileInfo format as below \n
 *		"#filename$filesize###(repeat #)" the string length is 64
 * \return 
 *		The return value is 0 \n
 *		and the created fileInfo store in [Param]Info
 */
extern int infoDeal(const char* filename,char * Info);

/**
 * \fn dataInfoDeal(int datalen,char * Info)
 * \param int datalen			[ data length to create dataInfo		]
 * \param char* Info			[ dataInfo 64bytes, filled with '#'		]
 * \brief 
 *		DataInfo pre-deal before send
 * \return 
 *		return 0 without error check
 */
extern int dataInfoDeal(int datalen,char * Info);

/**
 * \fn sendInfo(int sockfd,char * fileInfo)
 * \param int sockfd			[ socket file descriptor	]
 * \param char* fileInfo		[ fileInfo to send			]
 * \brief  
 *		send fileInfo through sockfd
 * \return 
 *		if send successfully, return 0 \n
 *		else return -1
 */
extern int sendInfo(int sockfd,char * fileInfo);

/**
 * \fn recvInfo(int sockfd, char *fileInfo)
 * \param int sockfd			[ socket file descriptor	]
 * \param char*	fileInfo	[ fileInfo to recv	]
 * \brief  
 *		receive fileInfo from socket and store it in [Param]fileInfo
 * \return 
 *		if recvInfo successfully, return 0 \n
 *		else return -1
 */
extern int recvInfo(int sockfd, char *fileInfo);

/**
 * \fn infoRmEnd(char *fileInfo,int len)
 * \param char *fileInfo		[ fileInfo to deal with			]
 * \param int len				[ the length of the fileInfo	]
 * \brief 
 *		remove '#' at end from [Param]fileInfo
 * \return null
 */
extern void infoRmEnd(char *fileInfo,int len);

/**
 * \fn infoParse(char* fileInfo,char * filename,int * filesize)
 * \param char *fileInfo			[ fileInfo to parse				]
 * \param char *fileInfo			[ filename parsed from fileInfo	]
 * \param int *filesize			[ filesize parsed from fileInfo	]
 * \brief 
 *		Parse [Param]fileInfo and extract filename and filesize \n
 *		and store them into [Param]filename and [Param]filesize 
 * \return 
 *		no error check, return 0 
 */
extern int infoParse(char* fileInfo,char * filename,int * filesize);

/**
 * \fn sendfile(int sockfd, const char * filename)
 * \param int sockfd			[ socket file descriptor		]
 * \param const char*filename	[ name of the file to send		]
 * \brief
 *		send the file with the [Param]filename through the sockfd		
 * \return 
 *		return  0 when failed to open file \n
 *		return -1 when some errors happen in send \n
 *		return  1 send file successfully
 */
extern ssize_t sendfile(int sockfd, const char * filename);

/**
 * functionName : recvfile(int sockfd,const char * filename,int filesize)
 * \param	int sockfd				[ socket file descriptor			]
 * \param const char* filename	[ the name of the file to receive	]
 * \param int filesize			[ the size of the file to receive	]
 * \brief 
 *		receive file named [Param]filename and with a size = [Param]filesize  through sockfd
 * \return 
 */
extern ssize_t recvfile(int sockfd,const char * filename,int filesize);

/**
 * \fn sendData(int sockfd,const char* data,int datalen)
 * \param	int sockfd				[ socket file descriptor		]
 * \param const char* data		[ data to send					]
 * \param int datalen				[ the lenght of data to send 	]
 * \brief 
 *		send data through sockfd \n
 *		this function will send a DataInfo before sending data \n
 *		[Param]datalen is recommanded <= 4096 to decrease the memory consumption
 * \return 
 *		return the length sent, and if some errors happened, \n
 *		the process will exit with EXIT_FAILURE
 */
extern ssize_t sendData(int sockfd,const char* data,int datalen);

/**
 * \fn recvData(int sockfd,char *dataStore)
 * \param	int sockfd		[ socket file descriptor	]
 * \param int dataStore	[ The pointer to store the received data, u need malloc enough space before using 	]
 * \brief  
 *		receive data through sockfd \n
 *		this function will receive a DataInfo before receiving data \n
 *		and Parse the DataInfo to create proper buffer to receive data
 * \return 
 *		return the length received, and if some errors happened, \n
 *		the process will exit with EXIT_FAILURE
 */
extern int recvData(int sockfd,char *dataStore);

/**
 * \fn addSocketfdToFileName(char *filename,int sockfd)
 * \param	char *filename	[ the filename						]
 * \param int dataStore	[ the sockfd to add into filename 	]
 * \brief
 *		adding sockfd(int) to filename \n
 *		for example: [a.txt] => addSocketfdToFileName("a.txt",1) =>[a1.txt]
 * \return 
 *		return -1 if the sockfd is invalid \n
 *		return 0 if it runs well
 */
extern int addSocketfdToFileName(char *filename,int sockfd);

/**
 * \fn sendTimestamptoClient (int sockfd,char * timestamp)
 * \param	int sockfd		[ the socket file descriptor	]
 * \param char* timestamp [ the timestamp	@server[12bytes]]  
 * \brief 
 *		sending timestamp through sockfd \n	
 *		we using this timestamp to avoid re-sent attacks
 * \return null
 */
extern void sendTimestamptoClient(int sockfd,char * timestamp);

/**
 * \fn createTimeStamp()
 * \brief
 *		create a 12byte timestamp,start with '#' and end with '\0'
 * \return char* 
 *		return the timeStamp [12 bytes] \n
 *		EG:#1234567890
 */
extern char * createTimeStamp();

#endif
