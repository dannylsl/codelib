// This is the simplest reference for homework5,
//   I hope it is useful for you.
// Copyright (C) 2004-2006, Li Suke, School of Software and Microelectronics,
// Peking University
// This  is free software; you can redistribute it and/or
// modify it freely.
//
// This software  is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 


#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cerrno>
#include <iostream>

using namespace std;

#define MAX_BUF_SIZE 1024
int main(int argc, char *argv[]) 
{
	int sockfd;
	int n;
	int ret_val;

	unsigned int seq;
	unsigned int ts;

	char recvbuf[MAX_BUF_SIZE];
	struct sockaddr_in servaddr;

	struct hdr {
		unsigned int seq;
		unsigned int ts;
	} recvhdr;

	struct iovec iovrecv[2];

	struct msghdr msgrecv;
	if (argc != 2) {
		cout << "usage udpserv <port>" << endl;
		exit(1);
	}

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_port = htons(atoi(argv[1]));
	servaddr.sin_addr.s_addr = ntohl(INADDR_ANY);

	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if (sockfd < 0) {
		perror("socket");
		exit(1);
	}

	ret_val = bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if (ret_val < 0) {
		perror("bind");
		exit (1);
	}

	msgrecv.msg_name = &servaddr;
	msgrecv.msg_namelen = sizeof(servaddr);

	msgrecv.msg_iov = iovrecv;
	msgrecv.msg_iovlen = 2;

	iovrecv[0].iov_base = &recvhdr;
	iovrecv[0].iov_len = sizeof(struct hdr);

	iovrecv[1].iov_base = recvbuf;
	iovrecv[1].iov_len = MAX_BUF_SIZE;

	for(;;) {
		n = recvmsg(sockfd, &msgrecv, 0);
		if (n < 0) {
			perror ("recvmsg");
			continue;
		} else {
			seq = recvhdr.seq;
			ts = recvhdr.ts;
			cout << "seq is " << seq << endl;
			cout << "ts is " << ts << endl;
			cout << recvbuf << endl;

			n = sendmsg(sockfd,&msgrecv,0);
			if (n < 0) {
				perror("sendmsg");
				continue;
			}
		}
	}

	return 0;
}
