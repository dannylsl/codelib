//https://www.hackerrank.com/challenges/insertionsort2
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>


void print_ar(int ar_size, int *ar) {
    int i;
    for(i = 0; i < ar_size; i++) {
        printf("%d ",ar[i]);
    }
    printf("\n");
}


void insertionSort(int ar_size, int *  ar) {
    int i,j, available;
    for(i = 0; i < ar_size; i++) {
        int value = ar[i];
        available = i;
        for(j=i-1; j >= 0; j--) {
            if(value < ar[j]) {
                ar[available] = ar[j];
                available = j;
            }else{
                break;
            }
        }
        ar[available] = value;
        print_ar(ar_size, ar);
    }
}

int main(void) {

    int _ar_size;
    scanf("%d", &_ar_size);
    int _ar[_ar_size], _ar_i;
    for(_ar_i = 0; _ar_i < _ar_size; _ar_i++) {
        scanf("%d", &_ar[_ar_i]);
    }

    insertionSort(_ar_size, _ar);

    return 0;
}
