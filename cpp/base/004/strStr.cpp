#include <iostream>
using namespace std;

char * strStr(char *haystack, char *needle) {
	char *hp = haystack;
	char *np = needle;
	char *res = NULL;

	if(haystack == "" && needle == "") {
		cout<<"Empty String"<<endl;
		return haystack;
	}

	while(*hp != '\0') {
		if( *hp != *np) {
			hp++;
		}else {
			res = hp;
			while(*np != '\0') {
				if(*np == *hp) {
					np++;
					hp++;
				}else {
					hp = res + 1;
					np = needle;
					res = NULL;
					break;
				}
			}
		}
	}
	return res;
}

int main() {
/* Notice
 * if you set the str without const, it will turn warning:
 *	warning: deprecated conversion from string constant to ‘char*’ 
 *
 * Convert every parameters to the type the function define
 */
	const char *str1 = "mississippi";
	const char *str2 = "issip";

	cout<<"Str1="<<str1<<endl;	
	cout<<"Str2="<<str2<<endl;	
// Pay attention to the FORCE CONVERTION
	cout<<"strStr="<<strStr((char*)str1,(char*)str2)<<endl;
}
