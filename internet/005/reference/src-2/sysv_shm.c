/* 
 SystemV shared memory example.
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
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <wait.h>

#define PERMS 0666
#define SHM_SIZE 10
int main(int argc, char *argv[])
{
        key_t key;
        int shmid;
        char *ptr;
        int i ;
        pid_t pid;
        int status;
        
        key = (long)getpid();
 
        if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | PERMS)) == -1) {
            perror("shmget");
            exit(1);
        }

        ptr = (char *) shmat(shmid, NULL, 0);
        printf("parent process shared memory address is %p\n",ptr);
        for(i=0;i<10;i++){
            *ptr++ = i;
        }
        if (ptr == (char *)(-1)) {
            perror("shmat");
            exit(1);
        }
        
        pid = fork();
        if(pid == 0){
            ptr = (char *)shmat(shmid, NULL, 0);
            printf("child process shared memory address is %p\n",ptr);
            for(i=0;i<SHM_SIZE;i++){
               printf("child_ptr[%d]=%d\n",i,*ptr++);
            }
            shmdt(ptr); 
            exit(0);
        } 
        shmdt(ptr);
        wait(&status);
       
        shmctl(shmid,IPC_RMID,NULL);
      
        return 0;
    }

