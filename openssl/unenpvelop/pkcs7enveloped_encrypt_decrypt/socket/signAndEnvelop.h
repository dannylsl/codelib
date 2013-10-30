#ifndef  __SIGNANDENVELOP_H
#define  __SIGNANDENVELOP_H

#include "print.h"

#define MAX_LEN 10000
#define DER		1
#define PEM		2

/**
 * \fn functionName : saveprikey   
 * \param @Param : RSA *rsa				[ the rsa type key ]
 * \param @Param : const char * filename	[ the name of the file save the RSA private key]
 * \param @Param : int bits				[ the bits of the private key, 512 or 1024  ]  
 * \brief Brief  : 
 *		save private key as file with name of @Param:filename		
 * return : 
 *		return 0 if failed to create file
 *		return 1 if the function runs successfully
 */
int saveprikey(RSA *rsa,const char *filename,int bits){
	FILE *file;
	if(NULL == rsa){
		printf("RSA not initial.\n");	
	}
	file = fopen(filename,"wb");

	if(NULL == file){
		printf("create file %s failed!\n",filename);	
		return 0;
	}

	PEM_write_RSAPrivateKey(file, rsa, NULL,NULL,bits,NULL,NULL);
	fclose(file);
	return 1;
}


/**
 * \fn functionName :  read_RSA_Prikey 
 * \param @Param : const char* filename [ the name of the file which store Private keys ]
 * \param @Param : int fileCodeType	 [ the codeType of the file, DER or PEM  ]
 * \brief Brief  : 
 *		read DER or PEM codeType file and return the Private key in RSA type 
 * return : 
 *		return (RSA*) -1 fail to open file
 *		return (RSA*) -2 fail to read private key from PEM file descriptor
 *		return private key in RSA*
 */
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
			pkey = d2i_PrivateKey(EVP_PKEY_RSA,NULL,&p,len);	
			rsa = EVP_PKEY_get1_RSA(pkey);
			break;
	}
	fclose(fp);
	return rsa;	
}


/**
 * \fn functionName :  read_RSA_Prikey_PEM 
 * \param @Param : const char* filename
 * \brief Brief  : 
 *		read private key from PEM file 	
 * return :  
 *		return (RSA*) -1 fail to open file
 *		return (RSA*) -2 fail to read private key from PEM file descriptor
 *		return private key in RSA*
 */
