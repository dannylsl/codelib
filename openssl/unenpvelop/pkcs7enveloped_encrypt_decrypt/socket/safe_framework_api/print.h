/**
 * \file print.h
 * \brief  self-defined openssl data structure print out
 */
#ifndef __PRINT_H
#define __PRINT_H

#include <openssl/x509.h>
#include <openssl/bio.h>

/**
 * \fn x509_cert_print(X509* x509_cert,const char* title)
 * \param X509 *x509_cert  [ X509 format certification									]
 * \param const char* tile [ description of the certification, will be printed at the head]
 * \brief 
 *		print the x509 format certification	
 * \return 
 *		return 0 without error check
 */
extern int x509_cert_print(X509* x509_cert,const char* title);
/**
 * \fn int X509_ALGOR_print(BIO *bp,X509_ALGOR *signature)
 * \param BIO *bp		[ abstract IO ]
 * \param X509_ALGOR	[ X509 ALGORITHM]
 * \brief 
 *		print X509_ALGOR data
 * \return 
 *		return 0 without error check
 */
extern int X509_ALGOR_print(BIO *bp,X509_ALGOR *signature);

/**
 * \fn asn1_integer_print(ASN1_INTEGER*asn1value,const char *title)
 * \param ASN1_INTEGER * asn1value[ ASN1_INTERGER pointer type value]
 * \param const char * title		[ description of the ASN1_INTERGER, will be printed at the head]
 * \brief 
 *		print the ASN1_INTERGER  	
 * \return null
 */
extern void asn1_integer_print(ASN1_INTEGER*asn1value,const char *title);
/**
 * \fn signer_info_print(PKCS7_SIGNER_INFO*info)
 * \param PKCS7_SIGNER_INFO *info [ signer information ]
 * \brief 
 *		print signer info with PKCS7_SIGNER_INFO type
 * \return  null
 */
extern void signer_info_print(PKCS7_SIGNER_INFO*info);

/**
 * \fn asn1_octet_string_print(ASN1_OCTET_STRING *octet)
 * \param ASN1_OCTET_STRING * octet
 * \brief 
 *		print data with ASN1_OCTET_STRING type
 * \return  null
 */
extern void asn1_octet_string_print(ASN1_OCTET_STRING *octet);

/**
 * \fn pkcs7_recip_print(PKCS7_RECIP_INFO *recip)
 * \param PKCS7_RECIP_INFO *recip [ recipient information ]
 * \brief 
 *		print recipient information in detail
 * \return  null
 */
extern void pkcs7_recip_print(PKCS7_RECIP_INFO *recip);
/**
 * \fn asn1_object_print(ASN1_OBJECT *a, const char* title)
 * \param ASN1_OBJECT *a		[ ASN1_OBJECT pointer  ] 
 * \param const char* title	[ description of the ASN1_OBJECT, will be printed at the head] 
 * \brief 
 *		print data with ASN1_OBJECT type
 * \return null
 */
extern void asn1_object_print(ASN1_OBJECT *a, const char* title);

/**
 * \fn pkcs7_envelop_print(PKCS7_ENVELOPE* envelop)
 * \param PKCS7_ENVELOPE* envelop [ enveloped structure data] 
 * \brief 
 *		print data with PKCS7_ENVELOPE type
 * \return  null
 */
extern void pkcs7_envelop_print(PKCS7_ENVELOPE* envelop);

/**
 * \fn pkcs7_signed_and_envelop_print(PKCS7_SIGN_ENVELOPE* envelop)
 * \param PKCS7_SIGN_ENVELOPE * envelop [ signed and enveloped ]
 * \brief 
 *		print signed and enveloped data
 * \return  null
 */
extern void pkcs7_signed_and_envelop_print(PKCS7_SIGN_ENVELOPE* envelop);
#endif

