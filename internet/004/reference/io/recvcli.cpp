// 
// Just show a concurrent multi-connection client example.
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
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#include <csignal>
#include <cerrno>
#include <wait.h>
#include <iostream>
using namespace std;

#define MAX_LEN 1024

void sighandler(int signo) {
  int status;
  pid_t pid;
  while((pid =waitpid(-1, &status, WNOHANG)) > 0) {
    cout << "process " << pid << "terminated" << endl;
  }
}

int main(int argc, char *argv[])
{
   int sockfd;
   int conn_ret;
   int status;
   int i;
   int ret_val;
   ssize_t number_bytes;

   struct sockaddr_in servaddr;

   char sendbuf[30]; 
   const char *hello= "hello world!";
   char recvbuf[MAX_LEN];

   pid_t pid;

   signal(SIGCHLD,sighandler);
   if(argc != 3) {
      cout << "Usage:readcli <address> <port> " << endl;
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

   for(i=0; i<3; i++) {
     pid =fork();
     if (pid == 0 ) {
    
       sockfd = socket(AF_INET,SOCK_STREAM,0);
       if (sockfd  == -1) {
          perror("sock");
          exit(1);
       }

       conn_ret = connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
       if(conn_ret == -1){
          perror("connect");
          exit(1);
       }
      
       snprintf(sendbuf, sizeof(sendbuf), "%s,client:%d", hello, i);
       cout << "sendbuf is " << sendbuf << endl;

       number_bytes = send(sockfd, sendbuf, strlen(sendbuf), 0);
       if (number_bytes == -1) {
          perror("send");
          exit(1);
       }	
       number_bytes = recv(sockfd, recvbuf, MAX_LEN-1, 0);
       if (number_bytes ==- 1) {
          perror("recv");
          exit(1);
       }else{
         recvbuf[number_bytes] = '\0';
         cout << endl;
         cout << "client receives message:" << recvbuf << endl;
       }
       close(sockfd);
       exit(0);
     }
   
   }
   return 0;
}
