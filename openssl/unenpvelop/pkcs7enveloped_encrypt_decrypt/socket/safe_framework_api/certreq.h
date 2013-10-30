/**
 * \file certreq.h
 * \brief 
 *	data structure and functions used in creating certification application file
 */
#include <openssl/x509.h>
#include <openssl/rsa.h>
#include <string.h>
#include <stdio.h>

#define SET		1
#define UNSET	0

/**
 * \var  subjectInfo
 * \brief Certification application file subject name Information
 * \warning 
 *		countryname is two letters limited \n
 *		other information is 50 letters limited \n
 *		extra_challengepwd and extra_opt_company is optional
 */
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
 * \fn setCountryName(subjectInfo* subject,const char * countryname) 
 * \param subjectInfo * subject
 * \param const char* countryname
 * \brief 
 *		subject->countryname = countryname
 * \return 
 *	if set successfully, return SET(1)  \n
 *	else return UNSET(0)
 */
extern int setCountryName(subjectInfo* subject,const char * countryname);

/**
 * \fn setStateFullName(subjectInfo* subject, const char * statename)  
 * \param subjectInfo * subject
 * \param const char* statename
 * \brief 
 *		subject->statefullname = statename
 * \return 
 *	if set successfully, return SET(1) \n
 *	else return UNSET(0)
 */
extern int setStateFullName(subjectInfo* subject, const char * statename);

/**
 * \fn setLocalityName(subjectInfo* subject, const char* localityname)   
 * \param subjectInfo * subject
 * \param const char* localityname
 * \brief 
 *		subject->localityname = localityname
 * \return 
 *	if set successfully, return SET(1) \n
 *	else return UNSET(0)
 */
extern int setLocalityName(subjectInfo* subject, const char* localityname);

/**
 * \fn setOrganizationName(subjectInfo *subject, const char* organizationname) 
 * \param subjectInfo * subject
 * \param const char* organizationname
 * \brief 
 *		subject->organizationname = organizationname
 * \return 
 *	if set successfully, return SET(1) \n
 *	else return UNSET(0)
 */
extern int setOrganizationName(subjectInfo *subject, const char* organizationname);

/**
 * \fn setOrganizationalUnit(subjectInfo * subject, const char* organizationalUnit)
 * \param subjectInfo * subject
 * \param const char* organizationalUnit
 * \brief 
 *		subject->organizationalUnit = organizationalUnit
 * \return 
 *	if set successfully, return SET(1) \n
 *	else return UNSET(0)
 */
extern int setOrganizationalUnit(subjectInfo * subject, const char* organizationalUnit);

/**
 * \fn setCommonname(subjectInfo * subject, const char* commonname)
 * \param subjectInfo * subject
 * \param const char* commonname
 * \brief 
 *		subject->commonname = commonname
 * \return 
 *	if set successfully, return SET(1) \n
 *	else return UNSET(0)
 */
extern int setCommonname(subjectInfo * subject, const char* commonname);

/**
 * \fn setEmailAddress(subjectInfo * subject,const char * emailaddress) 
 * \param subjectInfo * subject
 * \param const char* emailaddress
 * \brief 
 *		subject->emailaddress = emailaddress	
 * \return 
 *	if set successfully, return SET(1) \n
 *	else return UNSET(0)
 */
extern int setEmailAddress(subjectInfo * subject,const char * emailaddress);

/**
 * \fn setExtChallengepwd(subjectInfo * subject,const char * extra_challengepwd)
 * \param subjectInfo * subject
 * \param const char* extra_challengepwd
 * \brief 
 *		subject->extra_challengepwd = extra_challengepwd
 * \return 
 *	if set successfully, return SET(1) \n
 *	else return UNSET(0)
 */
extern int setExtChallengepwd(subjectInfo * subject,const char * extra_challengepwd);

/**
 * \fn  setExtOptCompany(subjectInfo* subject, const char* extra_opt_company) 
 * \param subjectInfo * subject
 * \param const char* extra_opt_company
 * \brief 
 *		subject->extra_opt_company = extra_opt_company
 * \return 
 *	if set successfully, return SET(1) \n
 *	else return UNSET(0)
 */
extern int setExtOptCompany(subjectInfo* subject, const char* extra_opt_company);

/**
 * \fn subjectCheck(subjectInfo* subject) 
 * \param subjectInfo * subject
 * \brief 
 *		check information of subject if all the must info are filled	
 * \return 
 *		if all the must info are filled, return 0\n
 *		else return value < 0
 */
extern int subjectCheck(subjectInfo* subject);

/**
 * \fn subject2name(const subjectInfo* subject,X509_NAME * name)
 * \param subjectInfo * subject
 * \brief 
 *		initialize name with subjectInfo
 * \return 
 *		no error check, return 0
 */
extern int subject2name(const subjectInfo* subject,X509_NAME * name);

/**
 * \fn genApply(const char *certname, const subjectInfo *subject) 
 * \param const char *certname			[certification application filename]
 * \param const subjectInfo * subject  [subject info]
 * \brief 
 *		use subject to create certification application file which is named certname
 * \return 
 *		if failed to sign, return -1 \n			
 *		if successfully generating certification application file, return 0
 */
extern int genApply(const char *certname, const subjectInfo *subject);
