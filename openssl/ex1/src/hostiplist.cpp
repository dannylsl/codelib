/* 
 Get the host's multiple IPs.
 Copyright (C) 2006, Li Suke, School of Software,Peking University
 This  is free software; you can redistribute it and/or
 modify it freely.

 This software  is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
*/


#include <cstdlib>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cerrno>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
   struct hostent *h;
   char **hp;
   const char *p = 0;

   char ip_str[INET_ADDRSTRLEN];

   int i = 0 ;

   if (argc != 2) {
       cout << "Usage:hostiplist <hostname> " << endl;
       exit(1);
   }

   h = gethostbyname(argv[1]);
   if (h == 0) {
      herror("gethostbyname");
      exit(1);
   }
  
   hp = h->h_addr_list;

   /* We can get the ip address list in this way: */
   for(; *hp!= 0; hp++){
      p = inet_ntop(AF_INET,(*(struct in_addr **)hp),
                    ip_str,INET_ADDRSTRLEN);
      if (p != 0) {
          cout <<"get ip:" << ip_str << endl; 
      }
   }
   /* We also can get the ip address list in another way: */
   for(i=0;h->h_addr_list[i]!=0 ;i++){
      p=inet_ntop(AF_INET,((struct in_addr *)h->h_addr_list[i]),
                           ip_str,INET_ADDRSTRLEN);
      if (p != 0) { 
         cout << "other ip:"<<ip_str << endl;
      }
   }
   cout << "office domain name is "<< h->h_name << endl;
   /* We also can get the alias domain name: */
   for(i=0;h->h_aliases[i]!=0; i++){
      cout << "alias is " <<  h->h_aliases[i] << endl;
   }
   return 0;
}
