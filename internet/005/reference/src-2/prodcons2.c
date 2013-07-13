/* 
 Use SystemV semaphore to solve consumer and producer problem example2.
 Copyright (C) 2006, Li Suke, School of Software, Beijing University
 This  is free software; you can redistribute it and/or
 modify it freely.

 This software  is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
*/

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define	NBUFF	 3
#define MUTEX 0
#define NEMPTY 1
#define NSTORED 2

#define PERMS 0666  /* _rw_rw_rw */
union semun {
       int val;                    /* value for SETVAL */
       struct semid_ds *buf;       /* buffer for IPC_STAT, IPC_SET */
       unsigned short int *array;  /* array for GETALL, SETALL */
       struct seminfo *__buf;      /* buffer for IPC_INFO */
};

int		nitems;			
struct sto {
  int	buff[NBUFF];
};

sto shared;

void	*produce(void *), *consume(void *);
static struct sembuf mutex[2],nempty[2],nstored[2];

int semid;
int main(int argc, char **argv)
{
	pthread_t	tid_produce, tid_consume;
        int i;
	struct sembuf sem_op[6];
        key_t key;
	if (argc != 2){
           printf("Usage: prodcons number\n");
           exit(0);
        }
		
	nitems = atoi(argv[1]);
        key = (long)getpid();

        /* initialize three semaphores */
        union semun arg[3];

        /* mutex */
        arg[0].val =1;
        /* nempty */
        arg[1].val = NBUFF;
        /* nstored */
        arg[2].val = 0;
 	
        mutex[0].sem_num = 0;
        mutex[0].sem_op = -1;
        mutex[0].sem_flg = 0;

        mutex[1].sem_num = 0;
        mutex[1].sem_op =  1;
        mutex[1].sem_flg = 0;
        
        nempty[0].sem_num = 1;
        nempty[0].sem_op = -1;
        nempty[0].sem_flg = 0;
        
        nempty[1].sem_num = 1;
        nempty[1].sem_op = 1;
        nempty[1].sem_flg = 0;

        nstored[0].sem_num = 2;
        nstored[0].sem_op = -1;
        nstored[0].sem_flg = 0;
        
        nstored[1].sem_num = 2;
        nstored[1].sem_op = 1;
        nstored[1].sem_flg = 0;
 	
        /* create a semaphore set with 3 semaphores */
        if ((semid = semget(key, 3,   IPC_CREAT | PERMS)) == -1) {
            perror("semget");
            exit(1);
        }
        
        for(i=0;i<3;i++){
          if (semctl(semid, i, SETVAL, arg[i]) == -1) {
            perror("semctl");
            exit(1);
          }
        } 
        

	pthread_create(&tid_produce, NULL, produce, NULL);
	pthread_create(&tid_consume, NULL, consume, NULL);

	pthread_join(tid_produce, NULL);
	pthread_join(tid_consume, NULL);
 	    

	if (semctl(semid, 0, IPC_RMID) == -1) {
              perror("semctl rm");
              exit(1);
        } 
       
	exit(0);
}


void *produce(void *arg)
{
	int		i;
        
	for (i = 0; i < nitems; i++) {
		semop(semid,&nempty[0],1);
                semop(semid,&mutex[0],1);
		shared.buff[i % NBUFF] = i;	
                printf("Product %d\n",shared.buff[i% NBUFF]);
                /* store i into circular buffer */
		semop(semid,&mutex[1],1);
                semop(semid,&nstored[1],1);
	}
	return(NULL);
}

void *consume(void *arg)
{
	int		i;

	for (i = 0; i < nitems; i++) {
		semop(semid,&nstored[0],1);
                semop(semid,&mutex[0],1);
		if (shared.buff[i % NBUFF] != i)
			printf("buff[%d] = %d\n", i, shared.buff[i % NBUFF]);
                printf("Consumer:%d\n",shared.buff[i % NBUFF]);
		semop(semid,&mutex[1],1);
                semop(semid,&nempty[1],1);
	}
	return(NULL);
}
