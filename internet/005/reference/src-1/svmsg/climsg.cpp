// 
// SystemV message queue client
// Copyright (C) 2006, Li Suke, School of Software and Microelectronics,
// Beijing University
// This  is free software; you can redistribute it and/or
// modify it freely.

// This software  is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
//

#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>
#include "mymsg.h"

#define SVMSG_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

using namespace std;

int main (int argc, char*argv[]) 
{
    int msqid;
    struct my_msgbuf mesg;
    int len;
    long key;
    int n;
    char *hello = "hello world!";

    if(argc != 2){
       cerr << "Usage: sendmsg key" << endl;
       exit(1);
    }
    //msqid = atol(argv[1]);
    key = atol(argv[1]);
    msqid = msgget(key,0);
    
    if(msqid < 0) {
       perror("msgget");
       exit(1);
    }
    len = strlen(hello);
    memcpy(mesg.msg_data,hello,len);
    mesg.msg_data[len] ='\0';
    mesg.msg_type = 1;
    mesg.msg_len = len;
    msgsnd(msqid,&(mesg.msg_type),len,0);
    return 0;
}

