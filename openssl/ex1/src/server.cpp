/* 
 Very simeple TCP client-server server program.
 Copyright (C) 2006, Li Suke, School of Software and Microelectronics,
 Beijing University
 This  is free software; you can redistribute it and/or
 modify it freely.

 This software  is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
*/

#include <cstdlib>
#include <cerrno>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

using namespace std;

#define BACKLOG 10

int main(int argc, char* argv[])
{
   int connfd, sockfd;
   struct sockaddr_in servaddr;
   struct sockaddr_in tempaddr;
   struct sockaddr_in cliaddr;

   socklen_t clilen;
   char ip_str[INET_ADDRSTRLEN];
   int ret_val;

   socklen_t templen;

   // create a IPv4 TCP socket 
   sockfd = socket(AF_INET, SOCK_STREAM,0);
   if (sockfd == -1) {
      perror("socket");
      exit(1);
   } 
   // initialize the sockaddr_in 
   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

   // We let the kernel to choose our port number 
   servaddr.sin_port = 0;

   // ok, now bind 

   ret_val = bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
   if(ret_val == -1)
   {
      perror("bind");
      exit(1);
   }
   cout << "the sockfd is " << sockfd << endl;

   // listen on the port
   ret_val = listen(sockfd,BACKLOG);
   if (ret_val  == -1) {
      perror("listen");
      exit(1);
   }
   
   // how we can get the binded socket information 
   templen = sizeof(struct sockaddr);

   ret_val = getsockname(sockfd, (struct sockaddr *)&tempaddr,&templen);
   if (ret_val  == -1) {

      perror("getsockname");
      exit(1);
   }
   cout << "Server is listening on port " << ntohs(tempaddr.sin_port) << endl;
   for(;;){
      clilen = sizeof(cliaddr);
      connfd = accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);
      if(connfd == -1){
         perror("accept");
         continue;
      }
      cout << "Server: client " << inet_ntoa(cliaddr.sin_addr) << " connect" << endl;
      close(connfd);  
   }
   return 0;
}
