#include <stdio.h>
#include "signAndEnvelop.h"

/*
#define CLIENTPRIKEY	"/data/local/openssl/clientPrikey.pem"
#define CLIENTCERT		"/data/local/openssl/clientCert.pem"
#define SERVERCERT		"/data/local/openssl/serverCert.pem"
*/

#define SERVERPRIK		"serverPrikey.pem"
#define SERVERCERT		"serverCert.pem"

int main(int argc, char**argv){

	EVP_PKEY *pkey = NULL;	
	RSA *rsa = NULL;
	X509 *x509_cert = NULL;

	if(argc != 2){
		printf("Usage:%s <se_filename>\n",argv[0]);			
		exit(1);
	}
	
	OpenSSL_add_all_algorithms();

	rsa = read_RSA_Prikey_PEM(SERVERPRIK);						
	pkey = EVP_PKEY_new(); 
	EVP_PKEY_assign_RSA(pkey,rsa);
	x509_cert = read_pem_certification(SERVERCERT);

	
	ssl_PKCS7_get_Signed_Enveloped_data_from_p7file(argv[1],pkey,x509_cert);
			
}
