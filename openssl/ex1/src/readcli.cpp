/* 
 Very simple and nasty client --just send a hello world message.
 Copyright (C) 2006, Li Suke, School of Software,Peking University
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

#define MAX_LEN 1024
int main(int argc, char *argv[])
{
   int sockfd;
   int conn_ret;
   struct sockaddr_in servaddr;
   const char *sendbuf = "hello world!";
   char recvbuf[MAX_LEN];
   ssize_t number_bytes;
   int ret_val;

   if(argc != 3 ){ 
      cout << "Usage: client <address> <port>" << endl;
      exit(0);
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
     exit(1);
   }

   ret_val = write(sockfd,sendbuf,strlen(sendbuf));
   if (ret_val == -1){
     perror("send");
     exit(1);
   }	
   number_bytes = read(sockfd,recvbuf,MAX_LEN-1);
   if (number_bytes == -1) {
     perror("recv");
     exit(1);
   }else{

     recvbuf[number_bytes] = '\0';
     cout <<"client receives message:"<< recvbuf << endl;
   }
   close(sockfd);
   return 0;
}
