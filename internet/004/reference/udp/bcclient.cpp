// 
// UDP broadcasting example.
// Copyright (C) 2006, Li Suke, School of Software and Microelectronics,
// Peking University
// This  is free software; you can redistribute it and/or
// modify it freely.
//
// This software  is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <cerrno>
#include <cstdlib>

#include <iostream>

using namespace std;


int main(int argc, char *argv[])
{
   int sockfd;
  
   struct sockaddr_in servaddr;
   const char *sendbuf = "hello world!";


   const int  max_len =  1024;

   char recvbuf[max_len];
   int number_bytes;
   int servlen;
   int on = 1;

   if(argc != 3){
      printf("Usage: client <address> <port>\n");
      return 1;
   }

   sockfd = socket(AF_INET,SOCK_DGRAM,0);
   if (sockfd == -1) {
       perror("sock");
       exit(1);
   }

   int ret_val = setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&on,sizeof(on));
   if (ret_val < 0) {
       perror("setsockopt");
       exit(1);
   }
   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(atoi(argv[2]));
   inet_pton(AF_INET,argv[1],&servaddr.sin_addr);

   servlen = sizeof(servaddr);
   number_bytes = sendto(sockfd,sendbuf,strlen(sendbuf),MSG_DONTWAIT,(struct sockaddr *)&servaddr,servlen);

   if (number_bytes == -1) {
      perror("sendto");
      exit(1);
   }
   
   while(1){

     number_bytes = recvfrom(sockfd,recvbuf,max_len-1,0,(struct sockaddr *)&servaddr,(socklen_t *)&servlen);
     if (number_bytes ==-1 ) {
        perror("recvbuf");
     }else {

       recvbuf[number_bytes] = '\0';
       cout << "client receives message:" << recvbuf << endl;
     }
   }
   close(sockfd); 
   return 0;
}
