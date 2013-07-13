//
// FIFO server 
// Copyright (C) 2006, Li Suke, School of Software and Microelectronics, 
// Beijing University
// This  is free software; you can redistribute it and/or
// modify it freely.

// This software  is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cerrno>
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
   cout << "a" << endl;
   writefd = open(FIFO1, O_WRONLY);
   cout << "b" << endl;
   readfd = open(FIFO2, O_RDONLY);
   cout << "c" << endl;
   read_num = read(readfd,buf,sizeof(buf));
   write(writefd,buf,read_num);
   
   close(readfd);
   close(writefd);
   unlink(FIFO1);
   unlink(FIFO2);
   return 0;
}
