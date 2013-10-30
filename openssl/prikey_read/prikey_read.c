#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/bn.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

#define DER 1
#define PEM 2

RSA* read_RSA_Prikey(const char*filename, int fileCodeType ){
	FILE*fp;		
	RSA *rsa;
	unsigned char *p,tmp[5000];	
	int len;
	EVP_PKEY *pkey;

	memset(tmp,0,5000);

	if(NULL==(fp = fopen(filename,"r"))){
		perror("failed to open file");	
		return (RSA*)-1;
	};

	switch(fileCodeType){	
		case PEM:
			if((rsa = PEM_read_RSAPrivateKey(fp,NULL,NULL,NULL))==NULL){
				perror("Unable to read private key parameters");
				return (RSA*)-2;
			}
			break;
		case DER:
			len = fread(tmp,1,5000,fp);
			p = tmp;
			d2i_PrivateKey(EVP_PKEY_RSA,NULL,&p,len);	
			rsa = EVP_PKEY_get1_RSA(pkey);
			break;
	}
	fclose(fp);
	return rsa;	
}

int main(int argc, char* argv[]){
	RSA* rsa;	

	if(argc != 2){
		printf("Usage:%s <prikey_filename>\n",argv[0]);	
		return 0;
	}

	rsa =read_RSA_Prikey(argv[1]);
	RSA_print_fp(stdout,rsa,0);
	printf("\n");
	return 1;
	
}
