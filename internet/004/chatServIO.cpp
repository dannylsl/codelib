/* fileName: chatServThread.cpp
 * author: danny lee
 * Email : dannylsl@pku.edu.cn
 * Description:
 *	 SERVER for chatroom with IO
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

#include <iostream>

using namespace std;

const int BACKLOG = 10;
const int MAX_LEN = 1024;
const int PORT	  = 6000;

void printErr(const char* title){
	cerr<<title<<":"<<strerror(errno)<<endl;
}


int main(int argc,char *argv[]){
	int connfd,sockfd,clifd,max_fd;
	struct sockaddr_in servaddr;
	struct sockaddr_in cliaddr;
	socklen_t clilen;
	int ret_val;
	
	int i,nready,max_index;
	int len;
	int client[FD_SETSIZE];
	char buffer[MAX_LEN];

	fd_set allset,rdset;


	bzero(&servaddr,sizeof(struct sockaddr_in));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1){
		printErr("socket error");
		exit(EXIT_FAILURE);
	}


	ret_val = bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	if(ret_val == -1){
		printErr("bind error");
		exit(EXIT_FAILURE);
	}

	ret_val = listen(sockfd, BACKLOG);
	if(ret_val == -1){
		printErr("listen error");
		exit(EXIT_FAILURE);
	}
	
	setsockopt(sockfd, SOL_SOCKET,SO_REUSEADDR,&len,sizeof(len));

	max_fd = sockfd;
	cout << "Server is starting..."<<endl;

	FD_ZERO(&allset);
	FD_ZERO(&rdset);
	FD_SET(sockfd,&allset);

	for( i = 0; i < FD_SETSIZE; i++)
		client[i]=-1;
	max_index = -1;

	while(1){
		rdset = allset;
		nready = select(max_fd+1, &rdset,NULL,NULL,NULL);

		if(FD_ISSET(sockfd,&rdset)){
			clilen = sizeof(cliaddr);	
			connfd = accept(sockfd, (struct sockaddr*)&cliaddr, &clilen);

			if(connfd == -1){
				printErr("accept error");
				continue;
			}

			for(i = 0; i < FD_SETSIZE; i++){
				if(client[i] == -1){
					client[i] = connfd;
					break;
				}	
			}

			if(i == FD_SETSIZE){
				cout<<"Too many client here!"<<endl;
				exit(EXIT_FAILURE);
			}
			if(i > max_index)
				max_index = i;
			if(connfd > max_fd)
				max_fd = connfd;
			FD_SET(connfd,&allset);

			if(--nready <=0 )
				continue;
		}

		for ( i=0; i <= max_index;i++){

			if((clifd = client[i]) < 0){
				continue;	
			}

			if(FD_ISSET(clifd,&rdset)){
				len = MAX_LEN;

				len = recv(clifd, buffer, len, 0);
				if(len <= 0){
					close(clifd);
					FD_CLR(clifd,&allset);
					client[i] = -1;
				}else{
		//			send(clifd,buffer, len,0);	
						
					for( i = 0; i < FD_SETSIZE; i++){
						if(client[i]!=-1){
							send(client[i],buffer, len,0);	
						}
					}
				}
				if(--nready <=0)
					break;
			}
		}
	
	}
}






