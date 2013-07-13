#include "certreq.h"

int main(){
	subjectInfo subject;	
	printf("HelloWorld!\n");	

	setCommonname(&subject,"XiaoRua");
	setCountryName(&subject,"HL");
	setEmailAddress(&subject,"sanpuyouyou@163.com");
	setStateFullName(&subject,"Heilongjiang");
	setOrganizationName(&subject,"SSPKU");
	setOrganizationalUnit(&subject,"Peking University");
	setLocalityName(&subject,"24 JinYuan Road");
	if(subjectCheck(&subject) < 0)
		printf("subject error set!\n");
	printf("subject set!\n");
	genApply("genCertName.pem",&subject);

	return 0;
}
