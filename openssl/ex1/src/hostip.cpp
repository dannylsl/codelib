/* 
 Get the host's IP.
 Copyright (C) 2006, Li Suke, School of Software,Peking University
 This  is free software; you can redistribute it and/or
 modify it freely.

 This software  is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
*/

#include <cerrno>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) 
{
   struct hostent *h;
   char ip_str[INET_ADDRSTRLEN];
   const char *p = NULL;

   if (argc != 2) {
       cout << "Usage: hostip <domain name>" << endl;
       exit(1);
   }
   
   h = gethostbyname(argv[1]);
   if(h == 0) {
      herror("gethostbyname");
      exit(1);
   }

   /* inet_ntop(), tries to convert numberic address to presentation string */ 
   p=inet_ntop(AF_INET,((struct in_addr *)h->h_addr), ip_str, INET_ADDRSTRLEN);

   if (p != 0){
      cout <<"Host name is :" << h->h_name;
      cout <<"IP Address is :"<< ip_str;

   }else{
      perror("inet_ntop");
   }
   return 0;
}
