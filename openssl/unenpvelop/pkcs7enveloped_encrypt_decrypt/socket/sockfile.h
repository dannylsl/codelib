#include  <sys/stat.h>

#define BUFSIZE		1024
#define INFOSIZE	64

/**
 * functionName : infoInit
 * @Param :	char* info		[ char array to initialize	]
 * @Param : const char ch	[ initialize info with ch	]
 * @Param : int len			[ initial length of info	]
 * Brief  : 
 *		initialize info with ch letter by letter
 * return : null
 */
void infoInit(char *info,const char ch,int len){
	int i;
	for(i = 0;i < len; i++){
		info[i] = ch;	
	}
}


/**
 * functionName : infoDeal 
 * @Param :	const char* filename	[ the name of the file which is to create Info ]
 * @Param : char* Info				[ store the fileInfo 	]
 * Brief  : 
 *		use filename to create fileInfo and store it in @Param:Info 
 *		The fileInfo format as below
 *		"#filename$filesize###(repeat #)" the string length is 64
 * return : 
 *		The return value is 0
 *		and the created fileInfo store in @Param:Info
 */
int infoDeal(const char* filename,char * Info){
	struct stat sb; // stat buffer
	int fsize;
	char fileInfo[INFOSIZE+1];
	char tmp[INFOSIZE+1];

	memset(fileInfo,0,INFOSIZE+1);
	memset(tmp,0,INFOSIZE+1);
	infoInit(fileInfo,'#',INFOSIZE);

	//Get file Size
	stat(filename,&sb);
	fsize = (int)sb.st_size;

	sprintf(tmp,"#%s$%d",filename,fsize);

	//	printf("BEFORE:fileInfo = %s\n",fileInfo);
	//	printf("BEFORE:tmp      = %s\n",tmp);
	strncpy(fileInfo,tmp,strlen(tmp));
	//	printf("AFTER :fileInfo = %s\n",fileInfo);
	strcpy(Info,fileInfo);
	return 0;
}

/**
 * functionName : dataInfoDeal
 * @Param : int datalen			[ data length to create dataInfo		]
 * @Param : char* Info			[ dataInfo 64bytes, filled with '#'		]
 * Brief  : 
 *		DataInfo pre-deal before send
 * return : 
 *		return 0 without error check
 */
int dataInfoDeal(int datalen,char * Info){

	char dataInfo[INFOSIZE+1];
	char tmp[INFOSIZE+1];

	memset(dataInfo,0,INFOSIZE+1);	
	memset(tmp,0,INFOSIZE+1);	
	infoInit(dataInfo,'#',INFOSIZE);

	sprintf(tmp,"#DATAINFO$%d",datalen);
	strncpy(dataInfo,tmp,strlen(tmp));	

	strcpy(Info,dataInfo);	
	return 0;
}

/**
 * functionName : sendInfo
 * @Param : int sockfd			[ socket file descriptor	]
 * @Param : char* fileInfo		[ fileInfo to send			]
 * Brief  : 
 *		send fileInfo through sockfd
 * return : 
 *		if send successfully, return 0
 *		else return -1
 */
int sendInfo(int sockfd,char * fileInfo){
	int number_bytes;

	if(strlen(fileInfo) != INFOSIZE){	
		printf("fileInfo length is illegal\n");
		exit(EXIT_FAILURE);
	}else{
		if(-1 == (number_bytes = send(sockfd, fileInfo, INFOSIZE,0))){
			perror("send error");	
			return -1; 
		}else{
			return 0;	
		}	
	}
}

/**
 * functionName :  recvInfo
 * @Param : int sockfd			[ socket file descriptor	]
 * @Param : char*	fileInfo	[ fileInfo to recv	]
 * Brief  : 
 *		receive fileInfo from socket and store it in @Param:fileInfo
 * return : 
 *		if recvInfo successfully, return 0
 *		else return -1
 */
int recvInfo(int sockfd, char *fileInfo){
	int number_bytes;

	memset(fileInfo,0,INFOSIZE);
	if(-1 == (number_bytes = recv(sockfd, fileInfo, INFOSIZE,0))){
		perror("recv error");			
		return -1;
	}
	if(number_bytes != INFOSIZE){
		printf("fileInfo recv error\n");	
		return -1;
	}
	return 0;
}


/**
 * functionName : infoRmEnd
 * @Param : char *fileInfo		[ fileInfo to deal with			]
 * @Param : int len				[ the length of the fileInfo	]
 * Brief  : 
 *		remove '#' at end from @Param:fileInfo
 * return : null
 */
void infoRmEnd(char *fileInfo,int len){
	int i; 	
	for(i = len-1; i > 0; i--){
		if(fileInfo[i] == '#')	
			fileInfo[i] = 0;
		else //fileInfo[i] != 0
			break;
	}
}

