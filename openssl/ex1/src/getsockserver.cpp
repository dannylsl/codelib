
#include <cstdlib>
#include <cerrno>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

using namespace std;

#define BACKLOG 10
int main(int argc, char* argv[])
{
   int connfd, sockfd;
   struct sockaddr_in servaddr;
   struct sockaddr_in return_addr;
   struct sockaddr_in cliaddr;
   socklen_t return_len;

   socklen_t clilen;
   int ret_val;
   
   sockfd = socket(AF_INET, SOCK_STREAM,0);
   if (sockfd  == -1) {
      perror("socket");
      exit(1);
   } 
   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 //  servaddr.sin_port = htons(2000);
   ret_val = bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
   if(ret_val == -1)
   {
      perror("bind");
      exit(1);
   }


   if (listen(sockfd,BACKLOG) == -1){
      perror("listen");
      exit(1);
   }
   if (getsockname(sockfd,(struct sockaddr *)&return_addr,&return_len)==-1){
      perror("getsockname");
      exit(1);
   }
   cout <<"The server ipaddr is " << inet_ntoa(return_addr.sin_addr) << endl;
   cout <<"The server port is " << ntohs(return_addr.sin_port) << endl;
	
   for(;;){
      clilen = sizeof(cliaddr);
      connfd = accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);
      if(connfd == -1){
         perror("accept");
         continue;
      }
      cout << "Server: client %s" << inet_ntoa(cliaddr.sin_addr) << "connected " << endl;
      close(connfd);  
   }
   return 0;
}
