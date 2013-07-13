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
#include <unistd.h>
#include <cerrno>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wait.h>

#define FIFO1 "fifo11"
#define FIFO2 "fifo12"
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define BUFFER_LEN 1024

using namespace std;

int main(int argc, char* argv[])
{
   int readfd, writefd;
   int read_num;
   pid_t pid;
   int status;
   char buf[BUFFER_LEN];
   const char *hello= "Hello,world!";
   if ((mkfifo(FIFO1, FILE_MODE) < 0) && (errno != EEXIST)){
      perror("mkfifo");
      exit(1);
   }
   if ((mkfifo(FIFO2, FILE_MODE) < 0) && (errno != EEXIST)) {
      perror("mkfifo");
      unlink(FIFO1);
      exit(1);
   }
   if((pid=fork())==0) {
      writefd = open(FIFO1, O_WRONLY);
      readfd = open(FIFO2, O_RDONLY);
      read_num = read(readfd,buf,sizeof(buf));
      write(writefd,buf,read_num);
      close(readfd);
      close(writefd);
   } else {
      readfd = open(FIFO1,O_RDONLY);
      writefd = open(FIFO2,O_WRONLY);

      write(writefd,hello,strlen(hello));

      read_num = read(readfd,buf,strlen(hello));
      buf[read_num] = '\0';
      cout << "Client received the server's echo:" << endl;
      cout << buf << endl;

      close(readfd);
      close(writefd);

      unlink(FIFO1);
      unlink(FIFO2);
      waitpid(pid, &status, 0);
   }
   return 0;
}
