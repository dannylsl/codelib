// 
// UDP echo server.
// Copyright (C) 2006, Li Suke, School of Software and Microelectronics,
// Peking University
// This  is free software; you can redistribute it and/or
// modify it freely.

// This software  is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 

#include <cerrno>
#include <cstring>
#include <cstdlib>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include <iostream>

using namespace std;


int main(int argc, char* argv[])
{
   int connfd, sockfd;
   struct sockaddr_in servaddr;
   struct sockaddr_in cliaddr;
   socklen_t clilen;
   int ret_val;

   const int backlog = 10;
   const int max_len = 1024;
   
   int msglen;
   char buffer[max_len];

   if (argc != 2){
      printf("Usage:server <port>\n");
      exit(1); 
   }

   sockfd = socket(AF_INET, SOCK_DGRAM,0);

   if (sockfd == -1) {
      perror("socket");
      exit(1);
   } 

   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   servaddr.sin_port = htons(atoi(argv[1]));
   
   ret_val = bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
   if (ret_val == -1)
   {
      perror("bind");
      exit(1);
   }
   
   for(;;) {

      clilen = sizeof(cliaddr);      
      if((msglen = recvfrom(sockfd, buffer, max_len,0,(struct sockaddr *)&cliaddr,&clilen))==-1){
          perror("recvfrom");   
          continue;
      }

      buffer[msglen] ='\0';

      if(sendto(sockfd,buffer,msglen,0,(struct sockaddr *)&cliaddr,clilen)==-1){
          perror("sendto");
          continue;
      }
   }
   close(sockfd);
   return 0;
}
