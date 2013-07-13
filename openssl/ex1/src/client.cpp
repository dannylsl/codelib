/* 
 simple TCP client-server client program
 Copyright (C) 2006, Li Suke, School of Software,
 Beijing University
 This  is free software; you can redistribute it and/or
 modify it freely.

 This software  is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
*/
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
   int sockfd;
   int conn_ret;
   struct sockaddr_in servaddr;

   if(argc != 3){
      cout << "Usage: client <address> <port> " << endl;
      return 0;
   }
   
   sockfd = socket(AF_INET,SOCK_STREAM,0);
   if (sockfd == -1) {
       perror("sock");
       exit(1);
   }

   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(atoi(argv[2]));
   inet_pton(AF_INET,argv[1],&servaddr.sin_addr);

   conn_ret = connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
   if(conn_ret == -1){
     perror("connect");
   }
   
   close(sockfd);
   return 0;
}
