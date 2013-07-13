/* fileName: chatServThread.cpp
 * author: danny lee
 * Email : dannylsl@pku.edu.cn
 * Description:
 *	 SERVER for chatroom with multiThread
 * */

#include <cerrno>
#include <cstring>
#include <cstdlib>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <pthread.h>

#include <iostream>

using namespace std;

const int BACKLOG = 10;
const int MAX_LEN = 1024;
const int PORT	  = 6000;

int client[FD_SETSIZE];
int clicnt = 0;

void printErr(const char* title){
	cerr<<title<<":"<<strerror(errno)<<endl;
}

void * deal_client(void*arg){

    char buffer[MAX_LEN];
    ssize_t number_bytes;
	int i;

    int connfd = *((int *)arg);
    pthread_detach(pthread_self());
	while(1){
		number_bytes = recv(connfd,buffer,sizeof(buffer)-1,0);
		if (number_bytes == -1){
			printErr("recv");
		}else{
			buffer[number_bytes] = '\0';
			//cout<<"Server receives message:"<<buffer<<endl;
			if(strcmp(buffer,"quit")==0){
				number_bytes = recv(connfd,buffer,sizeof(buffer)-1,0);
		
				for(i = 0; i < clicnt;i++){
					if(client[i] == connfd){
						client[i] =-1;	
						clicnt--;
						continue;
					}else{
						send(client[i],buffer,number_bytes,0);
					}
				}		
				memset(buffer,'\0',MAX_LEN);
			}
			
			for(i = 0;i < clicnt; i++){
				if(client[i] != -1){
					if(strcmp(buffer,""))
						send(client[i],buffer,number_bytes,0);
				}
			}
		}
	}

    free(arg);
    close(connfd);
    pthread_exit(NULL);      

}

int main(int argc,char *argv[]){

	int *connfd; 
	int sockfd;
	struct sockaddr_in servaddr;
	struct sockaddr_in cliaddr;
	socklen_t clilen;
	int len;

	for(int i = 0; i< FD_SETSIZE;i++){
		client[i] = -1;	
	}
	if((sockfd = socket(AF_INET, SOCK_STREAM,0)) == -1){
		printErr("socket error");
		exit(EXIT_FAILURE);
	} 

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	if (bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) == -1)
	{
		printErr("build error");
		exit(EXIT_FAILURE);
	}

	if (listen(sockfd,BACKLOG) == -1){
		printErr("listen error");
		exit(EXIT_FAILURE);
	}

	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&len,sizeof(len));

	cout<<"Server is working..."<<endl;
	for(;;){
		pthread_t pt;
		clilen = sizeof(cliaddr);
		connfd = (int *)malloc(sizeof(int));
		if((*connfd = accept(sockfd,(struct sockaddr *)&cliaddr,&clilen))==-1)
		{
			if(errno == EINTR){
				printErr("EINTR ERROR");
				continue;
			}else{
				exit(1);
			}
		}
		client[clicnt] = *connfd;
		clicnt++;

		if(pthread_create(&pt, NULL, deal_client, connfd) != 0){
			printErr("pthread_create");
			break;
		}

	}

	return 0;

}
