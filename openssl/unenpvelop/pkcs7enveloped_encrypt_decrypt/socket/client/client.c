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

#define CLIENTCERT		"clientCert.pem"
//#define CLIENTPRIKDER	"prikey.der"
#define CLIENTPRIKPEM	"clientPrikey.pem"
#define DATAFILE		"data.txt"

#define PORT 6000

int main(int argc, char *argv[]){
	int sockfd;
	int conn_ret;
	struct sockaddr_in servaddr;
	char filename[64];
	char fileInfo[INFOSIZE+1];
	int fsize;
	
	RSA *rsa = NULL;
	EVP_PKEY *pkey = NULL;
	X509 *x509_cert = NULL;

	OpenSSL_add_all_algorithms();

	if(argc != 2){
		printf("Usage: %s <address> \n",argv[0]);
		return 0;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port= htons(PORT);
	inet_pton(AF_INET,argv[1], &servaddr.sin_addr);

	if((sockfd = socket(AF_INET, SOCK_STREAM,0 )) == -1){
		perror("SOCKET ERROR");
		exit(EXIT_FAILURE);
	}

	conn_ret = connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	if(conn_ret == -1){
		perror("CONNECT ERROR");
		exit(EXIT_FAILURE);
	}

	printf("client starting...\n");
	//接收服务端证书
	printf("receiving cert from server\n");
	recvInfo(sockfd,fileInfo);	
	printf("recv fileInfo:%s\n",fileInfo);
	infoParse(fileInfo,filename,&fsize);	
	printf("recv filename:%s\tfilesize:%d\n ",filename,fsize);
	recvfile(sockfd,filename,fsize);

	//获取客户端密钥,用于签名
	printf("reading client private key\n");
	//rsa = read_RSA_Prikey(CLIENTPRIKDER,DER);		
	rsa = read_RSA_Prikey_PEM(CLIENTPRIKPEM);
	pkey = EVP_PKEY_new();
	EVP_PKEY_assign_RSA(pkey,rsa);
	//获取客户端的证书
	x509_cert = read_pem_certification(CLIENTCERT);
	//生成签名数字信封
	printf("Generating Signed And Enveloped data\n");

	ssl_PKCS7_signed_and_enveloped_from_file(pkey,NULL,x509_cert,filename,PEM,DATAFILE);

	printf("Send Signed And Enveloped data file from client to server\n");
	infoDeal("signedAndEnveloped.p7",fileInfo);	
	printf("fileInfo:%s\n",fileInfo);	
	sendInfo(sockfd,fileInfo);
	sendfile(sockfd,"signedAndEnveloped.p7");

	return 0;
}
