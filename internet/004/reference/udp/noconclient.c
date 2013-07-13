/* 
 A simple udp client program which  do not call  connect().
 If the server is not up, the client is blocking for ever!
 
 Copyright (C) 1994-1995, Li Suke, School of Software,Peking University
 This  is free software; you can redistribute it and/or
 modify it freely.

 This software  is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_LEN 1024
int main(int argc, char *argv[]){
   int sockfd;
   struct sockaddr_in servaddr;
   const char *sendbuf = "hello world!";
   char recvbuf[MAX_LEN];
   int number_bytes;
   int servlen;
   int on = 1;
   if(argc != 3){
      printf("Usage: noconclient <address> <port>\n");
      return 0;
   }
   if((sockfd = socket(AF_INET,SOCK_DGRAM,0)) == -1){
       perror("sock");
       exit(1);
   }
   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(atoi(argv[2]));
   inet_pton(AF_INET,argv[1],&servaddr.sin_addr);

   servlen = sizeof(servaddr);
   if (sendto(sockfd,sendbuf,strlen(sendbuf),MSG_DONTWAIT,(struct sockaddr *)&servaddr,servlen)== -1){
      perror("sendto");
      exit(1);
   }
   
   while(1){
       if ((number_bytes = recvfrom(sockfd,recvbuf,MAX_LEN-1,0,
                         (struct sockaddr *)&servaddr,&servlen))==-1)
       {
           perror("recvbuf");
           continue;
       }else{
           recvbuf[number_bytes] = '\0';
           printf("client receives message:%s\n",recvbuf);
       }
   }
   close(sockfd); 
   return;
}
