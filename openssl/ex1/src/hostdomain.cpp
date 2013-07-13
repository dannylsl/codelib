/* 
 Get the host's IP.
 Copyright (C) 2006, Li Suke, School of Software and Microelectronics,
 Peking University
 
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

int main(int argc, char *argv[]) {

   struct hostent *h;
   struct in_addr ip;
   int ret_val;

   if (argc != 2) {
       cout << "Usage: hostdomain <ip address> " << endl;
       exit(0);
   }

   // get the numeric ip address from presentation ip address string 
   // Please pay attention: if inet_pton succeeds return a value,
   // the value is a positive value, not 0.
 
   ret_val = inet_pton(AF_INET, argv[1], &ip);
   if(ret_val == -1 || ret_val == 0)
   {
       perror("inet_pton");
       exit(1);
   }

   // ok, it is time to call gethostbyaddr()  
   h = gethostbyaddr((const char *)&ip, sizeof(ip), AF_INET);

   if (h == NULL) {

      herror("gethostbyname");
      exit(1);
   }
   cout << "domain name is " << h->h_name << endl;
   return 0;
}
