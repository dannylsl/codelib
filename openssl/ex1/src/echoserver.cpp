/* 
 A very simple and nasty TCP echo server.
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
#define MAX_LEN 1024

int main(int argc, char* argv[])
{
   int connfd, sockfd;
   struct sockaddr_in servaddr;
   struct sockaddr_in tempaddr;
   struct sockaddr_in cliaddr;

   socklen_t clilen;
   socklen_t templen;

   ssize_t number_bytes;
   char buffer[MAX_LEN];
   int ret_val; 

   char ip_str[INET_ADDRSTRLEN];

   sockfd = socket(AF_INET, SOCK_STREAM,0);
   if (sockfd == -1) {
      perror("socket");
      exit(1);
   } 

   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   servaddr.sin_port = 0;
   ret_val = bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

   ret_val = listen(sockfd,BACKLOG);
  
   if (ret_val == -1)
   {
      perror("bind");
      exit(1);
   }
   // how we can get the binded socket information 
   templen = sizeof(struct sockaddr);

   ret_val = getsockname(sockfd, (struct sockaddr *)&tempaddr,&templen);
   if (ret_val  == -1) {
      perror("getsockname");
      exit(1);
   }

   cout << "Server is listening on port "<< ntohs(tempaddr.sin_port) << endl;
   inet_ntop(AF_INET, &tempaddr.sin_addr, ip_str, INET_ADDRSTRLEN);
   cout << "getsockname's IP is " << ip_str << endl; 

   if (ret_val  == -1) {
      perror("listen");
      exit(1);
   }	
   for(;;){

      clilen = sizeof(cliaddr);
      connfd = accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);
      if(connfd == -1){
         perror("accept");
         continue;
      }

      ret_val = getsockname(connfd, (struct sockaddr *)&tempaddr,&templen);
      if (ret_val  == -1) {
        perror("getsockname");
        exit(1);
      }

      cout << "connect fd port "<< ntohs(tempaddr.sin_port) << endl;
      inet_ntop(AF_INET, &tempaddr.sin_addr, ip_str,INET_ADDRSTRLEN);
      cout << "connect fd IP is " << ip_str << endl; 


      number_bytes = read(connfd,buffer,sizeof(buffer)-1);
      if (number_bytes == -1){
         perror("recv");
      }else{
         buffer[number_bytes] = '\0';
         cout << "Server receives message:"<< buffer << endl;
         if((number_bytes = write(connfd,buffer,number_bytes))==-1){
            perror("send");
         }
      }
      close(connfd);  
   }
   return 0;
}
