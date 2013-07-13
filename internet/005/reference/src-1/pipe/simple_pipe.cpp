// 
// Simple pipe applicaiton.
// Copyright (C) 2006, Li Suke, School of Software and Microelectronics,
// Beijing University
// This  is free software; you can redistribute it and/or
// modify it freely.

// This software  is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 


#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <cstdlib>
using namespace std;

int main(void)
{
   int fd[2];
   char buf[4096];
   int n;
   const char* hello = "hello world!";
   pipe(fd);
   
   n = write(fd[1],hello,strlen(hello));
   if (n < 0) {
      perror("write");
      exit(1);
   }
   n =read(fd[0],buf,strlen(hello));
   if (n < 0) {
      perror("read");
      exit(1);
   }
   buf[n]='\0';
   cout << "The buf is " << buf << endl;
   return 0;

}
