#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/bn.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>


#define MAXLEN 10000

RSA* read_RSA_Prikey(const char*filename){
	FILE*fp;		
	RSA *rsa;
	
	if(NULL==(fp = fopen(filename,"r"))){
		perror("failed to open file");	
		return (RSA*)-1;
	};

	if((rsa = PEM_read_RSAPrivateKey(fp,NULL,NULL,NULL))==NULL){
		perror("Unable to read private key parameters");
		fclose(fp);
		return (RSA*)-2;
	}
	fclose(fp);
	return rsa;	
}


int main(int argc, char* argv[]){
	RSA *rsa;
	FILE *fp;
	char buf[MAXLEN];
	unsigned char * decrypt_string;
	EVP_PKEY *pkey;
	int number_bytes;

	if(argc != 3){
		printf("Usage:%s <prikey_filename> <pkcs7_file2decrypt>\n",argv[0]);	
		return 0;
	}

	rsa = read_RSA_Prikey(argv[1]);
	
	if(NULL == (fp = fopen(argv[2],"rb"))){
		perror("failed to open file");			
		return -1;
	}

	number_bytes=fread(buf,1,MAXLEN,fp);

	pkey = EVP_PKEY_new();
	EVP_PKEY_assign_RSA(pkey,rsa);

	PKCS7* v_p7 = NULL;
	BIO*v_p7bio = PKCS7_dataDecode(v_p7,pkey,NULL,x509_Cert);	

	unsigned char src[4096];	
	int srcLen = BIO_read(v_p7bis,src,4096);

/*	
				
    // alloc decrypt_string
    decrypt_string = (unsigned char*)calloc(RSA_size(rsa),sizeof(unsigned char));
    if (decrypt_string == NULL) {
		perror("Unable to allocate memory for decrypt_string");
        exit(-1);
    }

    // decrypt
    int decrypt_size = RSA_private_decrypt(number_bytes,buf, decrypt_string, rsa, RSA_PKCS1_OAEP_PADDING);

    printf("decrypted string (%d) = %s\n", decrypt_size, decrypt_string);
	return 0;
	*/

}
