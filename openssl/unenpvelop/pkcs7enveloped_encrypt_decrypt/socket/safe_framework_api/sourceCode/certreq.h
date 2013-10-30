/**
 * FileName : certreq.h
 * Author	: danny lee
 * Email	: dannylsl@sina.com
 * Date		: 2013-07-12
 * Brief	: 
 *	data structure and functions used in creating certification application file
 */
#include <openssl/x509.h>
#include <openssl/rsa.h>
#include <string.h>
#include <stdio.h>

#define SET		1
#define UNSET	0

// DATA STRUCTURE	:	subjectInfo
// certification application file subject name info  
typedef struct subjectInfo{
	char countryname[3];			// must
	char statefullname[51];			// must
	char localityname[51];			// must
	char organizationname[51];		// must
	char organizationalUnit[51];	// must
	char commonname[51];			// must
	char emailaddress[51];			// must
	char extra_challengepwd[51];    // optional
	char extra_opt_company[51];		// optional
}subjectInfo;

/**
 * functionName	: setCountryName 
 * @Param: subjectInfo * subject
 * @Param: const char* countryname
 * Brief : 
 *		subject->countryname = countryname
 * return: 
 *	if set successfully, return SET(1) 
 *	else return UNSET(0)
 */
int setCountryName(subjectInfo* subject,const char * countryname){

	if(strlen(countryname) != 2){	
		printf("CountryName is illegal, only two letter permitted!\n");
		return UNSET;
	}else{
		memset(subject->countryname,0,3);
		strcpy(subject->countryname,countryname);
		return SET;
	}
}

/**
 * functionName	: setStateFullName  
 * @Param: subjectInfo * subject
 * @Param: const char* statename
 * Brief : 
 *		subject->statefullname = statename
 * return: 
 *	if set successfully, return SET(1) 
 *	else return UNSET(0)
 */
int setStateFullName(subjectInfo* subject, const char * statename){

	if(strlen(statename) > 50){
		printf("statename length is out of limitation of 50 letters!\n");	
		return UNSET;
	}else{
		memset(subject->statefullname,0,51);
		strcpy(subject->statefullname,statename);
		return SET;
	}	
}

/**
 * functionName	: setLocalityName   
 * @Param: subjectInfo * subject
 * @Param: const char* localityname
 * Brief : 
 *		subject->localityname = localityname
 * return: 
 *	if set successfully, return SET(1) 
 *	else return UNSET(0)
 */
int setLocalityName(subjectInfo* subject, const char* localityname){

	if(strlen(localityname) > 50){
		printf("localityname length is out of limitation of 50 letters!\n");
		return UNSET;
	}else{
		memset(subject->localityname,0,51);
		strcpy(subject->localityname,localityname);
		return SET;
	}
} 

/**
 * functionName	: setOrganizationName 
 * @Param: subjectInfo * subject
 * @Param: const char* organizationname
 * Brief : 
 *		subject->organizationname = organizationname
 * return: 
 *	if set successfully, return SET(1) 
 *	else return UNSET(0)
 */
int setOrganizationName(subjectInfo *subject, const char* organizationname){

	if(strlen(organizationname) > 50){
		printf("organizationname length is out limitation of 50 letters!\n");			
		return UNSET;
	}else{
		memset(subject->organizationname,0,51);	
		strcpy(subject->organizationname,organizationname);
		return SET;
	}	
}

/**
 * functionName	: setOrganizationalUnit
 * @Param: subjectInfo * subject
 * @Param: const char* organizationalUnit
 * Brief : 
 *		subject->organizationalUnit = organizationalUnit
 * return: 
 *	if set successfully, return SET(1) 
 *	else return UNSET(0)
 */
int setOrganizationalUnit(subjectInfo * subject, const char* organizationalUnit){

	if(strlen(organizationalUnit) > 50){
		printf("organizationalUnit length is out limitation of 50 letters!\n");
		return UNSET;
	}else{
		memset(subject->organizationalUnit,0,51);		
		strcpy(subject->organizationalUnit,organizationalUnit);
		return SET;
	}
}

