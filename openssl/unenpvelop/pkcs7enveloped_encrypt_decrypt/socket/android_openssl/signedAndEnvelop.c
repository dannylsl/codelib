#include <stdio.h>
#include "signAndEnvelop.h"

// The filename of the data signed and enveloped is signedAndEnvelop.p7 
/*
#define CLIENTPRIKEY	"/data/local/openssl/clientPrikey.pem"
#define CLIENTCERT		"/data/local/openssl/clientCert.pem"
#define SERVERCERT		"/data/local/openssl/serverCert.pem"
#define DATAFILE		"/data/local/openssl/data"
*/

#define CLIENTPRIKEY	"/data/data/cn.pku.edu.easyhome/openssl/clientPrikey.pem"
#define CLIENTCERT		"/data/data/cn.pku.edu.easyhome/openssl/clientCert.pem"
#define SERVERCERT		"/data/data/cn.pku.edu.easyhome/openssl/serverCert.pem"
#define DATAFILE		"/data/data/cn.pku.edu.easyhome/openssl/data"
#define SE_FILENAME     "/data/data/cn.pku.edu.easyhome/openssl/se_out"

int main(int argc,char ** argv){

	EVP_PKEY *pkey = NULL;	
	RSA *rsa = NULL;
	X509 *x509_cert = NULL;
/*
	if(argc != 2){
		printf("Usage:%s <datafilename>\n",argv[0]);			
		exit(1);
	}
*/	
	OpenSSL_add_all_algorithms();

	//获取客户端密钥
	rsa = read_RSA_Prikey_PEM(CLIENTPRIKEY);						
	pkey = EVP_PKEY_new(); 
	EVP_PKEY_assign_RSA(pkey,rsa);
	x509_cert = read_pem_certification(CLIENTCERT);

	ssl_PKCS7_signed_and_enveloped_from_file(pkey, NULL,x509_cert ,SERVERCERT,PEM, DATAFILE,SE_FILENAME);

} 
