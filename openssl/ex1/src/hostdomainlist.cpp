/* 
 Get the host's domains.
 Copyright (C) 2006, Li Suke, 
 School of Software and Microelectronics,Beijing University
 This  is free software; you can redistribute it and/or
 modify it freely.

 This software  is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
*/
#include <cerrno>
#include <cstdlib>

#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
   struct hostent *h;
   char **hp;
   int i;
   struct in_addr ip;

   if (argc != 2) {

       cout << "Usage: hostdomainlist <ip address>" << endl;
       exit(1);
   }
  
   if( inet_pton(AF_INET,argv[1],&ip) == -1){
       perror("inet_pton");
       exit(1);
   }
   
   h = gethostbyaddr((const char *)&ip,sizeof(ip),AF_INET);
   if (h == 0){
      herror("gethostbyname");
      exit(1);
   }
   cout << "domain name is " << h->h_name << endl;
  
   hp = h->h_aliases;

   for(;*hp != 0; hp++)
      cout << "alias " << *hp;

   for(i=0; h->h_aliases[i] != 0;i++) {
      cout << "The alias is " << h->h_aliases[i] << endl;
     
   }	
   return 0;

}
