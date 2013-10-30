#include <string.h>
#include <openssl/pkcs12.h>

#define MAX_LEN 100000

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
	X509 *cert = NULL;
	STACK_OF(X509) *ca = NULL;
	EVP_PKEY *pkey = NULL;
	RSA *rsa = NULL;

	fp=fopen("new05092.p12","rb");
	len=fread(buf,1,10000,fp);
	fclose(fp);
	OpenSSL_add_all_algorithms();
	
	bp=BIO_new(BIO_s_file());
	BIO_set_fp(bp,stdout,BIO_NOCLOSE);
	p=buf;
	d2i_PKCS12(&p12,&p,len);
	strcpy(pass,"test");
	PKCS12_parse(p12,pass,&pkey,&cert,&ca);

	//Print the Prikey
	rsa = EVP_PKEY_get1_RSA(pkey);
	RSA_print_fp(stdout,rsa,11);	

	printf("**********************************************\n");
	//Print the x509 certification
	X509_print(bp,cert);	

	if(NULL==(fp=fopen("derData.p7","rb"))){
		perror("fail to open p7 file");		
		return -1;
	};

	memset(buf,0,MAX_LEN);	
	num = fread(buf,1,MAX_LEN,fp);
	fclose(fp);

	p = buf;
/*
	X509 *dertmp,*der = NULL;
	der = X509_new();	
	num = d2i_X509(&der,(const unsigned char**)&p,num);
	dertmp = der;
*/	
	//PKCS7 *v_p7 = PKCS7_new();
	PKCS7 *v_p7 = NULL;
	//v_p7 = PKCS7_new();
	PKCS7 *v_p7_tmp = d2i_PKCS7(&v_p7,(const unsigned char**)&p,num);			
	
	BIO *v_p7bio_tmp = BIO_new(BIO_s_file());
	BIO *v_p7bio = PKCS7_dataDecode(v_p7,pkey,NULL,cert);

	unsigned char src[4096];
	int srcLen = BIO_read(v_p7bio,src,4096);

	printf("%s\n",src);

	BIO_free(v_p7bio);
	PKCS7_free(p7);

	return 0;
}

