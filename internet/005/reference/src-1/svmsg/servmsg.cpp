// 
// SystemV Message queue server
// Copyright (C) 2006, Li Suke, School of Software and Microelectronics,
// Beijing University
// This  is free software; you can redistribute it and/or
// modify it freely.

// This software  is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 


#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <cstring>
#include <cerrno>
#include "mymsg.h"
#define SVMSG_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
using namespace std;

int msqid;
void sighandler(int signo)
{
    msgctl(msqid, IPC_RMID, NULL);
    exit(0);
}


int main () 
{
    struct my_msgbuf rec_mesg;
    int len;
    long key;
    int n;
    signal(SIGINT, sighandler);
    signal(SIGTERM,sighandler);
    
    key = getpid();
    
    msqid = msgget(key, IPC_CREAT | SVMSG_MODE);
    if (msqid < 0) {
       perror("msgget");
       exit(1);
    }

    cout << "The message queue key is " << key << endl;
    cout << "The message queue id is " << msqid << endl;
    rec_mesg.msg_type = 1;
    
    n = msgrcv(msqid,&(rec_mesg.msg_type), MAX_MSG_DATA_LENGTH, rec_mesg.msg_type, 0);
    rec_mesg.msg_data[n] = '\n';
    cout << "Read from the client: " << rec_mesg.msg_data << endl;
    sleep(10);
    msgctl(msqid, IPC_RMID, NULL);
    return 0;
}

