// 
// This example come from the source code of 
// <Unix Network Programming,volume 1>
//
// Copyright (C) 2006, Li Suke, School of Software and Microelectronics,
//   Beijing University
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
#include <cerrno>
#include <sys/select.h>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

#define BUF_SIZE 1024

int str_cli(FILE *fp, int sockfd)
{
    
   int maxfdp1, stdineof = 0;
   int len;
   fd_set rset;

   char	sendline[BUF_SIZE], recvline[BUF_SIZE];

   FD_ZERO(&rset);
  
   for ( ; ; ) {
    
     FD_SET(sockfd, &rset);
     if (stdineof == 0)
        FD_SET(fileno(fp), &rset);

     if(fileno(fp) > sockfd)
       maxfdp1= fileno(fp)+1;
     else
       maxfdp1 = sockfd+1;
     
     select(maxfdp1, &rset, NULL, NULL, NULL);
     len = BUF_SIZE;
     if (FD_ISSET(sockfd, &rset)) {	// socket is readable 
        len = recv(sockfd, recvline, len,0);
        if(len ==0)
        {
           if (stdineof == 1)
	      return 0;		/// normal termination 
           else{
              cout <<"server terminated prematurely" << endl;
              return -1;
           }			
        }   
        fputs(recvline, stdout);
     }
 
     if (FD_ISSET(fileno(fp), &rset)) {  // input is readable 
       len = BUF_SIZE;
       if (fgets(sendline, BUF_SIZE, fp) == NULL) {
         stdineof = 1;
         shutdown(sockfd, SHUT_WR);	// send FIN 
         FD_CLR(fileno(fp), &rset);
         continue;
       }
       send(sockfd, sendline, len,0);
     }
   }
   return 0;
}
int main(int argc, char **argv)
{
   int sockfd;
   int ret_val;
   struct sockaddr_in	servaddr;
   char buffer[BUF_SIZE];
   if (argc != 3){
       cout << "Usage:echocli <port>" << endl;
       exit(1);
   }

   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0) {
      perror("socket");
      exit(1);
   }

   bzero(&servaddr, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(atoi(argv[2]));
   ret_val =  inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

   if (ret_val <= 0) {
     perror("inet_pton");
     exit(1);
   } 

   ret_val = connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));
   if (ret_val == -1) { 
      perror("connect");
      exit(1);
   };

   ret_val = str_cli(stdin, sockfd);
   if (ret_val < 0) {
      exit(1);
   }
   return 0;
}

