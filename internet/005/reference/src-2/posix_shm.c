/* 
 POSIX shared memory example.
 Copyright (C) 2006, Li Suke, School of Software and Microelectronics,
 Beijing University
 This  is free software; you can redistribute it and/or
 modify it freely.

 This software  is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <wait.h>

#define FILE_MODE 0666
#define RECORD_NUMBER 10
int main(int argc, char *argv[]) {
   int fd;
   char *ptr;
   pid_t pid; 

   int i;
   int status;
   if(argc != 2) {
      printf("Usage: simple_shm <name>\n");
      exit(1);
   }
     
   if ((fd = shm_open(argv[1], O_RDWR | O_CREAT,FILE_MODE)) == -1) {
      perror("shm_open");
      exit(1);
   }
   printf("the fd is %d\n",fd);
   ftruncate(fd,RECORD_NUMBER*sizeof(char));
   ptr = (char *)mmap(NULL,RECORD_NUMBER*sizeof(char),PROT_READ | PROT_WRITE ,MAP_SHARED,fd,0);
   if(ptr == (char*)(-1)){
      perror("mmap");
      exit(1);
   }
  
   printf("The parent process share memory address is %p\n",ptr);
  
   for(i=0; i<RECORD_NUMBER; i++){
       *ptr = i;
        ptr++;
   }
   pid = fork();
   if (pid < 0) {
      perror("fork");
      shm_unlink(argv[1]);
      exit(1);
   }

   if(pid == 0) {

      char *child_ptr;
      child_ptr = (char *)mmap(NULL,RECORD_NUMBER*sizeof(char),PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
      printf("Child process shared memory address %p\n",child_ptr);
      if (child_ptr == (char*)(-1)) {
         perror("child:mmap");
         exit(1);
      }
      close(fd);
      for(i=0;i<RECORD_NUMBER;i++)
         printf("child_ptr[%d]=%d\n",i,(*child_ptr++));
      //munmap(child_ptr,RECORD_NUMBER*sizeof(char));
      exit(0);

   }

   wait(&status);

   close(fd);
   shm_unlink(argv[1]);
   exit(0);

}
