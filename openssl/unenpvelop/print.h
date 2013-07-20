#include <openssl/x509.h>
#include <openssl/bio.h>

int X509_ALGOR_print(BIO *bp,X509_ALGOR *signature)
{
	int	nid;
	unsigned char *p;
	PBEPARAM *pbe=NULL;
	nid=OBJ_obj2nid(signature->algorithm);
	switch(nid)
	{
		case NID_md5WithRSAEncryption:
			printf("md5WithRSAEncryption");
			break;
		case NID_sha1WithRSAEncryption:
			printf("sha1WithRSAEncryption");
			break;
		case NID_rsaEncryption:
			printf("rsaEncryption");
			break;
		case NID_sha1:
			printf("sha1");
			break;
		case NID_pbe_WithSHA1And3_Key_TripleDES_CBC:
			printf("NID_pbe_WithSHA1And3_Key_TripleDES_CBC");
			break;
		case NID_des_cbc:
			printf("NID_des_cbc");
			break;
		default:
			printf("unknown signature.");
			break;
	}
	if(signature->parameter!=NULL)
	{
		if(nid==NID_pbe_WithSHA1And3_Key_TripleDES_CBC)
		{
			printf("算法参数:\n");
			p=signature->parameter->value.sequence->data;
			d2i_PBEPARAM(&pbe,&p,signature->parameter->value.sequence->length);
			printf("salt : \n");
			i2a_ASN1_INTEGER(bp,pbe->salt);
			printf("\n");
			printf("iter : %d\n",ASN1_INTEGER_get(pbe->iter));
		} }
	printf("\n");
	return 0;
}

void asn1_integer_print(ASN1_INTEGER*asn1value,const char *title){
	long value;
	value = ASN1_INTEGER_get(asn1value);
	printf("%s:\t%ld\n",title,value);
}

void signer_info_print(PKCS7_SIGNER_INFO*info){
	long version,serail;

	printf("****************************************************************\n");
	printf("signer_info_print...\n");
	version =  ASN1_INTEGER_get(info->version);			
	printf("version:%d\n",version);

//	printf("ISSUER AND SERIAL\n");
	serail = ASN1_INTEGER_get(info->issuer_and_serial->serial); 
	printf("serial:%ld\n",serail);
	printf("ISSUER INFO:");
	BIO *out = BIO_new(BIO_s_file());
	BIO_set_fp(out,stdout,BIO_NOCLOSE);
	X509_NAME_print(out,info->issuer_and_serial->issuer,0);
	BIO_free(out);
	printf("\n");

	printf("DIGEST_ALGORITHM:");
	BIO *b_alg = BIO_new(BIO_s_file());
	X509_ALGOR_print(b_alg,info->digest_alg);
	BIO_free(b_alg);

	printf("DIGEST_ENCRYPT_ALGORITHM:");
	BIO *b_enc_alg = BIO_new(BIO_s_file());
	X509_ALGOR_print(b_enc_alg,info->digest_enc_alg);
	BIO_free(b_enc_alg);

	printf("ENCRYPT DIGEST:");
	BIO *b_enc_dig = BIO_new(BIO_s_file());
	BIO_set_fp(b_enc_dig,stdout,BIO_NOCLOSE);	
	i2a_ASN1_STRING(b_enc_dig,info->enc_digest,1);
	BIO_free(b_enc_dig);
	printf("\n");

	printf("signer_info_print... END\n");	
	printf("****************************************************************\n");
}


void asn1_octet_string_print(ASN1_OCTET_STRING *octet){
	BIO *out = BIO_new(BIO_s_file());
	BIO_set_fp(out,stdout,BIO_NOCLOSE);	
	i2a_ASN1_STRING(out,octet,1);
	BIO_free(out);
	printf("\n");
}

