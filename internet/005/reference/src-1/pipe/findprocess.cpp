// 
// Find the process whose name is your one of your arguments passed.
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
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <cerrno>

using namespace std;

int main(int argc, char* argv[])
{
   pid_t pid;
   int fd[2];
   int status;
   char buf[4096];
   int i;
   int test;
   pipe(fd);

   if(argc != 2){
     cerr << "Usage: findprocess <name>" << endl;
     exit(1);
   }
   pid = fork();
   if(pid < 0){
     perror("fork");
     exit(1);
   }
   if (pid == 0){
    
     close(0);
     close(fd[1]);
     test =dup2(fd[0],0);
     execl("/bin/grep", "grep", argv[1], NULL); 
     
   }else{
  
     close(1);
     dup2(fd[1],1);
     close(fd[0]);
     execl("/bin/ps", "ps", "-ef", NULL);
     wait(&status);
     exit(0);
   }
   return 0;
}
