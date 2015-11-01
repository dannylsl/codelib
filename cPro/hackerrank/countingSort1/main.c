//https://www.hackerrank.com/challenges/countingsort1
//https://www.hackerrank.com/challenges/countingsort2
//

#include <stdio.h>
#include <string.h>


void print_arr(int ar_size, short int ar[]) {
    int i ;
    for(i = 0; i < ar_size; i++) {
        printf("%d ", ar[i]);
    };
    return;
}


void print_countSorted_data(int ar_size, short int ar[]) {
    int i, j;
    for(i = 0; i < ar_size; i++) {
        for(j = 0; j < ar[i]; j++) {
            printf("%d ",i);
        }
    }
}

int main(int argc, char *argv[]) {
    int len;
    short int count[100] = {0};
    int i,tmp;

    //printf("Input the array length:");
    scanf("%d",&len);

    for(i = 0; i < len; i++) {
        scanf("%d",&tmp);
        count[tmp]++;
    }

    print_countSorted_data(100, count);

    return 0;
}
