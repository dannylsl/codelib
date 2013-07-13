// 
// A echo server using select. 
// This example is modified from the source code of
// <unix network programming,volume 1>

// Copyright (C) 2006, Li Suke, School of Software and Microelectronics,
// Peking University
// This  is free software; you can redistribute it and/or
// modify it freely.
//
// This software  is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 


#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/select.h>
#include <cstring>
#include <cerrno>
#include <cstdio>

#include <iostream>
using namespace std;

#define  BACK_LOG 10
#define BUF_SIZE 1024
int main(int argc, char *argv[]) 
{
	int sockfd;
	int connfd;
	int clifd;
	int ret_val;

	int max_fd;
	int i;
	int nready;
	int max_index;
	int len;
	socklen_t clilen;

	struct sockaddr_in servaddr,cliaddr;
	int client[FD_SETSIZE];
	char buffer[BUF_SIZE];

	fd_set allset,rdset;

	if(argc != 2) {
		cout << "Usage: echoserv <port>" << endl;
		exit(1);
	}

	bzero(&servaddr,sizeof(struct sockaddr_in));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(atoi(argv[1]));

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		perror("socket");
		exit(1);
	}	 

	ret_val = bind(sockfd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr));
	if (ret_val == -1) {
		perror("bind");
		exit(1);
	}

	ret_val = listen(sockfd, BACK_LOG);
	if (ret_val == -1) {
		perror("listen");
		exit(1);
	}  
	max_fd = sockfd;

	FD_ZERO(&allset);
	FD_ZERO(&rdset);
	FD_SET(sockfd,&allset);

	for(i=0; i< FD_SETSIZE; i++)
		client[i] = -1;
	max_index = -1;

	for(;;) {
		rdset = allset;
		nready = select(max_fd+1,&rdset,NULL,NULL,NULL);

		if(FD_ISSET(sockfd, &rdset)) {
			clilen = sizeof(cliaddr);
			connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);

			if(connfd ==-1){
				perror("accept");
				continue;
			}

			for(i = 0; i < FD_SETSIZE; i++) {
				if(client[i] == -1) {
					client[i] = connfd;
					break;
				}
			}

			if(i == FD_SETSIZE){
				cout << "Too many client here!" << endl;
				exit(1);
			}

			if(i > max_index)
				max_index = i;
			if(connfd > max_fd)
				max_fd = connfd;
			FD_SET(connfd,&allset);

			if(--nready <=0)
				continue;        
		}

		for (i=0; i<= max_index; i++) {

			if((clifd=client[i])< 0){
				continue;
			}
			if(FD_ISSET(clifd,&rdset)) {
				len = BUF_SIZE;

				len = recv(clifd, buffer, len, 0);
				if (len <= 0) {

					close(clifd);
					FD_CLR(clifd,&allset);
					client[i] = -1;
				}else             
					send(clifd,buffer,len,0);

				if(--nready <=0) 
					break;

			}//if

		}//for   
	}//for 
}
