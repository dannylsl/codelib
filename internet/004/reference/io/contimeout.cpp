// 
// An example shows connection timeout and how to handle it.
// Client--SIGALRM
// Copyright (C) 2006, Li Suke, School of Software and Microelectronics,
// Beijing University
// This  is free software; you can redistribute it and/or
// modify it freely.

// This software  is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 


#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <unistd.h>
#include <csignal>
#include <cerrno>
#include <arpa/inet.h>
#include <iostream>
using namespace std;

#define MAX_LEN 1024

void sig_handler(int signum) {
   cout << "Alarm!." << endl;
   return;
}
int main(int argc, char *argv[]) 
{
   int sockfd;
   int conn_ret;
   int ret_val;

   struct sockaddr_in servaddr;
   struct timeval btval;
   struct timeval etval;

   if(argc != 3) {
      cout << "Usage:readint <address> <port>" << endl;
      exit(1);
   }
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd  == -1) {
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
   signal(SIGALRM, sig_handler);
   siginterrupt(SIGALRM, 1);
   alarm(1);
   gettimeofday(&btval, NULL);

   conn_ret = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
   gettimeofday(&etval,NULL);
   cout << "Connect timeout time is " << etval.tv_sec - btval.tv_sec << " seconds" << endl;
   if(conn_ret == -1) {
     perror("connect");
   }
   close(sockfd);
   return 0;
}
