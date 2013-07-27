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

X509 *x509_cert;	//接收端证书
RSA *rsa;			//接收端私钥	
EVP_PKEY *pkey;

ssize_t myrecvData(int sockfd,int filesize,char *timestamp);
int main(int argc,char *argv[]){
	int connfd;
	int sockfd;	
	struct sockaddr_in servaddr,tempaddr,cliaddr;
	socklen_t clilen;
	socklen_t templen;
	ssize_t number_bytes;
	char * buffer[BUF_LEN];
	int flag = 1, len = sizeof(int);

	char fileInfo[INFOSIZE+1];
	char filename[64];
	int fsize;
	
	strcpy(filename,"clientfile.t");
        addSocketfdToFileName(filename,4);
        printf("filename=%s\n",filename);


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
	if(-1 == (connfd = accept(sockfd,(struct sockaddr*)&cliaddr,&clilen))){
		if(errno == EINTR){
			perror("INTEREPTER CATCHED");		
			continue;
		}
		perror("SOCKET ACCEPT ERROR");
		exit(EXIT_FAILURE);
	}
	char *timestamp=createTimeStamp();
        printf("timestamp:%s\n",timestamp);
        sendTimestamptoClient(connfd,timestamp);
	//将接收证书发送给客户端
	infoDeal(SERVERCERT,fileInfo);		
	printf("fileInfo: %s\n",fileInfo);
	sendInfo(connfd,fileInfo);
	sendfile(connfd,SERVERCERT);	

	//接收客户端的签名数字证书	
	recvInfo(connfd,fileInfo);
	printf("recv fileInfo:%s\n",fileInfo);
	infoParse(fileInfo, filename, &fsize);
	printf("recv filename: %s\t filesize:%d\n",filename,fsize);	
	//recvfile(connfd,filename,fsize);

	rsa = read_RSA_Prikey(SERVERPRIK,PEM);		
	printf("************ 服务端私钥 ************\n");
	RSA_print_fp(stdout,rsa,1);
	pkey = EVP_PKEY_new();
	EVP_PKEY_assign_RSA(pkey,rsa);
        printf("before ...recvData,connfd=%d,fsize=%d\n",connfd,fsize);
        printf("in recvData ........................\n");
	unsigned char recvbuf[BUFSIZE];
	ssize_t number_bytes;
	int ret,restsize;
        restsize=fsize;
/*
        while(restsize>0)
        {
              printf("in while\n");
              memset(recvbuf,0,BUFSIZE);	
			if(restsize > BUFSIZE ){
				if((number_bytes = recv(connfd, recvbuf, BUFSIZE,0))==-1){
					perror("recvfile	recv() error");
					return -1;
				}else{
					ssl_PKCS7_get_Signed_Enveloped_data_from_charArr(recvbuf,pkey,NULL);			
					restsize -= number_bytes;
				}
			}else if(restsize == 0){
				break;
			}else{
                                printf("restsize < BUFSIZE\n");
				if((number_bytes = recv(connfd, recvbuf, restsize,0)) == -1){
					perror("recvfile	recv() error");
					return -1;
				}else{
                                         printf("before get_Signed_Enveloped_data_from_charArr\n");
					ssl_PKCS7_get_Signed_Enveloped_data_from_charArr(recvbuf,pkey,NULL);
					restsize -= number_bytes;
				}
			}
            
        }
*/
        myrecvData(connfd,fsize,timestamp);
	
	//ssl_PKCS7_get_Signed_Enveloped_data_from_p7file("signedAndEnveloped.p7",pkey,NULL);
		
	}  //while end
	return 0;
}

ssize_t myrecvData(int sockfd,int filesize,char *timestamp){
	printf("in recvData ........................\n");
	unsigned char recvbuf[BUFSIZE];
	ssize_t number_bytes;
	int ret,restsize;
  
	restsize = filesize;
        int sum=0;
        while(restsize>0)
        {
              printf("in while\n");
              memset(recvbuf,0,BUFSIZE);	
			if(restsize > BUFSIZE ){
				if((number_bytes = recv(sockfd, (unsigned char *)(recvbuf+sum), BUFSIZE,0))==-1){
					perror("recvfile	recv() error");
					return -1;
				}else{
					//ssl_PKCS7_get_Signed_Enveloped_data_from_charArr(recvbuf,pkey,NULL);			
                                        sum+=number_bytes;
					restsize -= number_bytes;
				}
			}else if(restsize == 0){
				break;
			}else{
                                printf("restsize < BUFSIZE,restsize=%d,bufsize=%d\n",restsize,BUFSIZE);
				if((number_bytes = recv(sockfd, (unsigned char *)(recvbuf+sum), restsize,0)) == -1){
					perror("recvfile	recv() error");
					return -1;
				}else{
                                         printf("number_bytes is %d\n",number_bytes);
                                         printf("before get_Signed_Enveloped_data_from_charArr\n");
					//ssl_PKCS7_get_Signed_Enveloped_data_from_charArr(recvbuf,pkey,NULL);
                                        sum+=number_bytes;
					restsize -= number_bytes;
                                        printf(",restsize=%d,bufsize=%d\n",restsize,BUFSIZE); 
				}
			}
            
        }
        printf("out of while\n");
        
        char *srcData=ssl_PKCS7_get_Signed_Enveloped_data_from_charArr(recvbuf,pkey,NULL,filesize);
	printf("%ld\n",get_timeStamp(srcData));
	printf("%ld\n",atol(timestamp+1));
        //if(atol(timestamp+1)==) 
        if(get_timeStamp(srcData)==atol(timestamp+1))
        printf("%s \n",remove_timeStamp(srcData));
        else {
        printf("非法访问  。。\n");        
        }

		
	return ret;
}
