// 
// Parent and child processes communicate with each other with pipes
// Copyright (C) 2006, Li Suke, School of Software and Microelectronics,
// Beijing University
// This  is free software; you can redistribute it and/or
// modify it freely.

// This software  is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
//

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <cerrno>

using namespace std;
int main()
{
   int fd[2];
   char buf[4096];
   int n;
   pid_t pid;
   int status;
   const char* hello = "hello world!";
   pipe(fd);
   pid = fork();
   if(pid < 0){
     perror("fork");
     exit(0);
   }
   if(pid ==0) {
      close(fd[0]);
      write(fd[1], hello, strlen(hello));
      exit(0);
   } else{
      close(fd[1]);
      wait(&status);
      n =read(fd[0], buf, strlen(hello));
      buf[n]='\0';
      cout << "The buf is " << buf << endl;
   }
   return 0;
}
