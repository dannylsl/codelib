/* fileName: chatServ.cpp
 * author: danny lee
 * Email : dannylsl@pku.edu.cn
 * Description:
 *	UDP client for chatroom with I/O multiplexing
 * */
#include <cerrno>
#include <cstring>
#include <cstdlib>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <cstdio>

#include <iostream>
using namespace std;

const int PORT = 55432;
const int MAX_LEN = 1024;

void printErr(const char* title){
	cerr<<title<<strerror(errno)<<endl;
}

int str_cli(FILE*fp,int sockfd){
	int maxfdp1,stdineof = 0;
	int len;
	fd_set rset;

	char sendline[MAX_LEN], recvline[MAX_LEN];

	FD_ZERO(&rset);

	while(1){
		FD_SET(sockfd, &rset);
			if(stdineof == 0)
				FD_SET(fileno(fp),&rset);

			if(fileno(fp) > sockfd)
				maxfdp1 = fileno(fp) + 1;
			else
				maxfdp1 = sockfd + 1;

			select(maxfdp1, &rset, NULL,NULL,NULL);
			len = MAX_LEN;
			if(FD_ISSET(sockfd, &rset)){
				len = recv(sockfd,&rset, len,0);
				if(len == 0){
					if(stdineof == 1)
						return 0;
					else{
						cout << "Server terminated permaturely" <<endl;
						return -1;
					}
				}
				fputs(recvline,stdout);
			}

			if(FD_ISSET(fileno(fp), &rset)){
				len = MAX_LEN;
				if(fgets(sendline, MAX_LEN, fp) == NULL){
					stdineof = 1;
					shutdown(sockfd, SHUT_WR);
					FD_CLR(fileno(fp),&rset);
					continue;
				}
				send(sockfd,sendline,len,0);
			}
	}
	return 0;
	
}

int main(int argc, char **argv)
{
   int sockfd;
   int ret_val;
   struct sockaddr_in	servaddr;
   //char buffer[MAX_LEN];
   if (argc != 3){
       cout << "Usage:chatCli <address> <username> " << endl;
       exit(1);
   }

   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0) {
      perror("socket");
      exit(1);
   }

   bzero(&servaddr, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(PORT);
   inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

   if((sockfd== socket(AF_INET, SOCK_STREAM, 0)) == -1){
		printErr("Sock Error");	
		exit(EXIT_FAILURE);
   }

   ret_val = connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));
   if (ret_val == -1) { 
      perror("connect");
      exit(1);
   };

   ret_val = str_cli(stdin, sockfd);
   if (ret_val < 0) {
      exit(1);
   }
   return 0;
}

/*
int main(int argc,char*argv[]){
	int sockfd;
	int conn_ret;
	struct sockaddr_in servaddr;
	
	char sendbuf[MAX_LEN], recvbuf[MAX_LEN];
	int number_bytes;

	if(argc != 3){
	
		cout<<"Usage:"<<argv[0]<<" <address> <username>"<<endl;
		return 1;
	}
	
	sockfd = socket(AF_INET, SOCK_DGRAM,0);
	if(sockfd == -1){
		printErr("socket error");
		exit(EXIT_FAILURE);
	}

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	inet_pton(AF_INET,argv[1],&servaddr.sin_addr);

	conn_ret = connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	if(conn_ret == -1){
		printErr("connect error");	
		exit(EXIT_FAILURE);
	}

	cout << "UDP BASED CHATROOM CONNECTED"<<endl;
	cout << "Say anything if u want"<<endl;
	cin  >> sendbuf;
	cout << endl;

	number_bytes = send(sockfd,sendbuf,strlen(sendbuf),0);

	if(number_bytes == -1){
		printErr("send error");
		exit(EXIT_FAILURE);
	}

	number_bytes = recv(sockfd,recvbuf,MAX_LEN-1,0);

	if(number_bytes == -1){
		printErr("recv error");
		exit(EXIT_FAILURE);
	}else{
		recvbuf[number_bytes] = '\0';
		cout<< "client receives message:"<<recvbuf<<endl;
	}
	close(sockfd);
	return 0;
	
	

}

*/
