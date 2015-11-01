#include <iostream>
#include <cstring>
using namespace std;

char * strStr(char *haystack, char *needle) {
    char *hp = haystack;
    char *np = needle;
    char *res = NULL;

    if(!strcmp(haystack,"") && !strcmp(needle,"")) {
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

char * strStr_index(char *haystack, char *needle) {
    int hl = strlen(haystack);
    int nl = strlen(needle);
    int k = 0;
    int i = 0;
    for (i = 0; i < hl;) {
        if(haystack[i] != needle[0]) {
            i++;
        } else {
            k = i;
            for(int j = 0; j <= nl;) {
                if(haystack[k] == needle[j]) {
                    if(j != (nl-1)) {
                        k++;
                        j++;
                    } else {
                        return haystack+i;
                    }
                }else {
                    i++;
                    break;
                }
            }

        }
    }
    return haystack+i;
}

int main() {
/* Notice
 * if you set the str without const, it will turn warning:
 *  warning: deprecated conversion from string constant to ‘char*’
 *
 * Convert every parameters to the type the function define
 */
    const char *str1 = "mississippi";
    const char *str2 = "issip";

    cout<<"Str1="<<str1<<endl;
    cout<<"Str2="<<str2<<endl;
// Pay attention to the FORCE CONVERTION
    cout<<"strStr="<<strStr((char*)str1,(char*)str2)<<endl;
    cout<<"strStr_index="<<strStr_index((char*)str1,(char*)str2)<<endl;
}
