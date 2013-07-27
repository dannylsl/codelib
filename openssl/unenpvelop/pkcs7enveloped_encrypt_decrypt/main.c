#include <string.h>
#include <openssl/pkcs12.h>
#include "print.h"

#define MAX_LEN 100000
#define P7FILE "verify.p7"
//#define P7FILE "derData.p7"


char* ssl_PKCS7_signed_and_enveloped(EVP_PKEY*priKey);
char* ssl_PKCS7_get_Enveloped_data (EVP_PKEY *priKey,X509 *x509_Cert);
char* ssl_PKCS7_get_Enveloped_data_from_p7file(char* filename,EVP_PKEY *priKey,X509 *x509_Cert);

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


	printf("signed and enveloped ..\n");
	ssl_PKCS7_signed_and_enveloped(pkey);
	ssl_PKCS7_get_Enveloped_data(pkey,cert);
	printf("read file P7FILE and decrpyt start...\n");
	ssl_PKCS7_get_Enveloped_data_from_p7file(P7FILE,pkey,cert);


}


char* ssl_PKCS7_get_Enveloped_data_from_p7file(char* filename,EVP_PKEY *priKey,X509 *x509_Cert){
	FILE *fp;			
	int num;	
	unsigned char buf[MAX_LEN],*p;
	PKCS7 *p7 = NULL;

	if(NULL==(fp=fopen(filename,"rb"))){
		perror("failed to open p7 file");
		exit(1);
	}
	
	num = fread(buf,1,MAX_LEN,fp);
	fclose(fp);

	p = buf;
/*
//  method 1	
	d2i_PKCS7(&p7,(const unsigned char**)&p,num);
    BIO * v_p7bio_tmp = BIO_new(BIO_s_file());
    BIO * v_p7bio = PKCS7_dataDecode(p7,priKey,NULL,x509_Cert);
*/
/* Method 2 */
	p7 = d2i_PKCS7(NULL,(const unsigned char**)&p,num);	
	BIO * v_p7bio = PKCS7_dataDecode(p7,priKey,NULL,x509_Cert);

    //从BIO中读取原始数据,将得到"How are you!"
    unsigned char src[4096];
    int srcLen = BIO_read(v_p7bio,src,4096);

    printf("Decrypt from enveloped file src = %s\n",src);
    BIO_free(v_p7bio);
    PKCS7_free(p7);
}

char* ssl_PKCS7_signed_and_enveloped(EVP_PKEY*priKey)
{
    //读取公钥证书
    char buf[4096];
    unsigned char *p;
    char *DerPathCharp = "./senderCer.der";
    FILE* fp=fopen(DerPathCharp,"rb");
    if(!fp) return 0;
    int len=fread(buf,1,5000,fp);
    fclose(fp);

    p=buf;
    
    X509 *x509_Cert=X509_new();
    
    d2i_X509(&x509_Cert,(const unsigned char **)&p,len);    

	printf("******************* senderCer.der ***************************\n");
	BIO *bp = BIO_new(BIO_s_file());
	BIO_set_fp(bp,stdout,BIO_NOCLOSE);
	X509_print(bp,x509_Cert);	
	
	//打印私钥
	//Print the Prikey
	printf("========================  PRIVATE KEY ========================\n");
	RSA *rsa = EVP_PKEY_get1_RSA(priKey);
	RSA_print_fp(stdout,rsa,1);	
	
    //调用openssl的代码如下：
    PKCS7* p7 = PKCS7_new();
    //设置类型为NID_pkcs7_enveloped
	//PKCS7_set_type(p7, NID_pkcs7_enveloped);
    //设置类型为NID_pkcs7_signedAndEnveloped
	PKCS7_set_type(p7, NID_pkcs7_signedAndEnveloped);
    
    //DES算法，用于加密内容“How are you!”
    EVP_CIPHER *evp_cipher = EVP_des_cbc();
    PKCS7_set_cipher(p7,evp_cipher);
    
    //设置接收者证书，获取公钥用于加密对称密钥
    PKCS7_RECIP_INFO *p7recipinfo = PKCS7_add_recipient(p7,x509_Cert);
	pkcs7_recip_print(p7recipinfo);
//////////////////////
	//x509:签名证书　pkey:签名者私钥．　EVP_sha1()签名者摘要算法
	PKCS7_SIGNER_INFO *info = PKCS7_add_signature(p7, x509_Cert,priKey, EVP_sha1());
	//打印 signature 信息
	signer_info_print(info);
	//添加签名者证书
	//PKCS7_add_certificate(p7,x509_Cert);	
/*	
	//添加签名者的证书链
	for(int i=0;i < sk_X509_num(ca);i++){
		PKCS7_add_certificate(p7,sk_X509_value(ca,i)):
	}
//////////////////////
*/
    BIO *p7bio = PKCS7_dataInit(p7, NULL);
    //char *instr = "12";
	char instr[MAX_LEN];

	memset(instr,0,MAX_LEN);

	if(NULL==(fp = fopen("verify.txt","rb"))){
		perror("verify open error!");	
		exit(0);
	};

	int num = fread(instr,1,MAX_LEN,fp);
	printf("FREAD: %s\n",instr);
	fclose(fp);

    BIO_write(p7bio,instr,strlen(instr));
    printf("instr = %s\n",instr);

	BIO_flush(p7bio);
    //完成数字信封的运算
    PKCS7_dataFinal(p7, p7bio);

	//打印数字信封的信息
	//pkcs7_envelop_print(p7->d.enveloped);
	//打印签名数字信封的信息
	pkcs7_signed_and_envelop_print(p7->d.signed_and_enveloped);
		

    //转换PKCS7结构体为DER编码
    X509* derTmp,*der;
    
    int derLen = i2d_PKCS7(p7,NULL);
    der  = (unsigned char*)malloc(derLen);
    derTmp = der;
    //转换为der编码输出
    derLen = i2d_PKCS7(p7,&derTmp);
	//将DER编码后的内容写入文件
	fp = fopen("signedEnveloped.p7","wb");
	fwrite(der,1,derLen,fp);
	fclose(fp);

	//以PEM格式存储
	BIO *b = BIO_new_file("derData.pem","wb");		
	PEM_write_bio_PKCS7(b,p7);
	BIO_free(b);

    BIO_free(p7bio);
    PKCS7_free(p7);     
}