/**
 * functionName	: setCommonname
 * @Param: subjectInfo * subject
 * @Param: const char* commonname
 * Brief : 
 *		subject->commonname = commonname
 * return: 
 *	if set successfully, return SET(1) 
 *	else return UNSET(0)
 */
int setCommonname(subjectInfo * subject, const char* commonname){

	if(strlen(commonname) > 50){
		printf("commonname length is out limitation of 50 letters!\n");	
		return UNSET;
	}else{
		memset(subject->commonname,0,51);
		strcpy(subject->commonname,commonname);
		return SET;
	}
}

/**
 * functionName	: setEmailAddress 
 * @Param: subjectInfo * subject
 * @Param: const char* emailaddress
 * Brief : 
 *		subject->emailaddress = emailaddress	
 * return: 
 *	if set successfully, return SET(1) 
 *	else return UNSET(0)
 */
int setEmailAddress(subjectInfo * subject,const char * emailaddress){

	if(strlen(emailaddress) > 50){
		printf("emailaddress length is out limitation of 50 letters!\n");
		return UNSET;
	}else{
		memset(subject->emailaddress,0,50);	
		strcpy(subject->emailaddress,emailaddress);
		return SET;
	}	
}

/**
 * functionName	: setExtChallengepwd
 * @Param: subjectInfo * subject
 * @Param: const char* extra_challengepwd
 * Brief : 
 *		subject->extra_challengepwd = extra_challengepwd
 * return: 
 *	if set successfully, return SET(1) 
 *	else return UNSET(0)
 */
int setExtChallengepwd(subjectInfo * subject,const char * extra_challengepwd){

	if(strlen(extra_challengepwd) > 50){
		printf("extra_challengepwd length is out limitation of 50 letters!\n");
		return UNSET;
	}else{
		memset(subject->extra_challengepwd,0,50);	
		strcpy(subject->extra_challengepwd,extra_challengepwd);
		return SET;
	}	

}

/**
 * functionName	:  setExtOptCompany 
 * @Param: subjectInfo * subject
 * @Param: const char* extra_opt_company
 * Brief : 
 *		subject->extra_opt_company = extra_opt_company
 * return: 
 *	if set successfully, return SET(1) 
 *	else return UNSET(0)
 */
int setExtOptCompany(subjectInfo* subject, const char* extra_opt_company){

	if(strlen(extra_opt_company) > 50){
		printf("extra_opt_company length is out limitation of 50 letters!\n");
		return UNSET;
	}else{
		memset(subject->extra_opt_company,0,50);	
		strcpy(subject->extra_opt_company,extra_opt_company);
		return SET;
	}	

}

/**
 * functionName	: subjectCheck 
 * @Param: subjectInfo * subject
 * Brief : 
 *		check information of subject if all the must info are filled	
 * return: 
 *		if all the must info are filled, return 0
 *		else return value < 0
 */
int subjectCheck(subjectInfo* subject){
	int ret = 0;
	if(!strcmp(subject->countryname,""))				
		ret = -1;
	if(!strcmp(subject->statefullname,""))
		ret = -2;
	if(!strcmp(subject->localityname,""))
		ret = -3;
	if(!strcmp(subject->organizationname,""))
		ret = -4;
	if(!strcmp(subject->organizationalUnit,""))
		ret = -5;
	if(!strcmp(subject->commonname,""))
		ret = -6;
	if(!strcmp(subject->emailaddress,""))
		ret = -7;
	return ret;	
} 

/**
 * functionName	: subject2name
 * @Param: subjectInfo * subject
 * Brief : 
 *		initialize name with subjectInfo
 * return: 
 *		no error check, return 0
 */
