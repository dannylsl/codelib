/* 
 This example show:
   A server deals with multiple client requests using 
   pthread API.
 Copyright (C) 1994-1995, Li Suke, School of Software,Peking University
 This  is free software; you can redistribute it and/or
 modify it freely.

 This software  is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <errno.h>

#define BACKLOG 10
#define MAX_LEN 1024

void * deal_client(void *arg)
{
    char buffer[MAX_LEN];
    ssize_t number_bytes;

    int connfd = *((int *)arg);
    pthread_detach(pthread_self());

	while(1){
		number_bytes = recv(connfd,buffer,sizeof(buffer)-1,0);
		if (number_bytes == -1){
			perror("recv");
		}else{
			buffer[number_bytes] = '\0';
			printf("Server receives message:%s\n",buffer);

			if((number_bytes = send(connfd,buffer,number_bytes,0))==-1){
			  perror("send");
			}
		}
	}
    free(arg);
    close(connfd);
    pthread_exit(NULL);      
}
int main(int argc, char* argv[])
{
   int *connfd; 
   int sockfd;
   struct sockaddr_in servaddr;
   struct sockaddr_in tempaddr;
   struct sockaddr_in cliaddr;
   socklen_t clilen;
   socklen_t templen;

   if((sockfd = socket(AF_INET, SOCK_STREAM,0)) == -1){
      perror("socket");
      exit(1);
   } 
   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   servaddr.sin_port = 0;
   
   if (bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) == -1)
   {
      perror("bind");
      exit(1);
   }
   /* how we can get the binded socket information */
   templen = sizeof(struct sockaddr);
   if (getsockname(sockfd, (struct sockaddr *)&tempaddr,&templen) == -1){
      perror("getsockname");
      exit(1);
   }
   printf("Server is listening on port %d\n",ntohs(tempaddr.sin_port));
   if (listen(sockfd,BACKLOG) == -1){
      perror("listen");
      exit(1);
   }
 
   for(;;){
      pthread_t pt;
      clilen = sizeof(cliaddr);
      connfd = (int *)malloc(sizeof(int));
      if((*connfd = accept(sockfd,(struct sockaddr *)&cliaddr,&clilen))==-1)
      {
         if(errno == EINTR){
            perror("accept");
            continue;
         }else{
            exit(1);
         }
      }

      if(pthread_create(&pt, NULL, deal_client, connfd) != 0){
         perror("pthread_create");
         break;
      }
       
   }
  
   return 0;
}
