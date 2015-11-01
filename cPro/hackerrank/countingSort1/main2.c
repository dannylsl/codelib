//https://www.hackerrank.com/challenges/countingsort3

#include <stdio.h>

void print_L(int ar_size, int L[]) {
    int i, Lvalue = 0, j;
    for(i = 0; i < ar_size; i++) {
        Lvalue = 0;
        for(j = 0; j <= i; j++) {
            Lvalue = Lvalue + L[j];
        }
        printf("%d ", Lvalue);
    }
}

int main(int argc, char* argv[]) {
    int len;
    int i,value;
    int count[100] = {0};
    char str[100];

    scanf("%d",&len);

    for(i = 0; i < len;  i++) {
        scanf("%d %s",&value, str);
        count[value]++;
    }

    print_L(100, count);
    return 0;
}