int subject2name(const subjectInfo* subject,X509_NAME * name){

	X509_NAME_ENTRY *entry = NULL;
	
	entry = X509_NAME_ENTRY_create_by_txt(&entry,"commonName",V_ASN1_UTF8STRING,(unsigned char*)subject->commonname,strlen(subject->commonname));
	X509_NAME_add_entry(name,entry,0,-1);

	entry = X509_NAME_ENTRY_create_by_txt(&entry,"countryName",V_ASN1_UTF8STRING,(unsigned char*)subject->countryname,strlen(subject->countryname));
	X509_NAME_add_entry(name,entry,1,-1);
	
	entry = X509_NAME_ENTRY_create_by_txt(&entry,"emailAddress",V_ASN1_IA5STRING,(unsigned char*)subject->emailaddress,strlen(subject->emailaddress));
	X509_NAME_add_entry(name,entry,2,-1);

	entry = X509_NAME_ENTRY_create_by_txt(&entry,"stateOrProvinceName",V_ASN1_UTF8STRING,(unsigned char*)subject->statefullname,strlen(subject->statefullname));
	X509_NAME_add_entry(name,entry,3,-1);

	entry = X509_NAME_ENTRY_create_by_txt(&entry,"localityName",V_ASN1_UTF8STRING,(unsigned char*)subject->localityname,strlen(subject->localityname));	
	X509_NAME_add_entry(name,entry,4,-1);

	entry = X509_NAME_ENTRY_create_by_txt(&entry,"organizationName",V_ASN1_UTF8STRING,(unsigned char*)subject->organizationname,strlen(subject->organizationname));
	X509_NAME_add_entry(name,entry,5,-1);
	
	entry = X509_NAME_ENTRY_create_by_txt(&entry,"organizationalUnitName",V_ASN1_UTF8STRING,(unsigned char*)subject->organizationalUnit,strlen(subject->organizationalUnit));
	X509_NAME_add_entry(name,entry,6,-1);

	return 0;
}


/**
 * functionName	: genApply 
 * @Param: const char *certname			[certification application filename]
 * @Param: const subjectInfo * subject  [subject info]
 * Brief : 
 *		use subject to create certification application file which is named certname
 * return: 
 *		if failed to sign, return -1			
 *		if successfully generating certification application file, return 0
 */
int genApply(const char *certname, const subjectInfo *subject){
	int ret;
	long version;
	X509_REQ *req;		//certification application	
	X509_NAME *name;	//information of applyer
	EVP_PKEY *pkey;
	RSA *rsa;
	char mdout[20];
	int len,mdlen;
	int bits = 512;
	unsigned long e = RSA_3;
	unsigned char * der, *p;
	const EVP_MD *md;
	BIO *b;

	req = X509_REQ_new();
	version = 1;
	ret = X509_REQ_set_version(req,version);

	name = X509_NAME_new(); 
	// initialize applyer information
	subject2name(subject,name);	

	ret = X509_REQ_set_subject_name(req,name); //subject name
	// public key	
	pkey = EVP_PKEY_new();
	rsa = RSA_generate_key(bits,e,NULL,NULL);
	EVP_PKEY_assign_RSA(pkey,rsa);
	ret = X509_REQ_set_pubkey(req,pkey);  

	md = EVP_sha1();	
	ret = X509_REQ_digest(req,md,(unsigned char*)mdout,(unsigned int*)&mdlen);
	ret = X509_REQ_sign(req,pkey,md);
	if(!ret){
		printf("sign error!\n");	
		X509_REQ_free(req);
		return -1; 
	}
	
	// Write to pem                          //写入文件PEM格式
	b = BIO_new_file(certname,"w");           
	PEM_write_bio_X509_REQ(b,req,NULL,NULL);
	BIO_free(b);

	// DER encode	                         //DER编码
	len = i2d_X509_REQ(req,NULL);
	der = malloc(len);
	p = der;
	len = i2d_X509_REQ(req,&p);
	
	free(der);	
	X509_REQ_free(req);
	return 0;

}