char* ssl_PKCS7_get_Enveloped_data (EVP_PKEY *priKey,X509 *x509_Cert)
{
    //读取公钥证书
/*
    char buf[4096];
    unsigned char *p;
    char *DerPathCharp = "/Users/ipc/Desktop/openssl/rsa_encode_decode/CryptoDemo/yaclifecert.der";
    FILE* fp=fopen(DerPathCharp,"rb");
    if(!fp) return NO;
    int len=fread(buf,1,5000,fp);
    fclose(fp);

    p=buf;
    
    X509 *x509_Cert=X509_new();
    
    d2i_X509(&x509_Cert,(const unsigned char **)&p,len);    
*/
    //调用openssl的代码如下：
    PKCS7* p7 = PKCS7_new();
    //设置类型为NID_pkcs7_enveloped
    PKCS7_set_type(p7, NID_pkcs7_enveloped);
    //设置类型为NID_pkcs7_signedAndEnveloped
	//PKCS7_set_type(p7, NID_pkcs7_signedAndEnveloped);
    
    //DES算法，用于加密内容“How are you!”
    EVP_CIPHER *evp_cipher = EVP_des_cbc();
    PKCS7_set_cipher(p7,evp_cipher);
    
    //设置接收者证书，获取公钥用于加密对称密钥
    PKCS7_RECIP_INFO *p7recipinfo = PKCS7_add_recipient(p7,x509_Cert);
/**/
//////////////////////
	//x509:签名证书　pkey:签名者私钥．　EVP_sha1()签名者摘要算法
	//PKCS7_SIGNER_INFO *info = PKCS7_add_signature(p7, x509_Cert,priKey, EVP_sha1());
	//添加签名者证书
//	PKCS7_add_certificate(p7,x509_Cert);	
/*	
	//添加签名者的证书链
	for(int i=0;i < sk_X509_num(ca);i++){
		PKCS7_add_certificate(p7,sk_X509_value(ca,i)):
	}
    
//////////////////////
*/
    BIO *p7bio = PKCS7_dataInit(p7, NULL);
    char *instr = "12";
    BIO_write(p7bio,instr,strlen(instr));
    printf("instr = %s\n",instr);

	BIO_flush(p7bio);
    //完成数字信封的运算
    PKCS7_dataFinal(p7, p7bio);
	//打印数字信封信息
	printf("&&&&&&&&&&&&&&&&&&&&&&&&& ENVELOP INFO  &&&&&&&&&&&&&&&&&&&&&&&&&&\n");
	pkcs7_envelop_print(p7->d.enveloped);
	printf("&&&&&&&&&&&&&&&&&&&&&&&  ENVELOP INFO END  &&&&&&&&&&&&&&&&&&&&&&&\n");
	

    //转换PKCS7结构体为DER编码
    X509* derTmp,*der;
    
    int derLen = i2d_PKCS7(p7,NULL);
    der  = (unsigned char*)malloc(derLen);
    derTmp = der;
    //转换为der编码输出
    derLen = i2d_PKCS7(p7,&derTmp);
	//将DER编码后的内容写入文件
	FILE *fp;
	fp = fopen("derData.p7","wb");
	fwrite(der,1,derLen,fp);
	fclose(fp);

	//以PEM格式存储
	BIO *b = BIO_new_file("derData.pem","wb");		
	PEM_write_bio_PKCS7(b,p7);
	BIO_free(b);

    BIO_free(p7bio);
    PKCS7_free(p7);     
    
    //解P7数字信封的代码：
    //der编码转换为PKCS7结构体
    int derP7EnvelopedDataLen = derLen;
    PKCS7* v_p7 = NULL;
    PKCS7* v_p7_tmp = d2i_PKCS7(&v_p7,&der,derP7EnvelopedDataLen);
   
    //解析出原始数据, evp_key:接收者私钥，x509_Cert:接收者证书
    BIO * v_p7bio_tmp = BIO_new(BIO_s_file());
    BIO * v_p7bio = PKCS7_dataDecode(v_p7,priKey,NULL,x509_Cert);
    
    //从BIO中读取原始数据,将得到"How are you!"
    unsigned char src[4096];
    int srcLen = BIO_read(v_p7bio,src,4096);
    
    printf("\nsrc = %s",src);
    if (!strcmp(instr,src))
    {
        printf(" \n ssl_PKCS7_get_Enveloped_data ok !!\n");
    }
    
    BIO_free(v_p7bio);
    PKCS7_free(v_p7);
}


