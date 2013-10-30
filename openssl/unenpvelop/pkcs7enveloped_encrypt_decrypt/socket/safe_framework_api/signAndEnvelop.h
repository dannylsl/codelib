/*! \file signAndEnvelop.h
 *  \brief functions inlcudes signed and envelop
 */

#ifndef  __SIGNANDENVELOP_H
#define  __SIGNANDENVELOP_H

#include "print.h"

#define MAX_LEN 10000
#define DER		1
#define PEM		2

/**
 * \fn saveprikey(RSA *rsa,const char *filename,int bits)
 * \param  RSA *rsa				[ the rsa type key ]
 * \param  const char * filename	[ the name of the file save the RSA private key]
 * \param  int bits				[ the bits of the private key, 512 or 1024  ]  
 * \brief  
 *		save private key as file with name of [Param]filename		
 * \return 
 *		return 0 if failed to create file \n
 *		return 1 if the function runs successfully
 */
extern int saveprikey(RSA *rsa,const char *filename,int bits);
/**
 * \fn functionName :  RSA* read_RSA_Prikey(const char*filename, int fileCodeType );
 * \param const char* filename [ the name of the file which store Private keys ]
 * \param int fileCodeType	 [ the codeType of the file, DER or PEM  ]
 * \brief  
 *		read DER or PEM codeType file and return the Private key in RSA type 
 * \return 
 *		return (RSA*) -1 fail to open file \n
 *		return (RSA*) -2 fail to read private key from PEM file descriptor \n
 *		return private key in RSA*
 */
extern RSA* read_RSA_Prikey(const char*filename, int fileCodeType );

/**
 * \fn RSA* read_RSA_Prikey_PEM(const char*filename);
 * \param  const char* filename
 * \brief  
 *		read private key from PEM file 	
 * \return  
 *		return (RSA*) -1 fail to open file \n
 *		return (RSA*) -2 fail to read private key from PEM file descriptor \n
 *		return private key in RSA*
 */
extern RSA* read_RSA_Prikey_PEM(const char*filename);

/**
 * \fn my_PKCS7_cert_from_signer_info(PKCS7 *p7, PKCS7_SIGNER_INFO *si);
 * \param PKCS7 *p7
 * \param PKCS7_SIGNER_INFO *si
 * \brief  
 *		get certification from signer information \n			
 *		This function function is used while unpack signed_and_enveloped data
 * \return 
 *		return X509* type certification \n
 *		return NULL if failed
 */
extern X509* my_PKCS7_cert_from_signer_info(PKCS7 *p7, PKCS7_SIGNER_INFO *si);

/**
 * \fn write_pem_certification(X509 *x509_cert,const char*filename)
 * \param  X509 * x509_cert
 * \param  const char * filename
 * \brief  
 *		write x509_cert to file named [Param]filename	
 * \return 
 *		return -1 if fail to create file \n
 *		return 0
 */
extern int write_pem_certification(X509 *x509_cert,const char*filename);

/**
 * \fn X509 *read_pem_certification(const char*filename)
 * \param const char *filename  
 * \brief  
 *		read certification from PEM codetype filename
 * \return 
 *		return certification in X509* type if run successfully	\n
 *		return -1 if fail to open file
 */
extern X509 *read_pem_certification(const char*filename);

/**
 * \fn read_der_certification(const char*filename)
 * \param const char* filename
 * \brief  
 *		read certification from DER codetype file name [Param]filename	
 * \return 
 *		return certification in X509* type if run successfully \n
 *		return -1 if fail to open file
 */
extern X509 *read_der_certification(const char*filename);

/**
 * \fn  get_file_size(const char* filename)
 * \param const char* filename
 * \brief  
 *		get size of the file named [Param]filename			
 * \return 
 *		return -1 fail to open file \n
 *		return filesize if run successfully
 */
extern int get_file_size(const char* filename);

/**
 * \fn get_data_from_file(const char* filename,unsigned char *data,int len){
 * \param const char* filename
 * \param unsigned char* data
 * \param int len
 * \brief  
 *		get data from file \n
 *		read [Param]len bytes data from file named [Param]filename and store it into [Param]data
 * \return 
 *		return -1 if fail to open and read file \n
 *		return 0 if run successfully
 */
extern int get_data_from_file(const char* filename,unsigned char *data,int len);

/**
 * \fn write_data_to_file(const unsigned char* data,int datalen,const unsigned char* filename)
 * \param const unsigned char* data
 * \param int datalen
 * \param const unsigned char* filename
 * \brief 
 *		write [Param]datalen bytes of [Param]data into file named [Param]filename
 * \return 
 *		return -1 if fail to open and write file \n
 *		return 0  if run successfully
 */
extern int write_data_to_file(const unsigned char* data,int datalen,const unsigned char* filename);