/**
 * functionName : infoParse
 * @Param :	char *fileInfo			[ fileInfo to parse				]
 * @Param : char *fileInfo			[ filename parsed from fileInfo	]
 * @Param : int *filesize			[ filesize parsed from fileInfo	]
 * Brief  : 
 *		Parse @Param:fileInfo and extract filename and filesize
 *		and store them into @Param:filename and @Param:filesize 
 * return : 
 *		no error check, return 0 
 */
int infoParse(char* fileInfo,char * filename,int * filesize){

	char fname[30];
	char fsize[30];

	memset(fname,0,30);
	memset(fsize,0,30);

	//printf("BEFORE:%s\n",fileInfo);	
	infoRmEnd(fileInfo,INFOSIZE);
	//printf("AFTER:%s fileInfo len=%d\n",fileInfo,strlen(fileInfo));	

	strncpy(fname,fileInfo+1,strchr(fileInfo,'$')-fileInfo-1);	
	strcpy(fsize,strchr(fileInfo,'$')+1);

	//printf("FileName:%s\n",fname);
	//printf("Filesize:%s\n",fsize);

	strcpy(filename,fname);
	*filesize = atoi(fsize);
	return 0;

}


/**
 * functionName : sendfile
 * @Param : int sockfd			[ socket file descriptor		]
 * @Param : const char*filename	[ name of the file to send		]
 * Brief  : 
 *		send the file with the @Param:filename through the sockfd		
 * return : 
 *		return  0 when failed to open file
 *		return -1 when some errors happen in send
 *		return  1 send file successfully
 */
ssize_t sendfile(int sockfd, const char * filename){

	FILE *fp;
	char sendbuf[BUFSIZE];
	ssize_t number_bytes;
	int ret;

	if(NULL == (fp = fopen(filename,"rb+"))){
		perror("sendfile	 file open failed!\n");				
		ret = 0;
		//exit(EXIT_FAILURE);
	}else{
		while(!feof(fp)){
			memset(sendbuf,0,BUFSIZE);	
			number_bytes = fread(sendbuf,1,BUFSIZE,fp);
			if(-1==(number_bytes = send(sockfd,sendbuf,number_bytes,0))){
				perror("send error");		
				ret = -1; 
				fclose(fp);
				return ret;
				//	exit(EXIT_FAILURE);
			};
		}			
		ret = 1;
	}	
	fclose(fp);
	return ret;
}

/**
 * functionName : recvfile
 * @Param :	int sockfd				[ socket file descriptor			]
 * @Param : const char* filename	[ the name of the file to receive	]
 * @Param : int filesize			[ the size of the file to receive	]
 * Brief  : 
 *		receive file named @Param:filename and with a size = @Param:filesize  through sockfd
 * return : 
 */
ssize_t recvfile(int sockfd,const char * filename,int filesize){
	FILE *fp;	
	char recvbuf[BUFSIZE];
	ssize_t number_bytes;
	int ret,restsize;

	restsize = filesize;

	if(NULL==(fp = fopen(filename,"wb"))){
		perror("recvfile	failed to open ");
		ret = 0;
	}else{
		while(1){	
			memset(recvbuf,0,BUFSIZE);	
			if(restsize > BUFSIZE ){
				if((number_bytes = recv(sockfd, recvbuf, BUFSIZE,0))==-1){
					perror("recvfile	recv() error");
					fclose(fp);
					return -1;
				}else{
					fwrite(recvbuf,1,number_bytes,fp);				
					restsize -= number_bytes;
				}
			}else if(restsize == 0){
				break;
			}else{
				if((number_bytes = recv(sockfd, recvbuf, restsize,0)) == -1){
					perror("recvfile	recv() error");
					fclose(fp);
					return -1;
				}else{
					fwrite(recvbuf,1,number_bytes, fp);	
					restsize -= number_bytes;
				}
			}
		}
		fclose(fp);
	}	
	return ret;
}

//Data send && receive
/**
 * functionName : sendData
 * @Param :	int sockfd				[ socket file descriptor		]
 * @Param : const char* data		[ data to send					]
 * @Param : int datalen				[ the lenght of data to send 	]
 * Brief  : 
 *		send data through sockfd
 *		this function will send a DataInfo before sending data
 *		@Param:datalen is recommanded <= 4096 to decrease the memory consumption
 * return : 
 *		return the length sent, and if some errors happened,
 *		the process will exit with EXIT_FAILURE
 */
