#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "../sockfile.h"
#include "../print.h"
#include "../signAndEnvelop.h"

#define BUF_LEN  1024
#define PORT 6000

#define SERVERCERT "serverCert.pem"
#define SERVERPRIK "serverPrikey.pem"

int main(int argc,char *argv[]){
	int *connfd;
	int sockfd;	
	struct sockaddr_in servaddr,tempaddr,cliaddr;
	socklen_t clilen;
	socklen_t templen;
	ssize_t number_bytes;
	char * buffer[BUF_LEN];
	int flag = 1, len = sizeof(int);

	char fileInfo[INFOSIZE+1];
	char dataInfo[INFOSIZE+1];
	char filename[64];
	int fsize;
	char databuffer[4096];
	char dataOut[4096];
	int recvlen = 0;
	
	X509 *x509_cert;	//接收端证书
	RSA *rsa;			//接收端私钥	
	EVP_PKEY *pkey;

	memset(dataInfo,0,INFOSIZE+1);
	memset(fileInfo,0,INFOSIZE+1);
	memset(databuffer,0,4096);

	OpenSSL_add_all_algorithms();  // MUST

	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1){
		perror("socket");
		exit(1);
	}

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	if(setsockopt(sockfd, SOL_SOCKET,SO_REUSEADDR,&flag,len)== -1){
		perror("SOCKET OPT SET ERROR");
		exit(EXIT_FAILURE);
	}

	if(bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) == -1){
		perror("SOCKET BIND ERROR");
		exit(EXIT_FAILURE);
	}

	if(listen(sockfd,10)){
		perror("SOKCET LISTEN ERROR");	
		exit(EXIT_FAILURE);
	}; 

	while(1){
	clilen = sizeof(cliaddr);
	connfd = (int*)malloc(sizeof(int));
	if(-1 == (connfd = accept(sockfd,(struct sockaddr*)&cliaddr,&clilen))){
		if(errno == EINTR){
			perror("INTEREPTER CATCHED");		
			continue;
		}
		perror("SOCKET ACCEPT ERROR");
		exit(EXIT_FAILURE);
	}
	
	//将接收证书发送给客户端
	infoDeal(SERVERCERT,fileInfo);		
	printf("fileInfo: %s\n",fileInfo);
	sendInfo(connfd,fileInfo);
	sendfile(connfd,SERVERCERT);	

	//接收客户端的签名数字证书	
/*
	recvInfo(connfd,fileInfo);
	printf("recv fileInfo:%s\n",fileInfo);
	infoParse(fileInfo, filename, &fsize);
	printf("recv filename: %s\t filesize:%d\n",filename,fsize);	
	recvfile(connfd,filename,fsize);
	recvInfo(connfd,dataInfo);
	printf("Data Info:%s\n",dataInfo);
	infoParse(dataInfo,filename,&fsize);
	databuffer = (char*)malloc(fsize+1);
	memset(databuffer,0,fsize+1);
*/	

	recvlen = recvData(connfd,databuffer);		
	printf("recv databuffer:%s\n",databuffer);

	recvlen = recvData(connfd,databuffer);		
	printf("recv databuffer:%s\n",databuffer);

	rsa = read_RSA_Prikey(SERVERPRIK,PEM);		
	printf("************ 服务端私钥 ************\n");
	RSA_print_fp(stdout,rsa,1);
	pkey = EVP_PKEY_new();
	EVP_PKEY_assign_RSA(pkey,rsa);
	
//	ssl_PKCS7_get_Signed_Enveloped_data_from_p7file("signedAndEnveloped.p7",pkey,NULL);
	
	ssl_PKCS7_get_data_from_signed_and_enveloped_der(databuffer,recvlen,pkey,dataOut);
		
	}  //while end
	return 0;
}


