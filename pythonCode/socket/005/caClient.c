/**
 * FileName	: caClient.c
 * Author	: Danny Lee
 * Email	: dannylsl@hotmail.com
 * Date		: 2013-07-12  21:00PM
 * Brief	: 
 *		This program is a client apply for certification from CA
 *		create certification request file and apply certification from CA
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <wait.h>
#include "certreq.h"

#define BUFSIZE		1024
#define PORT		6000
#define INFOSIZE	64

#define REQNAME		"certreq.pem"


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
 * @Param :	const char *fileInfo	[ fileInfo to parse				]
 * @Param : char *fileInfo			[ filename parsed from fileInfo	]
 * @Param : int *filesize			[ filesize parsed from fileInfo	]
 * Brief  : 
 *		Parse @Param:fileInfo and extract filename and filesize
 *		and store them into @Param:filename and @Param:filesize 
 * return : 
 *		no error check, return 0 
 */
int infoParse(const char* fileInfo,char * filename,int * filesize){

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

int main(int argc, char* argv[]){
	int sockfd;
	int conn_ret;
	struct sockaddr_in servaddr;
	char filename[64];
	char fileInfo[INFOSIZE+1];
	int fsize;
	subjectInfo subject;


	if(argc != 2){
		printf("Usage: %s <address> \n",argv[0]);
		return 0;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port	= htons(PORT);
	inet_pton(AF_INET,argv[1], &servaddr.sin_addr);

	if((sockfd = socket(AF_INET, SOCK_STREAM,0 )) == -1){
		perror("SOCKET ERROR");
		exit(EXIT_FAILURE);
	}

	conn_ret = connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	if(conn_ret == -1){
		perror("CONNECT ERROR");
		exit(EXIT_FAILURE);
	}

	printf("starting...\n");
	
	setCommonname(&subject,"Zengtianning");
	setCountryName(&subject,"HL");
	setEmailAddress(&subject,"sanpuyouyou@163.com");
	setStateFullName(&subject,"Heilongjiang");
	setOrganizationName(&subject,"SSPKU");
	setOrganizationalUnit(&subject,"Peking University");
	setLocalityName(&subject,"24 JinYuan Road");
	if(subjectCheck(&subject) < 0){
		printf("subject error set!\n");
		return -1;
	}

	genApply(REQNAME,&subject);

	infoDeal(REQNAME,fileInfo);
	printf("fileInfo:%s\n",fileInfo);
	sendInfo(sockfd,fileInfo);
	sendfile(sockfd,REQNAME);


	recvInfo(sockfd,fileInfo);	
	printf("recv fileInfo:%s\n",fileInfo);

	infoParse(fileInfo,filename,&fsize);
	printf("recv filename: %s	filesize:%d\n",filename,fsize);
	recvfile(sockfd,filename,fsize);

	return 0;
}


