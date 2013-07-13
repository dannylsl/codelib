/* chatCli.cpp
 * author	: Danny Lee
 * email	: dannylsl@pku.edu.cn
 * studentId: 1201210660
 * Description:
 *	chat room client with multi thread	
 */	

#include <cstdlib>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <cstdio>
#include <iomanip>

#include <iostream>
using namespace std;

#define MAX_LEN 1024
#define PORT	6000

void printErr(const char* errmsg){	
	cerr<<errmsg<<":"<<strerror(errno)<<endl;
	return;
}

void *recvmsg(void *arg){
	char recvbuf[MAX_LEN];
	ssize_t numbers_bytes;

	cout<<"'quit' to exit the program"<<endl;

	int connfd = *((int*)arg);
	pthread_detach(pthread_self());

	while(1){
		numbers_bytes = recv(connfd,recvbuf,MAX_LEN -1,0);
		if(numbers_bytes == -1)
			printErr("recv Error");
		else{
			recvbuf[numbers_bytes] = '\0';
			cout<<recvbuf<<endl;
		}
	}
	free(arg);
	close(connfd);
	pthread_exit(NULL);
}

int main(int argc,char*argv[]){
	int conn_ret;
	int sockfd;
	struct sockaddr_in servaddr;
	char sendbuf[MAX_LEN];
	char tmpbuf[MAX_LEN];

	if(argc != 3){
		cout << "Usage:"<<argv[0]<<" <address> <username>"<<endl;
		exit(EXIT_FAILURE);
	}


	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	inet_pton(AF_INET,argv[1],&servaddr.sin_addr);


	if((sockfd=socket(AF_INET, SOCK_STREAM,0)) == -1){
		printErr("socket error");	
		exit(EXIT_FAILURE);
	}

	conn_ret = connect(sockfd,(struct sockaddr*)&servaddr, sizeof(servaddr));
	if(conn_ret == -1){
		printErr("connect error");
		exit(EXIT_FAILURE);
	}

	pthread_t pt;	

	if(pthread_create(&pt, NULL, recvmsg, &sockfd)!= 0){
		printErr("pthread Create Error");	
		exit(EXIT_FAILURE);
	}
	sleep(1);
	
	sprintf(tmpbuf,"%s enter the chatroom",argv[2]);
	send(sockfd,tmpbuf,strlen(tmpbuf),0);

	while(1){
		bzero(&sendbuf,sizeof(sendbuf));
	//	cout<<"say any u want:";		
		memset(tmpbuf,'\0',MAX_LEN);
		gets(tmpbuf);
		//cout <<endl;
		sprintf(sendbuf,"%s say:%s",argv[2],tmpbuf);
		if(strcmp(tmpbuf,"quit")==0){
			strcpy(sendbuf,"quit");
			send(sockfd,sendbuf,strlen(sendbuf),0);
			sprintf(sendbuf,"%s quit the room",argv[2]);
			send(sockfd,sendbuf,strlen(sendbuf),0);
			exit(EXIT_SUCCESS);
		}
		if(send(sockfd,sendbuf,strlen(sendbuf),0)==-1){
			printErr("send Error");
			exit(EXIT_FAILURE);
		}
	}

}