ssize_t sendData(int sockfd,const char* data,int datalen){

	int number_bytes;
	char dataInfo[INFOSIZE+1];

	memset(dataInfo,0,INFOSIZE+1);
	//data Info pre deal and send out
	dataInfoDeal(datalen,dataInfo);
	printf("DataInfo:%s\n",dataInfo);	
	sendInfo(sockfd,dataInfo);

	if((number_bytes = send(sockfd,data,datalen,0)) == -1){
		perror("sendData() failed");
		exit(EXIT_FAILURE);
	}

	printf("send Data:%s\n",data);
	return number_bytes;

}

/**
 * functionName : recvData
 * @Param :	int sockfd		[ socket file descriptor	]
 * @Param : int dataStore	[ The pointer to store the received data, u need malloc enough space before using 	]
 * Brief  : 
 *		receive data through sockfd
 *		this function will receive a DataInfo before receiving data
 *		and Parse the DataInfo to create proper buffer to receive data
 * return : 
 *		return the length received, and if some errors happened,
 *		the process will exit with EXIT_FAILURE
 */
int recvData(int sockfd,char *dataStore){
	int number_bytes;
	int datalen;
	char dataInfo[INFOSIZE+1];
	char tmp[INFOSIZE+1];
	char *buffer;

	memset(dataInfo,0,INFOSIZE+1);	
	memset(tmp,0,INFOSIZE+1);	

	recvInfo(sockfd,dataInfo);
	printf("recv data Info:%s\n",dataInfo);				

	//recv data info and parse
	infoParse(dataInfo,tmp,&datalen);
	buffer = (char*)malloc(datalen+1);			
	memset(buffer,0,datalen+1);

	if((number_bytes = recv(sockfd,buffer,datalen,0)) == -1){
		perror("recvData() failed");		
		exit(EXIT_FAILURE);
	}

	strcpy(dataStore,buffer);
	free(buffer);

	return number_bytes;
} 


/**
 * functionName : addSocketfdToFileName
 * @Param :	char *filename	[ the filename						]
 * @Param : int dataStore	[ the sockfd to add into filename 	]
 * Brief  : 
 *		adding sockfd(int) to filename
 *		for example: [a.txt] => addSocketfdToFileName("a.txt",1) =>[a1.txt]
 * return : 
 *		return -1 if the sockfd is invalid
 *		return 0 if it runs well
 */
int addSocketfdToFileName(char *filename,int sockfd)
{
	char numstr[20][3]={"0\0","1\0","2\0","3\0","4\0","5\0","6\0","7\0","8\0","9\0"};
	int i,bai,shi,ge;
	int first=1,hastype=0;
	//最大999
	if(sockfd>999){
		printf("invalid number..\n"); 
		return -1;
	}

	char last[16];
	memset(last,'\0',sizeof(last));

	//判断是否有后缀名
	int len=strlen(filename);
	for(i=len-1;i>0;i--)
	{
		if(filename[i]=='.')
		{
			hastype=1;
			break;
		}
	}  
	//有后缀名，先保存后缀名
	if(hastype==1)
	{
		strcpy(last,filename+i);
		memset(filename+i,'\0',strlen(filename)-i);
	}

	//百位
	bai=sockfd/100;
	if(bai>0) { strcat(filename,numstr[bai]); first=0;}
	sockfd=sockfd%100;
	//十位
	shi=sockfd/10;
	if(shi>0) { strcat(filename,numstr[shi]); first=0;}
	else if(shi==0&&first==0){ strcat(filename,numstr[shi]); first=0;}
	sockfd=sockfd%10;
	//个位
	ge=sockfd;
	{ strcat(filename,numstr[ge]); first=0;}

	//如果原来有后缀名，将后缀名添上
	if(hastype==1)
	{
		strcat(filename,last);
	}
	return 0;

}

/**
 * functionName : sendTimestamptoClient 
 * @Param :	int sockfd		[ the socket file descriptor	]
 * @Param : char* timestamp [ the timestamp	@server[12bytes]]  
 * Brief  : 
 *		sending timestamp through sockfd	
 *		we using this timestamp to avoid re-sent attacks
 * return : null
 */
void sendTimestamptoClient(int sockfd,char * timestamp)
{
	int number_bytes; 
	if((number_bytes = send(sockfd,timestamp,12,0)) == -1){
		perror("sendTimestamptoClient() failed");
		exit(EXIT_FAILURE);
	}
	return ;
}

/**
 * functionName : createTimeStamp
 * Brief  : 
 *		create a 12byte timestamp,start with '#' and end with '\0'
 * return : char* 
 *		return the timeStamp [12 bytes]
 *		EG:#1234567890
 */
char * createTimeStamp()
{
	time_t curtime;
	char *timestamp=(char *)malloc(12);
	infoInit(timestamp,'\0',12);
	time(&curtime);
	char timestr[20];
	memset(timestr,'\0',20);
	sprintf(timestr,"#%ld",curtime);
	strncpy(timestamp,timestr,strlen(timestr));

	return timestamp;
}
