// 
// An example shows connection timeout and how to handle it.
// I use setsockopt.
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
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <csignal>
#include <cerrno>

#include <iostream>
using namespace std;

#define MAX_LEN 1024

int main(int argc, char *argv[])
{
   int sockfd;
   int ret_val;

   struct sockaddr_in servaddr;

   struct timeval btval;
   struct timeval etval;
   struct timeval tval;

   if(argc != 3) {
      cout << "Usage:readint <address> <port> " << endl;
      exit(1);
   }
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd == -1) {
       perror("sock");
       exit(1);
   }
   tval.tv_sec = 5;
   tval.tv_usec = 0;

   ret_val = setsockopt(sockfd,SOL_SOCKET,SO_SNDTIMEO,&tval,sizeof(struct timeval));
   if (ret_val < 0) {
      perror("setsockopt");
      exit(1);
   }

   bzero(&servaddr, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(atoi(argv[2]));
   ret_val = inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
   if (ret_val <= 0) {
      perror("inet_pton");
      exit(1);
   }
   gettimeofday(&btval,NULL);
   ret_val = connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
   gettimeofday(&etval,NULL);
   cout << "Connect timeout time is "<< etval.tv_sec - btval.tv_sec << " seconds" << endl;
   if(ret_val <0) {
     perror("connect");
   }

   close(sockfd);
   return 0;
}
