/**
 * FileName : filetree.cpp
 * Author	: Danny Lee
 * Email	: dannylsl@pku.edu.cn
 * StudentID: 1201210660
 *
 * Description : 
 *		This program runs a server deals multiple client requests for file transmission
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <errno.h>

#define BACKLOG			10
#define MAX_LEN			1024
#define FILEBLOCKSIZE	1024
#define PORT			6000
#define FILEEXIST       "FILEXST"
#define FILEND			"FILEEND"
#define FILENOTEXIST    "FNEXIST"

void printErr(char* errname){
	perror(errname);
	perror(strerror(errno));
	exit(EXIT_FAILURE);
}

ssize_t sendMsg(int connfd, char *msg,int size){	
	ssize_t number_bytes;
	//printf("Send msg:%s\n",msg);
	if((number_bytes = send(connfd, msg,size,0))==-1){
		printErr("Send Error");	
	}
	//printf("send %d bytes\n",size);
	return number_bytes;
}

void *deal_client(void*arg){
	char buffer[MAX_LEN];	
	char sendbuf[MAX_LEN];
	ssize_t number_bytes;
	FILE* fp;
	struct stat sb;  //stat buffer
	int	fsize;
	int sent = 0;

	int connfd = *((int*)arg);
	pthread_detach(pthread_self());

	number_bytes = recv(connfd,buffer,sizeof(buffer)-1,0);
	if(number_bytes == -1){
		perror("recv error:");
		perror(strerror(errno));
	}else{
		buffer[number_bytes] = '\0';
		printf("Server receives message:%s\n",buffer);	
			
		if(NULL== (fp = fopen(buffer,"rb+"))){
			//FILE NOT EXIST
			number_bytes = sendMsg(connfd , FILENOTEXIST,strlen(FILENOTEXIST));

		}else{
			stat(buffer,&sb);
			fsize = (int)sb.st_size;
			printf("filesize:%11d\n",fsize);
			strcpy(sendbuf,FILEEXIST);

			if( 0 != (number_bytes = sendMsg(connfd,sendbuf,strlen(sendbuf)))){
				while(!feof(fp)){
					memset(sendbuf,'\0',MAX_LEN);
					number_bytes = fread(sendbuf,1,MAX_LEN,fp);		
					number_bytes = sendMsg(connfd,sendbuf,number_bytes);
					sent += number_bytes;
					printf("sent:%15d\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b",sent);
				}

				fclose(fp);
				sleep(1);
				sendMsg(connfd,FILEND,strlen(FILEND));
				printf("\nfile transmission finished\n");
			}; 
		}
	}

	free(arg);
	close(connfd);
	pthread_exit(NULL);
}

int main(int argc, char* argv[]){

	int *connfd; 
	int sockfd;
	struct sockaddr_in servaddr;
	struct sockaddr_in cliaddr;
	socklen_t clilen;
	int flag = 1,len = sizeof(int);

	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1){
		perror("socket");		
		perror(strerror(errno));
		exit(1);
	}
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	if(setsockopt(sockfd, SOL_SOCKET,SO_REUSEADDR,&flag,len)== -1){
		printErr("setsockopt error");
		exit(EXIT_FAILURE);
	}

	if(bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) == -1){
		perror("bind error:");
		perror(strerror(errno));
		exit(1);
	}

	printf("Server is running...\n");
	if (listen(sockfd,BACKLOG) == -1){
		perror("listen");
		exit(1);
	}

	while(1){
		pthread_t pt;
		clilen = sizeof(cliaddr);
		connfd = (int*)malloc(sizeof(int));
		if((*connfd = accept(sockfd,(struct sockaddr *)&cliaddr,&clilen))==-1){
			if(errno == EINTR){
				perror("accept");
				perror(strerror(errno));
				continue;
			}else{
				exit(1);
			}
		}

		if(pthread_create(&pt,NULL,deal_client,connfd) != 0){
			perror("pthread_create");	
			break;
		}
	}
	return 0;
}
