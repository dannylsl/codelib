#include <string.h>
#include <openssl/objects.h>
#include <openssl/pkcs7.h>
#include <openssl/pkcs12.h>

#define MAX_LEN 100000
//#define P7FILE "verify.p7"
#define P7FILE "../signedAndEnveloped_cert_ca.p7"

char* ssl_PKCS7_get_Enveloped_data_from_p7file(char* filename,EVP_PKEY *priKey,X509 *x509_Cert){
	FILE *fp;			
	int i,num;	
	unsigned char buf[MAX_LEN],*p;
	PKCS7 *p7 = NULL;

	if(NULL==(fp=fopen(filename,"rb"))){
		perror("failed to open p7 file");
		exit(1);
	}
	
	num = fread(buf,1,MAX_LEN,fp);
	fclose(fp);

	p = buf;
	d2i_PKCS7(&p7,(const unsigned char**)&p,num);
//	p7 = d2i_PKCS7(NULL,(const unsigned char**)&p,num);

    BIO * v_p7bio_tmp = BIO_new(BIO_s_file());
    BIO * p7bio = PKCS7_dataDecode(p7,priKey,NULL,x509_Cert);

    //从BIO中读取原始数据,将得到"How are you!"
    unsigned char src[4096];
    int srcLen = BIO_read(p7bio,src,4096);

	//获得签名者信息STACK
	STACK_OF(PKCS7_SIGNER_INFO)*sk = PKCS7_get_signer_info(p7);
	//获得签名者个数
	int signCount = sk_PKCS7_SIGNER_INFO_num(sk);	
	for(i = 0; i < signCount;i++){
		//获得签名者信息	
		PKCS7_SIGNER_INFO *signInfo = sk_PKCS7_SIGNER_INFO_value(sk,i);
		//获得签名者证书
		X509 *cert = PKCS7_cert_from_signer_info(p7,signInfo);
		//验证签名
		if(PKCS7_signatureVerify(p7bio,p7,signInfo,cert)!=1){
			printf("signatureVerify Failed\n");	
			exit(0);
		}	
	}

    printf("Decrypt from enveloped file src = %s\n",src);

    BIO_free(p7bio);
    PKCS7_free(p7);


}


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
	
	//ssl_PKCS7_get_Enveloped_data_from_p7file("verify.p7",pkey,cert);
	ssl_PKCS7_get_Enveloped_data_from_p7file("../signedAndEnveloped.p7",pkey,cert);
}

