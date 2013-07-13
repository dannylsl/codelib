// 
// FIFO client
// Copyright (C) 2006, Li Suke, School of Software and Microelectronics, 
// Beijing University
// This  is free software; you can redistribute it and/or
// modify it freely.

// This software  is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
//

#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>
#include <cstring>

#define FIFO1 "fifo11"
#define FIFO2 "fifo12"
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define BUFFER_LEN 1024

using namespace std;

int main(int argc, char* argv[])
{
   int readfd, writefd;
   int read_num;
   const char* hello = "hello world!";
   char buf[BUFFER_LEN];

   if ((mkfifo(FIFO1, FILE_MODE) < 0) && (errno != EEXIST)){
      perror("mkfifo");
      exit(1);
   }
   if ((mkfifo(FIFO2, FILE_MODE) < 0) && (errno != EEXIST)) {
      perror("mkfifo");
      unlink(FIFO1);
      exit(1);
   }
  
   readfd = open(FIFO1,O_RDONLY);
   cout << "e" << endl;
   writefd = open(FIFO2,O_WRONLY);
   cout << "f" << endl;
   
   cout <<"e" << endl; 
   write(writefd,hello,strlen(hello));
   
   read_num = read(readfd,buf,strlen(hello));
   buf[read_num] = '\0';
   cout << "Client received the server's echo:" << endl;
   cout << buf << endl;

   close(readfd);

   close(writefd);
   unlink(FIFO1);
   unlink(FIFO2);
   sleep(10);
   return 0;
}
