/* 
 Just show how to use getsockname() and getpeername()
 Copyright (C) 1994-1995, Li Suke, School of Software,Peking University
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
   struct sockaddr_in cliaddr;
   struct sockaddr_in sock_name;
   struct sockaddr_in peer_name;
   socklen_t peer_len;
   socklen_t clilen;
   socklen_t sock_len;

   sockfd = socket(AF_INET, SOCK_STREAM,0);
   if (sockfd == -1){
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
   if (listen(sockfd,BACKLOG) == -1){
      perror("listen");
      exit(1);
   }
   sock_len = sizeof(sock_name);
   if (getsockname(sockfd,(struct sockaddr*)&sock_name,&sock_len)==-1){
      perror("getsockname");
      exit(1);
   }
   cout <<"The server sock name info:" << endl;
   cout <<"Server address is "<< inet_ntoa(sock_name.sin_addr) << endl;
   cout <<"Server port is "<<ntohs(sock_name.sin_port) << endl;	
   cout <<"Server address length is "<< sock_len << endl;
   for(;;){
      clilen = sizeof(cliaddr);
      connfd = accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);
      if(connfd == -1){
         perror("accept");
         continue;
      }
      cout <<"Server: client" << inet_ntoa(cliaddr.sin_addr) << "connects" << endl;
      peer_len = sizeof(peer_name);
      if (getpeername(connfd,(struct sockaddr*)&peer_name,&peer_len)==-1){
         perror("getpeername");
      }else{
         cout <<"The peer sock name info:" << endl;
         cout <<"The peer address is" << inet_ntoa(peer_name.sin_addr) << endl;
         cout <<"The peer port is " << ntohs(peer_name.sin_port) << endl;
         cout <<"The peer address length is " << peer_len << endl;
      }
      close(connfd);  
   }
   return 0;
}
