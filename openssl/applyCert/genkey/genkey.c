#include <openssl/rsa.h>


int saveprikey(RSA *rsa,const char *filename){
	FILE *file;
	if(NULL == rsa){
		printf("RSA not initial.\n");	
	}
	file = fopen(filename,"wb");

	if(NULL == file){
		printf("create file %s failed!\n",filename);	
		return 0;
	}

	PEM_write_RSAPrivateKey(file, rsa, NULL,NULL,512,NULL,NULL);
	fclose(file);
	return 1;
}


int main(){
	RSA		*r;
	int		bits = 512,ret;
	unsigned long e = RSA_3;
	BIGNUM	*bne;

	r=RSA_generate_key(bits,e,NULL,NULL);
	RSA_print_fp(stdout,r,11);
	saveprikey(r,"prikey.pem");

	RSA_free(r);
	bne=BN_new();
	ret=BN_set_word(bne,e);
	r=RSA_new();
	ret=RSA_generate_key_ex(r,bits,bne,NULL);
	if(ret!=1)
	{
		printf("RSA_generate_key_ex err!\n");
		return -1;
	}
	RSA_free(r);
	return 0;
}
