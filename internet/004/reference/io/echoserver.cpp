// 
// This example shows:
//   1.How do an EINTR error happen?
//   2.Use waitpid()
//   3.Deal with SIGCHLD,SIGALRM
//   4.Use fork() to deal with multi-request from clients

// Copyright (C) 2006, Li Suke, School of Software and Microelectronics, 
//   Beijing University
// This  is free software; you can redistribute it and/or
// modify it freely.
//
// This software  is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 



#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <csignal>
#include <wait.h>

#include <iostream>
using namespace std;

#define BACKLOG 10
#define MAX_LEN 1024

void sig_handler(int signo)
{
  int stat;
  int pid;

  switch(signo) {
    case SIGALRM:
       cout << "SIGALRM happens" << endl;
       break;
    case SIGCHLD:

       while((pid = waitpid(-1,&stat,WNOHANG)) > 0)
         cout << "child "<< pid << "terminated" << endl;
       break;
    default:
       break;
  }
  return;
}

int main(int argc, char* argv[])
{
   int connfd, sockfd;
   struct sockaddr_in servaddr;
   struct sockaddr_in tempaddr;
   struct sockaddr_in cliaddr;
   struct sockaddr_in test;

   socklen_t testlen;
   socklen_t clilen;
   socklen_t templen;
   ssize_t number_bytes;
   char buffer[MAX_LEN];

   pid_t pid;
   int ret_val = 0;

   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd  == -1) {
      perror("socket");
      exit(1);
   } 
   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   servaddr.sin_port = 0;
   
   ret_val = bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
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

   cout << "Server is listening on port" << ntohs(tempaddr.sin_port) << endl;

   ret_val = listen(sockfd,BACKLOG);
   if (ret_val  == -1) {
      perror("listen");
      exit(1);
   }
   siginterrupt(SIGALRM, 1);
   signal(SIGALRM, sig_handler);	
   signal(SIGCHLD, sig_handler);
   alarm(1);

   for(;;) {

      clilen = sizeof(cliaddr);
      connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
      if (connfd == -1)
      {
         if(errno == EINTR) {
            perror("accept");
            continue;
         }else {
            exit(1);
         }
      }

      testlen = sizeof(test);
      getpeername(connfd, (struct sockaddr *)&test, &testlen);	
      pid = fork();

      if(pid == 0 ) { 
          close(sockfd);

          number_bytes = recv(connfd, buffer, sizeof(buffer)-1, 0);
          if (number_bytes == -1) {
             perror("recv"); 

          }else {
             buffer[number_bytes] = '\0';
             cout << "Server receives message:"<< buffer << endl;
             number_bytes = send(connfd,buffer,number_bytes,0);
             if (ret_val ==-1) {
                perror("send");
             }
          }
          close(connfd);
          exit(1);
      }
      cout << "fork a child " << pid << endl;
      close(connfd);
   }
   return 0;
}
