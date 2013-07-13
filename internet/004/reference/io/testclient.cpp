// 
// This example is a test client to test the server's recv timeout
// Copyright (C) 2006, Li Suke, School of Software and Microelectronics,
// Beijing University
// This  is free software; you can redistribute it and/or
// modify it freely.
//
// This software  is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 

#include <cstdlib>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cerrno>
#include <iostream>

using namespace std;

#define MAX_LEN 1024

int main(int argc, char *argv[]) 
{
   int sockfd;
   int ret_val;
   struct sockaddr_in servaddr;
   const char *sendbuf = "hello world!";

   char recvbuf[MAX_LEN];
   ssize_t number_bytes;

   if(argc != 3) {
      cout << "Usage:readcli <address> <port> " << endl;
      exit(1);
   }
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd == -1) {
       perror("sock");
       exit(1);
   }
   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(atoi(argv[2]));
   ret_val = inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
   if (ret_val <= 0) {
     perror("inet_pton");
     exit(1);
   }
   ret_val = connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
   if(ret_val == -1){
     perror("connect");
     exit(1);
   }


   while(read(sockfd,recvbuf,sizeof(recvbuf)) != 0) {
     sleep(1);
   }
   close(sockfd);
   return 0;
}
