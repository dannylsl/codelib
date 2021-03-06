#include <openssl/pkcs12.h>
#include <openssl/pem.h>
#include "print.h"

#define MAX_LEN 10000
#define DER		1
#define PEM		2

X509* my_PKCS7_cert_from_signer_info(PKCS7 *p7, PKCS7_SIGNER_INFO *si)
{
	if (PKCS7_type_is_signedAndEnveloped(p7))
		return(X509_find_by_issuer_and_serial(p7->d.sign->cert,
					si->issuer_and_serial->issuer,
					si->issuer_and_serial->serial));
	else
		return(NULL);
}


X509 *read_pem_certification(const char*filename){
	BIO *b;	
	X509 *x;

	b = BIO_new_file(filename,"r");
	if(b == NULL){
		printf("Can not open %s\n",filename);	
		return -1;
	}
	x = PEM_read_bio_X509(b,NULL,NULL,NULL);
	BIO_free(b);
	return x;
}

X509 *read_der_certification(const char*filename){
	FILE *fp;
	int size,len;
	unsigned char* buffer,*p;
	X509 *x509_cert = NULL;

	size = get_file_size(filename); 
	buffer = (unsigned char *)malloc(size+1);
	memset(buffer,0,size+1);

	if(NULL == (fp = fopen(filename,"rb"))){
		perror("failed to open file");
		return -1;
	}

	len = fread(buffer,1,size,fp);
	fclose(fp);
	x509_cert = X509_new();
	p = buffer;
	d2i_X509(&x509_cert,(const unsigned char**)&p,len);
	free(buffer);	
	return x509_cert;
}

int get_file_size(const char* filename){
	FILE *fp;	
	int size;
	if(NULL == (fp = fopen(filename,"rb"))){
		perror("failed to open file");
		return -1;
	}
	fseek(fp,0,SEEK_END);
	size = ftell(fp);
	fclose(fp);
	return size;
}

int get_data_from_file(const char* filename,unsigned char *data,int len){
	FILE *fp;	
	int num;

	if(NULL == (fp = fopen(filename,"rb"))){
		perror("failed to open file");		
		return -1;
	}		

	num = fread(data,1,len,fp);
	if(num < 0){
		perror("failed to read data from file");
		return -1;
	}
	fclose(fp);

	return 0;
}

int write_data_to_file(const unsigned char* data,int datalen,const unsigned char* filename){
	FILE *fp;			
	int len;
	if(NULL == (fp = fopen(filename,"wb"))){
		perror("failed to open file");
		return -1;
	}
	len = fwrite(data,1,datalen,fp);
	if(len != datalen){
		perror("something wrong while writting data to file");
		return -1;	
	}
	fclose(fp);
	return 0;

}

/**
 * @Param: filename		接受者证书   PEM 编码
 * @Param: x509_cert	发送者证书
 * @Param: datafilename 加密文本文件名
 */
char *ssl_PKCS7_signed_and_enveloped_from_file(EVP_PKEY *prikey, STACK_OF(X509)*ca, X509* x509_Cert ,const char* filename,const int fileCodeType,const char* datafilename){

	unsigned char *buffer;
	FILE *fp;	
	int size,len;
	int caCnt,i;
	X509* x509_RecCert = NULL;
	RSA *rsa;
	//读取接收者证书,为后面获取公钥，加密对称密钥准备
	switch(fileCodeType){
		case DER:
			x509_RecCert = read_der_certification(filename);
			break;
		case PEM:
			x509_RecCert = read_pem_certification(filename);
			break;
		defualt:	
			break;
	}
	//打印证书信息
	x509_cert_print(x509_RecCert,"接收者证书 x509_RecCert ");	
	x509_cert_print(x509_Cert,"发送者证书 x509_cert");	

	//获取RSA私钥
	rsa = EVP_PKEY_get1_RSA(prikey);
	//打印私钥信息	
	printf("\t\t\t\t\t发送者私钥\n");
	RSA_print_fp(stdout,rsa,1);

	PKCS7 *p7 = PKCS7_new();
	//设置类型为NID_pkcs7_signedAndEnveloped
	PKCS7_set_type(p7, NID_pkcs7_signedAndEnveloped);
	//BELOW ADD REFERS TO   http://ipedo.blog.sohu.com/114822405.html
	PKCS7_content_new(p7,NID_pkcs7_data);
	PKCS7_set_detached(p7,0);

	//DES 算法加密
	EVP_CIPHER *evp_cipher = EVP_des_cbc();
	PKCS7_set_cipher(p7,evp_cipher);
	//设置接受者证书,获取公钥用于加密对称密钥
	PKCS7_RECIP_INFO *p7recipinfo = PKCS7_add_recipient(p7,x509_RecCert);	
	//打印 recipient 信息
	pkcs7_recip_print(p7recipinfo);		

	//添加签名,用发送者证书,发送者私钥,sha1()加密算法
	PKCS7_SIGNER_INFO *info = PKCS7_add_signature(p7, x509_Cert, prikey,EVP_sha1());
	//打印 signature 信息
	signer_info_print(info);

	/*
	*/				
	//添加签名者证书
	PKCS7_add_certificate(p7,x509_Cert);
	//添加签名者证书链
	caCnt = sk_X509_num(ca);
	for(i = 0;i < caCnt; i++){
		PKCS7_add_certificate(p7,sk_X509_value(ca,i));		

		x509_cert_print(sk_X509_value(ca,i),"证书链");
	}
	BIO *p7bio = PKCS7_dataInit(p7,NULL);
	// GET DATA FROM FILE TO ENCRYPT
	size = get_file_size(datafilename);
	buffer = (unsigned char*)malloc(size+1);
	memset(buffer,0,size+1);

	if(NULL == (fp = fopen(datafilename,"rb"))){
		perror("failed to open file");
		return -1;
	}
	len = fread(buffer,1,size,fp);
	fclose(fp);
	printf("DATA FILE :%s\n",datafilename);
	printf("DATA:\n%s\n",buffer);

	BIO_write(p7bio,buffer,len);
	free(buffer);
	BIO_flush(p7bio);
	//完成签名数字信封
	PKCS7_dataFinal(p7,p7bio);

	//打印签名数字信封的信息
	pkcs7_signed_and_envelop_print(p7->d.signed_and_enveloped);

	//PKCS7编码转DER编码
	X509 *derTmp,*der;
	int derLen = i2d_PKCS7(p7,NULL);
	der = (unsigned char*)malloc(derLen+1);
	memset(der,0,derLen+1);
	derTmp = der;
	derLen = i2d_PKCS7(p7,&derTmp);
	//将DER编码后的内容写入文件
	write_data_to_file(der,derLen,"signedAndEnveloped.p7");

	return 0;
}

