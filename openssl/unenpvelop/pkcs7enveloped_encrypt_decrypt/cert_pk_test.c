#include <openssl/pkcs12.h>
#include <openssl/pem.h>
#include "signAndEnvelop.h"

int main(){
		FILE * fp;	
		PKCS12 *p12;
		PKCS7 *p7;
		unsigned char buf[MAX_LEN],*p;
		STACK_OF(PKCS7) *p7s;
		STACK_OF(PKCS12_SAFEBAG) * bags;
		PKCS12_SAFEBAG *bag;
		int len,i,num,j,count,ret;
		PBEPARAM *pbe;
		BIO *bp;
		char pass[100];
		int passlen;
		X509 *RecCert = NULL,*SendCert = NULL;
		STACK_OF(X509) *ca = NULL;
		EVP_PKEY *pkey = NULL;
		RSA *rsa = NULL;

		OpenSSL_add_all_algorithms();
/*
		fp=fopen("new05092.p12","rb");
		len=fread(buf,1,10000,fp);
		fclose(fp);

		bp=BIO_new(BIO_s_file());
		BIO_set_fp(bp,stdout,BIO_NOCLOSE);
		p=buf;
		d2i_PKCS12(&p12,&p,len);
		strcpy(pass,"test");
		PKCS12_parse(p12,pass,&pkey,&SendCert,&ca);

		//打印私钥信息	
		rsa = EVP_PKEY_get1_RSA(pkey);
		//保存密钥
		saveprikey(rsa,"clientPrikey.pem",1024);	
		//保存证书
		write_pem_certification(SendCert,"clientCert.pem");
*/

		//获取客户端密钥,用于签名
		printf("reading client private key\n");
		rsa = read_RSA_Prikey_PEM("clientPrikey.pem");
//		rsa = read_RSA_Prikey_PEM("client/prikey.pem");
		pkey = EVP_PKEY_new();
		EVP_PKEY_assign_RSA(pkey,rsa);
		//获取客户端的证书
		//SendCert = read_der_certification("client/clientCert.der");
		//SendCert = read_pem_certification("client/clientCert.pem");
		SendCert = read_pem_certification("clientCert.pem");

		//发送证书链者
		ssl_PKCS7_signed_and_enveloped_from_file(pkey,NULL,SendCert,"serverCert.pem",PEM,"verify.txt");
//		ssl_PKCS7_signed_and_enveloped_from_file(pkey,NULL,SendCert,"server/serv_cert.der",DER,"verify.txt");
//		ssl_PKCS7_signed_and_enveloped_from_file(pkey,ca,SendCert,"../senderCer.der",DER,"verify.txt");

//接收者
/*	
		printf("\n\t\t\t\t接收者解析部分\n\n");
		memset(buf,0,10000);
		fp = fopen("../server.p12","rb");	
		len=fread(buf,1,10000,fp);
		fclose(fp);
		p=buf;
		d2i_PKCS12(&p12,&p,len);
		strcpy(pass,"1234");
		PKCS12_parse(p12,pass,&pkey,&RecCert,&ca);
		//打印私钥信息	
		rsa = EVP_PKEY_get1_RSA(pkey);
		printf("\t\t\t\t\t接收者私钥 = Parse form p12\n");
		RSA_print_fp(stdout,rsa,1);
		//保存密钥
//		saveprikey(rsa,"serverPrikey.pem",1024);	
		//保存证书
		write_pem_certification(RecCert,"serverCert.pem");
*/

		rsa = read_RSA_Prikey_PEM("serverPrikey.pem");
//		rsa = read_RSA_Prikey_PEM("server/prikey.pem");
		EVP_PKEY_assign_RSA(pkey,rsa);
		printf("\t\t\t\t\t接收者私钥 read from serverPrikey.pem\n");
		RSA_print_fp(stdout,rsa,1);
		RecCert = read_pem_certification("serverCert.pem");

		ssl_PKCS7_get_Signed_Enveloped_data_from_p7file("out.p7",pkey,RecCert);
}