RSA* read_RSA_Prikey_PEM(const char*filename){
	FILE*fp;
	RSA *rsa;

	printf("READING RSA PRIVATE KEY FORM %s\n",filename);
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

/**
 * \fn functionName : my_PKCS7_cert_from_signer_info   
 * \param @Param : PKCS7 *p7
 * \param @Param : PKCS7_SIGNER_INFO *si
 * \brief Brief  : 
 *		get certification from signer information			
 * return : 
 *		return X509* type certification
 *		return NULL if failed
 */
X509* my_PKCS7_cert_from_signer_info(PKCS7 *p7, PKCS7_SIGNER_INFO *si)
{
	if (PKCS7_type_is_signedAndEnveloped(p7))
		return(X509_find_by_issuer_and_serial(p7->d.sign->cert,
					si->issuer_and_serial->issuer,
					si->issuer_and_serial->serial));
	else
		return(NULL);
}

/**
 * \fn functionName :  write_pem_certification 
 * \param @Param : X509 * x509_cert
 * \param @Param : const char * filename
 * \brief Brief  : 
 *		write x509_cert to file named @Param:filename	
 * return : 
 *		return -1 if fail to create file
 *		return 0
 */
int write_pem_certification(X509 *x509_cert,const char*filename){
	BIO *b;
	printf("write %s PEM file\n",filename);
	b = BIO_new_file(filename,"w");
	if(b == NULL){
		printf("Can not open %s\n",filename);	
		return -1;
	}
	PEM_write_bio_X509(b,x509_cert);
	BIO_free(b);
	return 0;

}

/**
 * \fn functionName : read_pem_certification   
 * \param @Param : const char *filename  
 * \brief Brief  : 
 *		read certification from PEM codetype filename
 * return : 
 *		return certification in X509* type if run successfully	
 *		return -1 if fail to open file
 */
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

/**
 * \fn functionName : read_der_certification
 * \param @Param : const char* filename
 * \brief Brief  : 
 *		read certification from DER codetype file name @Param:filename	
 * return : 
 *		return certification in X509* type if run successfully
 *		return -1 if fail to open file
 */
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

/**
 * \fn functionName :  get_file_size 
 * \param @Param : const char* filename
 * \param Brief  : 
 *		get size of the file named @Param:filename			
 * return : 
 *		return -1 fail to open file
 *		return filesize if run successfully
 */
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

/**
 * \fn functionName :  get_data_from_file 
 * \param @Param : const char* filename
 * \param @Param : unsigned char* data
 * \param @Param : int len
 * \brief Brief  : 
 *		get data from file
 *		read @Param:len bytes data from file named @Param:filename and store it into @Param:data
 * return : 
 *		return -1 if fail to open and read file
 *		return 0 if run successfully
 */
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

/**
 * \fn functionName : write_data_to_file   
 * \param @Param : const unsigned char* data
 * \param @Param : int datalen
 * \param @Param : const unsigned char* filename
 * \brief Brief  : 
 *		write @Param:datalen bytes of @Param:data into file named @Param:filename
 * return : 
 *		return -1 if fail to open and write file
 *		return 0  if run successfully
 */
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
 * \fn functionName : ssl_PKCS7_signed_and_enveloped_from_data
 * \param @Param :	EVP_PKEY *prikey			[ private key			]
 * \param @Param : STACK_OF(X509*) ca			[ certification chain   ] 
 * \param @Param : X509 * x509_cert			[ certification			]
 * \param @Param : const char* recCertFileName [ receiver's Certification filename, codeType is PEM only]
 * \param @Param : char *data					[ data to signed and enveloped ]
 * \param @Param : char *derOut				[ signed and enveloped data in DER codeType]
 * \brief Brief  : 
 *		Use @Param:prikey @Param:ca @Param:x509_cert and @Param:recCertFileName 
 *		to sign and envelop @Param:data, and the signed and Envelop data output in DER codeType 	
 *		and store in @Param:derOut
 * return : 
 *		return the length derOut
 */
int ssl_PKCS7_signed_and_enveloped_from_data(EVP_PKEY *prikey,STACK_OF(X509)*ca, X509* x509_Cert,const char* recCertFileName,char *data,char*derOut){

	int size,len;
	int caCnt,i;	
	X509 *x509_RecCert = NULL;
	RSA *rsa = NULL;

	x509_RecCert = read_pem_certification(recCertFileName);

	//打印证书信息
	//x509_cert_print(x509_RecCert,"接收者证书 x509_RecCert ");	
	//x509_cert_print(x509_Cert,"发送者证书 x509_cert");	

	//获取RSA私钥
	rsa = EVP_PKEY_get1_RSA(prikey);
	//打印私钥信息	
	//printf("\t\t\t\t\t发送者私钥\n");
	//RSA_print_fp(stdout,rsa,1);

	PKCS7 *p7 = PKCS7_new();
	//设置类型为NID_pkcs7_signedAndEnveloped
	PKCS7_set_type(p7, NID_pkcs7_signedAndEnveloped);

	//DES 算法加密
	EVP_CIPHER *evp_cipher = EVP_des_cbc();
	PKCS7_set_cipher(p7,evp_cipher);
	//设置接受者证书,获取公钥用于加密对称密钥
	PKCS7_RECIP_INFO *p7recipinfo = PKCS7_add_recipient(p7,x509_RecCert);	
	//打印 recipient 信息
	//pkcs7_recip_print(p7recipinfo);		

	//添加签名,用发送者证书,发送者私钥,sha1()加密算法
	PKCS7_SIGNER_INFO *info = PKCS7_add_signature(p7, x509_Cert, prikey,EVP_sha1());
	//打印 signature 信息
	signer_info_print(info);

	//添加签名者证书
	PKCS7_add_certificate(p7,x509_Cert);
	//添加签名者证书链
	caCnt = sk_X509_num(ca);
	for(i = 0;i < caCnt; i++){
		PKCS7_add_certificate(p7,sk_X509_value(ca,i));		
		//打印证书链
		//x509_cert_print(sk_X509_value(ca,i),"证书链");
	}
	BIO *p7bio = PKCS7_dataInit(p7,NULL);

	//获取明文信息
	size = strlen(data);		
	printf("Data:%s\n",data);

	BIO_write(p7bio,data,size);
	BIO_flush(p7bio);
	//完成签名数字信封
	PKCS7_dataFinal(p7,p7bio);

	//PKCS7编码转DER编码
	X509 *derTmp,*der;
	int derLen = i2d_PKCS7(p7,NULL);
	der = (unsigned char*)malloc(derLen+1);
	memset(der,0,derLen+1);
	derTmp = der;
	derLen = i2d_PKCS7(p7,&derOut);

	strcpy(derOut,(char*)der);

	return derLen;
}

/**
 * \fn functionName : ssl_PKCS7_get_data_from_signed_and_enveloped_der    
 * \fn @Param : char * der
 * \fn @Param : int len
 * \fn @Param : EVP_PKEY *prikey
 * \fn @Param : unsigned char * dataOut
 * \brief Brief  : 
 *		This function will get source data from signed and enveloped data	
 *		Using @Param:prikey to decrypt the signed and enveloped data @Param:der 
 *		whose length is @Param:len, and store the decrypt data in @Parm:dataOut
 * return : 
 *		return 0 if the signature verify failed
 *		return 1 if the signature verify successfully
 */
int ssl_PKCS7_get_data_from_signed_and_enveloped_der(char *der,int len,EVP_PKEY *prikey,unsigned char *dataOut){

	int i,num,size,srclen;
	unsigned char srcData[4096];
	unsigned char *tmp,*p;
	PKCS7 *p7;

	size = len;
	memset(srcData,0,4097);
	//	tmp = (char*)malloc(size);
	//	tmp = OPENSSL_malloc(len);	
	//	strncpy(tmp,der,size);
	//	p = tmp;

	//printf("tmp = %s\n",tmp);
	//检查数据转换是否有问题
	//p7 = PKCS7_new();
	//p7 = d2i_PKCS7(NULL,(const unsigned char**)&tmp,size);
	p7 = d2i_PKCS7(NULL,(const unsigned char**)&der,size);
	BIO *out = BIO_new(BIO_s_file());
	BIO_set_fp(out,stdout,BIO_NOCLOSE);
	ERR_print_errors(out);
	BIO_free(out);
	//BIO *v_p7bio = PKCS7_dataDecode(p7,prikey,NULL,x509_cert);
	BIO *v_p7bio = PKCS7_dataDecode(p7,prikey,NULL,NULL);

	srclen = BIO_read(v_p7bio,srcData,4096);
	if(srclen <= 0){
		printf("无法解析出明文\n");
		return -1;
	}

	printf("\t\t\t\t　密文解析内容 \n");
	printf("%s\n",srcData);
	//获得签名者信息stack
	STACK_OF(PKCS7_SIGNER_INFO)*sk = PKCS7_get_signer_info(p7);
	//获得签名者个数
	int signCount = sk_PKCS7_SIGNER_INFO_num(sk);
	for(i = 0;i < signCount; i++)
	{
		//获得签名者信息
		PKCS7_SIGNER_INFO *signInfo = sk_PKCS7_SIGNER_INFO_value(sk,i);		
		signer_info_print(signInfo);	
		//获得签名者证书
		//X509*cert = PKCS7_cert_from_signer_info(p7,signInfo);
		X509*cert = my_PKCS7_cert_from_signer_info(p7,signInfo);
		x509_cert_print(cert,"签名者(发送者)证书");
		//验证签名
		if(PKCS7_signatureVerify(v_p7bio,p7,signInfo,cert) != 1){
			//	if(PKCS7_signatureVerify(v_p7bio,p7,signInfo,x509_cert) != 1) //验证签名的证书是否有问题?
			printf("Signature Verity Error\n");
			return 0;
		}else{
			printf("Signature Verify successfully!\n");	
			//由dataOut返回数据
			strcpy(dataOut,srcData);  
			//DataOut输出
			printf("Data Out:%s\n",dataOut);
			return 1;
		}	
	}
}


/**
 * \fn functionName :   ssl_PKCS7_signed_and_enveloped_from_file
 * \param @Param :	EVP_PKEY *prikey			[ sender's private key			]
 * \param @Param : STACK_OF(X509*) ca			[ sender's certification chain  ] 
 * \param @Param : X509 * x509_cert			[ sender's certification		]
 * \param @Param : const char* filename        [ receiver's Certification filename]
 * \param @Param : const char* fileCodeType	[ the reciver's certification codeType, DER and PEM ]
 * \param @Param : char *datafile				[ name fo the file which stores data to signed and enveloped]
 * \brief Brief  : 
 *		sign and envelop data from @Param:datafile
 *		Using the @Param:prikey @Param: ca @Param:x509_Cert and receiver's certification
 * return : 
 *		return -1 if failed to open file
 *		return 0 if the function run successfully
 */
char *ssl_PKCS7_signed_and_enveloped_from_file(EVP_PKEY *prikey, STACK_OF(X509)*ca,	X509* x509_Cert , const char* filename, const int fileCodeType, const char* datafilename)
{
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
	//	PKCS7_content_new(p7,NID_pkcs7_data);
	//	PKCS7_set_detached(p7,0);

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
 * \fn functionName : ssl_PKCS7_get_Signed_Enveloped_data_from_p7file    
 * \param @Param : const char* filename [ name of the file which stores signed and enveloped data]
 * \param @Param : EVP_PKEY *prikey	 [ receiver's privatekey ]
 * \param @Param : X509 *x509_cert		 [ receiver's certification]
 * \brief Brief  : 
 *		get source data from a file which stores signed and enveloped data
 *		Using receiver's private key @Param:prikey and receiver's certification @Param:x509_cert 
 *		to decrypt the signed and enveloped data
 * return : 
 *		return 0 failed to signed and enveloped data
 *		return 1 if the function runs successfully
 */
char* ssl_PKCS7_get_Signed_Enveloped_data_from_p7file(const char * filename,EVP_PKEY *prikey, X509 *x509_cert){
	FILE *fp;
	int i,num,size,srclen;
	unsigned char * buffer;
	unsigned char srcData[4097];
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
			//	if(PKCS7_signatureVerify(v_p7bio,p7,signInfo,x509_cert) != 1) //验证签名的证书是否有问题?
			printf("Signature Verity Error\n");
			return 0;
		}else{
			printf("Signature Verify successfully!\n");	
			return 1;
		}	
	}
	return 1;
}

/**
 * \fn functionName : ssl_PKCS7_get_Signed_Enveloped_data_from_charArr    
 * \param @Param : const char* filename [ name of the file which stores signed and enveloped data]
 * \param @Param : EVP_PKEY *prikey	 [ receiver's privatekey ]
 * \param @Param : X509 *x509_cert		 [ receiver's certification]
 * \param @Param : int sizett
 * \brief Brief  : 
 *		get source data from signed and enveloped data
 *		Using receiver's private key @Param:prikey and receiver's certification @Param:x509_cert 
 *		to decrypt the signed and enveloped data
 * return : 
 *		if run successfully return the decrypted source data 
 *		no error check
 */

char* ssl_PKCS7_get_Signed_Enveloped_data_from_charArr(unsigned char *buffer,EVP_PKEY *prikey, X509 *x509_cert,int sizett){
	FILE *fp;
	int i,num,size,srclen;
	//unsigned char * buffer;
	unsigned char srcData[4096];
	char *retData=(char *)malloc(4096);
	memset(retData,'\0',4096);
	PKCS7 *p7;
	printf("------------------\n");
	printf("buffer in ssl_PKCS7_get_Signed_Enveloped_data_from_charArr.....%s\n",buffer);
	memset(srcData,0,4097);
	size=sizett;
	//size = get_file_size(filename);
	//buffer = (unsigned char*)malloc(size+1);
	//memset(buffer,0,size+1);

	//get_data_from_file(filename,buffer,size);

	p7 = d2i_PKCS7(NULL,(const unsigned char**)&buffer,size);

	//BIO *v_p7bio = PKCS7_dataDecode(p7,prikey,NULL,x509_cert);

	BIO *v_p7bio = PKCS7_dataDecode(p7,prikey,NULL,NULL);

	srclen = BIO_read(v_p7bio,srcData,4096);
	if(srclen <= 0){
		printf("无法解析出明文\n");
		//return;
	}
	printf("\t\t\t\t　密文解析内容 \n");
	printf("%s \n",srcData);
	strcpy(retData,srcData);
	return  retData;

}
#endif