/**
 * @Param: filename		签名数字信封
 * @Param: prikey		接收者的私钥，用于解密对称密钥
 * @Param:
 */
char* ssl_PKCS7_get_Signed_Enveloped_data_from_p7file(const char * filename,EVP_PKEY *prikey, X509 *x509_cert){
	FILE *fp;
	int i,num,size,srclen;
	unsigned char * buffer;
	unsigned char srcData[4096];
	PKCS7 *p7;

	memset(srcData,0,4097);

	size = get_file_size(filename);
	buffer = (unsigned char*)malloc(size+1);
	memset(buffer,0,size+1);

	get_data_from_file(filename,buffer,size);

	p7 = d2i_PKCS7(NULL,(const unsigned char**)&buffer,size);
	//BIO *v_p7bio = PKCS7_dataDecode(p7,prikey,NULL,x509_cert);
	BIO *v_p7bio = PKCS7_dataDecode(p7,prikey,NULL,NULL);

	srclen = BIO_read(v_p7bio,srcData,4096);
	if(srclen <= 0){
		printf("无法解析出明文\n");
		//return;
	}
	printf("\t\t\t\t　密文解析内容 \n");
	printf("%s\n",srcData);
	//获得签名者信息stack
	STACK_OF(PKCS7_SIGNER_INFO)*sk = PKCS7_get_signer_info(p7);
	//获得签名者个数
	int signCount = sk_PKCS7_SIGNER_INFO_num(sk);
	for(i = 0;i < signCount; i++){
		//获得签名者信息
		PKCS7_SIGNER_INFO *signInfo = sk_PKCS7_SIGNER_INFO_value(sk,i);		
		signer_info_print(signInfo);	
		//获得签名者证书
		//X509*cert = PKCS7_cert_from_signer_info(p7,signInfo);
		X509*cert = my_PKCS7_cert_from_signer_info(p7,signInfo);
		x509_cert_print(cert,"签名者(发送者)证书");
		//验证签名
		if(PKCS7_signatureVerify(v_p7bio,p7,signInfo,cert) != 1){
			//	if(PKCS7_signatureVerify(v_p7bio,p7,signInfo,x509_cert) != 1){ //验证签名的证书是否有问题?
			printf("Signature Verity Error\n");
			return 0;
		}else{
			printf("Signature Verify successfully!\n");	
		}	
		}
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
		X509 *RecCert = NULL,*SendCert = NULL;
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
		PKCS12_parse(p12,pass,&pkey,&SendCert,&ca);

		//发送证书链者
		ssl_PKCS7_signed_and_enveloped_from_file(pkey,ca,SendCert,"../server.der",PEM,"verify.txt");
	//	ssl_PKCS7_signed_and_enveloped_from_file(pkey,ca,SendCert,"../senderCer.der",DER,"verify.txt");

		//接收者
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
		printf("\t\t\t\t\t接收者私钥\n");
		RSA_print_fp(stdout,rsa,1);

		ssl_PKCS7_get_Signed_Enveloped_data_from_p7file("signedAndEnveloped.p7",pkey,SendCert);

	}
