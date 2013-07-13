/* 
 Just show how to use send() and recv()
 Copyright (C) 1994-1995, Li Suke, School of Software,Peking University
 This  is free software; you can redistribute it and/or
 modify it freely.

 This software  is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
*/

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cerrno>
#include <unistd.h>
#define MAX_LEN 1024

using namespace std;

int main(int argc, char *argv[])
{
   int sockfd;
   int conn_ret;
   struct sockaddr_in servaddr;
   const char *sendbuf = "hello world!";
   char recvbuf[MAX_LEN];
   ssize_t number_bytes;

   if(argc != 3) {
      printf("Usage:readcli <address> <port> \n");
      return 1;
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
   if(conn_ret == -1) {
     perror("connect");
     exit(1);
   }

   number_bytes = send(sockfd,sendbuf,strlen(sendbuf),0);
   if (number_bytes == -1) {
     perror("send");
     exit(1);
   }	

   number_bytes = recv(sockfd,recvbuf,MAX_LEN-1,0);

   if (number_bytes  == -1) {
     perror("recv");
     exit(1);

   }else{
     recvbuf[number_bytes] = '\0';
     printf("client receives message:%s\n",recvbuf);
   }
   close(sockfd);
   return 0;
}