void pkcs7_recip_print(PKCS7_RECIP_INFO *recip){
	long version,serail;

	printf("****************************************************************\n");
	printf("recipient info print...\n");
	version = ASN1_INTEGER_get(recip->version);
	printf("version:\t%d\n",version);
	
//	printf("ISSUER AND SERIAL\n");
	serail = ASN1_INTEGER_get(recip->issuer_and_serial->serial); 
	printf("serial:\t%ld\n",serail);
	printf("ISSUER INFO:\t");
	BIO *out = BIO_new(BIO_s_file());
	BIO_set_fp(out,stdout,BIO_NOCLOSE);
	X509_NAME_print(out,recip->issuer_and_serial->issuer,0);
	BIO_free(out);
	printf("\n");

	printf("KEY ENCRYPT ALGORITHM:\t");
	out = BIO_new(BIO_s_file());
	X509_ALGOR_print(out,recip->key_enc_algor);
	BIO_free(out);

	printf("ENCRYPT KEY:");
	asn1_octet_string_print(recip->enc_key);

	printf("recipient info print end ...\n");
	printf("****************************************************************\n");
				
}

void asn1_object_print(ASN1_OBJECT *a, const char* title){
	char buf[1024];	
	OBJ_obj2txt(buf,1024,a,0);
	printf("%s:%s\n",title,buf);
	OBJ_obj2txt(buf,1024,a,1);
	printf("%s:%s\n",title,buf);
}


void pkcs7_envelop_print(PKCS7_ENVELOPE* envelop){

	BIO *out ;
	printf("========================= PKCS7 ENVELOP ===========================\n");
	asn1_integer_print(envelop->version,"Envelop version");	
	asn1_object_print(envelop->enc_data->content_type,"ENCRYPT_DATA_TYPE");
	printf("ENCRYPT_DATA_ALGORITHM:\t");
	out = BIO_new(BIO_s_file());
	X509_ALGOR_print(out,envelop->enc_data->algorithm);
	BIO_free(out);

	printf("ENCRYPT_DATA_ENC Data:\t");
	asn1_octet_string_print(envelop->enc_data->enc_data);
		
	printf("[STACK] RECIPIENT INFO PRINT\n");
	int num,i,recip_ver;	
	PKCS7_RECIP_INFO *recip;
	num = sk_PKCS7_RECIP_INFO_num(envelop->recipientinfo);
	for(i = 0; i < num; i++){
		//print recipient version
		printf("RECIPIENT-%d:\n",i);
		recip = sk_PKCS7_RECIP_INFO_value(envelop->recipientinfo,i);
		pkcs7_recip_print(recip);
		asn1_integer_print(recip->version,"Envelop stack recipientinfo version");	
	}
	printf("[STACK] RECIPIENT INFO PRINT PRIN  END\n");

	printf("========================= PKCS7 ENVELOP ===========================\n");
}

void pkcs7_signed_and_envelop_print(PKCS7_SIGN_ENVELOPE* envelop){

	BIO *out ;
	printf("========================= PKCS7 SIGNED AND ENVELOP ===========================\n");
	asn1_integer_print(envelop->version,"Envelop version");	
	asn1_object_print(envelop->enc_data->content_type,"ENCRYPT_DATA_TYPE");
	printf("ENCRYPT_DATA_ALGORITHM:\t");
	out = BIO_new(BIO_s_file());
	X509_ALGOR_print(out,envelop->enc_data->algorithm);
	BIO_free(out);

	printf("ENCRYPT_DATA_ENC Data:\t");
	asn1_octet_string_print(envelop->enc_data->enc_data);
		
	printf("[STACK] RECIPIENT INFO PRINT\n");
	int num,i,recip_ver;	
	PKCS7_RECIP_INFO *recip;
	num = sk_PKCS7_RECIP_INFO_num(envelop->recipientinfo);
	for(i = 0; i < num; i++){
		//print recipient version
		printf("RECIPIENT-%d:\n",i);
		recip = sk_PKCS7_RECIP_INFO_value(envelop->recipientinfo,i);
		pkcs7_recip_print(recip);
		asn1_integer_print(recip->version,"Envelop stack recipientinfo version");	
	}
	printf("[STACK] RECIPIENT INFO PRINT PRIN  END\n");
	
		
	printf("========================= PKCS7 SIGNED AND ENVELOP ===========================\n");
}