/**
 * \fn ssl_PKCS7_signed_and_enveloped_from_data(EVP_PKEY *prikey,STACK_OF(X509)*ca, X509* x509_Cert,const char* recCertFileName,char *data,char*derOut)
 * \param EVP_PKEY *prikey				[ sender's private key			]
 * \param STACK_OF(X509*) ca			[ sender's certification chain   ] 
 * \param X509 * x509_cert				[ sender's certification			]
 * \param const char* recCertFileName	[ receiver's Certification filename, codeType is PEM only]
 * \param char *data					[ data to signed and enveloped ]
 * \param char *derOut					[ signed and enveloped data in DER codeType]
 * \brief  
 *		Use [Param]prikey [Param]ca [Param]x509_cert and [Param]recCertFileName \n
 *		to sign and envelop [Param]data, and the signed and Envelop data output in DER codeType \n	
 *		and store in [Param]derOut
 * \return 
 *		return the length derOut
 */
extern int ssl_PKCS7_signed_and_enveloped_from_data(EVP_PKEY *prikey,STACK_OF(X509)*ca, X509* x509_Cert,const char* recCertFileName,char *data,char*derOut);

/**
 * \fn ssl_PKCS7_get_data_from_signed_and_enveloped_der(char *der,int len,EVP_PKEY *prikey,unsigned char *dataOut)
 * \param char * der
 * \param int len
 * \param EVP_PKEY *prikey
 * \param unsigned char * dataOut
 * \brief 
 *		This function will get source data from signed and enveloped data \n	
 *		Using [Param]prikey to decrypt the signed and enveloped data [Param]der \n 
 *		whose length is [Param]len, and store the decrypt data in [Param]dataOut
 * \return 
 *		return 0 if the signature verify failed \n
 *		return 1 if the signature verify successfully
 */
extern int ssl_PKCS7_get_data_from_signed_and_enveloped_der(char *der,int len,EVP_PKEY *prikey,unsigned char *dataOut);

/**
 * \fn ssl_PKCS7_signed_and_enveloped_from_file(EVP_PKEY *prikey, STACK_OF(X509)*ca,	X509* x509_Cert , const char* filename, const int fileCodeType, const char* datafilename)
 * \param EVP_PKEY *prikey			[ sender's private key			]
 * \param STACK_OF(X509*) ca		[ sender's certification chain  ] 
 * \param X509 * x509_cert			[ sender's certification		]
 * \param const char* filename      [ receiver's Certification filename]
 * \param const char* fileCodeType	[ the reciver's certification codeType, DER and PEM ]
 * \param char *datafile			[ name fo the file which stores data to signed and enveloped]
 * \brief 
 *		sign and envelop data from [Param]datafile \n
 *		Using the [Param]prikey [Param] ca [Param]x509_Cert and receiver's certification
 * \return 
 *		return -1 if failed to open file \n
 *		return 0 if the function run successfully
 */
extern char *ssl_PKCS7_signed_and_enveloped_from_file(EVP_PKEY *prikey, STACK_OF(X509)*ca,	X509* x509_Cert , const char* filename, const int fileCodeType, const char* datafilename);

/**
 * \fn char* ssl_PKCS7_get_Signed_Enveloped_data_from_p7file(const char * filename,EVP_PKEY *prikey, X509 *x509_cert)
 * \param const char* filename	[ name of the file which stores signed and enveloped data]
 * \param EVP_PKEY *prikey		[ receiver's privatekey ]
 * \param X509 *x509_cert		[ receiver's certification]
 * \brief  
 *		get source data from a file which stores signed and enveloped data \n
 *		Using receiver's private key [Param]prikey and receiver's certification [Param]x509_cert \n
 *		to decrypt the signed and enveloped data
 * \return 
 *		return 0 failed to signed and enveloped data \n
 *		return 1 if the function runs successfully
 */
extern char* ssl_PKCS7_get_Signed_Enveloped_data_from_p7file(const char * filename,EVP_PKEY *prikey, X509 *x509_cert);

/**
 * \fn ssl_PKCS7_get_Signed_Enveloped_data_from_charArr(unsigned char *buffer,EVP_PKEY *prikey, X509 *x509_cert,int sizett)
 * \param const char* filename [ name of the file which stores signed and enveloped data]
 * \param EVP_PKEY *prikey	 [ receiver's privatekey ]
 * \param X509 *x509_cert		 [ receiver's certification]
 * \param int sizett
 * \brief  
 *		get source data from signed and enveloped data \n
 *		Using receiver's private key [Param]prikey and receiver's certification [Param]x509_cert \n
 *		to decrypt the signed and enveloped data
 * \return 
 *		if run successfully return the decrypted source data \n
 *		no error check
 */
char* ssl_PKCS7_get_Signed_Enveloped_data_from_charArr(unsigned char *buffer,EVP_PKEY *prikey, X509 *x509_cert,int sizett);

#endif
