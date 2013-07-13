/* This file is modified from example source code of
  <<unix network programming, volumne2>>
  sh/incr2.c
  I just change the POSIX semphore to System v semphore in linux
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>
#define PERMS 0666  /* _rw_rw_rw */
union semun {
       int val;                    /* value for SETVAL */
       struct semid_ds *buf;       /* buffer for IPC_STAT, IPC_SET */
       unsigned short int *array;  /* array for GETALL, SETALL */
       struct seminfo *__buf;      /* buffer for IPC_INFO */
};


int main(int argc, char **argv)
{
   int		fd, i, nloop, zero = 0;
   int		*ptr;
   key_t key;
   key = (long)getpid();
   union semun  arg;
   struct sembuf postop,waitop;
   int semid;
   if (argc != 3){
      printf("usage: mmap  <filename> <#loops>\n");
      exit(0);
   }

   if((semid=semget(key,1,IPC_CREAT | PERMS))<0){
      perror("semget");
      exit(1);
   }
   printf("The sem id is %d\n",semid);
   arg.val = 1;
   if (semctl(semid, 0, SETVAL, arg) == -1) {
      perror("semctl");
      exit(1);
   }

   postop.sem_num = 0;
   postop.sem_op = 1;
   postop.sem_flg = SEM_UNDO;

   waitop.sem_num = 0;
   waitop.sem_op = -1;
   waitop.sem_flg = SEM_UNDO;
   nloop = atoi(argv[2]);


   fd = open(argv[1], O_RDWR | O_CREAT, PERMS);
   write(fd, &zero, sizeof(int));
   ptr = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
   close(fd);
   
   setbuf(stdout, NULL);	/* stdout is unbuffered */
   if (fork() == 0) {		/* child */
	for (i = 0; i < nloop; i++) {
            semop(semid,&waitop,1);
            printf("child: %d\n", (*ptr)++);
	    semop(semid,&postop,1);	
	}
	exit(0);
   }
   for (i = 0; i < nloop; i++) {
        semop(semid,&waitop,1);  	    	
	printf("parent: %d\n", (*ptr)++);
	semop(semid,&postop,1);	
   }
   semctl(semid,0,IPC_RMID);
   exit(0);
}

