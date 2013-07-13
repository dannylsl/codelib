// 
// A connected UDP socket  example.
// Copyright (C) 2006, Li Suke, School of Software and Microelectronics,
// Peking University
// This  is free software; you can redistribute it and/or
// modify it freely.

// This software  is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <cerrno>

#include <iostream>

using namespace std;


int main(int argc, char *argv[])
{
   int sockfd;
   int conn_ret;
   struct sockaddr_in servaddr;

   const int  max_len = 1024;
   const char *sendbuf = "hello world!";
   char recvbuf[max_len];

   int number_bytes;


   if(argc != 3) {
      printf("Usage: conclient <address> <port>\n");
      return 1;
   }

   sockfd = socket(AF_INET,SOCK_DGRAM,0);
   if (sockfd  == -1) {
       perror("socket");
       exit(1);
   }

   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(atoi(argv[2]));
   inet_pton(AF_INET,argv[1],&servaddr.sin_addr);

   conn_ret = connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
   if(conn_ret == -1){
       perror("connect");
       exit(1);
   }
 
   number_bytes = send(sockfd,sendbuf,strlen(sendbuf),0);

   if (number_bytes == -1) {
       perror("sendto");
       exit(1);
   }

   number_bytes = recv(sockfd,recvbuf,max_len-1,0);

   if (number_bytes == -1) {

       perror("recvbuf");
       exit(1);

   }else{

       recvbuf[number_bytes] = '\0';
       cout << "client receives message:"<< recvbuf << endl;
   }

   close(sockfd); 

   return 0;
}
