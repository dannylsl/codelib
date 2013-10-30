#include "certreq.h"

int main(){
	subjectInfo subject;	
	printf("HelloWorld!\n");	

	setCommonname(&subject,"DANNY LEE");
	setCountryName(&subject,"CN");
	setEmailAddress(&subject,"dannylsl@sina.com");
	setStateFullName(&subject,"ZheJiang");
	setOrganizationName(&subject,"SSPKU");
	setOrganizationalUnit(&subject,"Peking University");
	setLocalityName(&subject,"24 JinYuan Road");
	if(subjectCheck(&subject) < 0)
		printf("subject error set!\n");
	printf("subject set!\n");
	genApply("genCertName.pem",&subject);

	return 0;
}
