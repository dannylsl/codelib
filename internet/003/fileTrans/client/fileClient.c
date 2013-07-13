/**
 * FileName : fileClient.c
 * Author	: Danny Lee
 * Email	: dannylsl@pku.edu.cn
 * StudentID: 1201210660
 *
 * Description : 
 *		This program runs a client to retrive files from server 
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <wait.h>

#define MAX_LEN		1024
#define PORT		6000
#define FILEND		"FILEEND"
#define FILEEXIST   "FILEXST"
#define FILENOTEXIST "FNEXIST"

void printErr(char* errname){
	perror(errname);
	perror(strerror(errno));

}

int main(int argc, char * argv[]){
	int sockfd;
	int conn_ret;
	struct sockaddr_in servaddr;
	char fileName[64];
	char recvname[64];
	char recvbuf[MAX_LEN];
	ssize_t number_bytes;
	FILE *fp;
	
	if(argc < 3 || argc > 4){
		printf("Usage:fileClient <address> <filename> [recvname]\n");	//to be continued	
		printf("Eg1  :fileClient 192.168.1.100 hello.txt\n");			//to be continued	
		printf("Eg2  :fileClient 192.168.1.100 hello.txt recvfile\n");	//to be continued	
		return 0;
	}

	if(argc == 3)
		strcpy(recvname,argv[2]);
	if(argc == 4)
		strcpy(recvname,argv[3]);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port	= htons(PORT);
	inet_pton(AF_INET,argv[1], &servaddr.sin_addr);

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		printErr("Sock Error");
		exit(EXIT_FAILURE);
	}

	conn_ret = connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	if(conn_ret == -1){
		printErr("Connect Error");
		exit(EXIT_FAILURE);
	}

	snprintf(fileName, sizeof(fileName),"%s",argv[2]);
	if(send(sockfd,fileName,strlen(fileName),0) == -1){
		printErr("Send Error:");	
		exit(EXIT_FAILURE);
	} 

	printf("waiting message\n");
	while(1){

		if ((number_bytes = recv(sockfd, recvbuf, 7, 0))==-1){
			printErr("recv Erroe");
			exit(EXIT_FAILURE);
		}else{
			recvbuf[number_bytes] = '\0';
	//		if(strcmp(recvbuf,""))
	//			printf("client receives message:%s\n",recvbuf);
			if(strcmp(recvbuf,FILENOTEXIST) == 0){
				printf("File request not exsit on Server\n");	
				exit(1);	
			}
			if(strcmp(recvbuf,FILEEXIST) == 0){
				if((fp = fopen(recvname,"wb+")) == NULL){
					printErr("file Create error");			
					exit(EXIT_FAILURE);
				}else{
					printf("File Receiving...\n");	
					while(1){
						memset(recvbuf,'\0',MAX_LEN);
						if ((number_bytes = recv(sockfd, recvbuf, MAX_LEN, 0))==-1){
							printErr("recv Erroe");
							exit(EXIT_FAILURE);
						}else{
							if(strcmp(recvbuf,FILEND) == 0){
								printf("file received!\n");	
								exit(EXIT_SUCCESS);
							}
							else{
								fwrite(recvbuf,1,number_bytes,fp);
								continue;
							}
						}
					}
				}
			}
		}
	}
/*

	if((fp = fopen(fileName,"rw+")) == NULL){
		printErr("File open failed:");			
		exit(EXIT_FAILURE);
	}
	fclose(fp);

*/
	close(sockfd);
	exit(0);

}

